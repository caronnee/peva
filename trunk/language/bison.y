%{
	#include <iostream>
	#include "header1.h"
	#include "robot.h"
	#include "parser_functions.h"

	#define YYSTYPE Lval 
	#define YYLTYPE unsigned
	#define YYLLOC_DEFAULT(cur, rhs, n)	do { if(n) (cur)=(rhs)[1]; else (cur)=(rhs)[0]; } while(0)

	#define YYERROR_VERBOSE 1		
	static void yyerror(YYLTYPE *line, Robots* ctx, const char *m);

%}

/* keywords */
%token TOKEN_MAIN
%token TOKEN_LOCATION
%token TOKEN_OBJECT
%token TOKEN_VAR_REAL
%token TOKEN_VAR_INT
%token TOKEN_VOID
%token TOKEN_FUNCTION
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_WHILE
%token TOKEN_DO
%token TOKEN_FOR
%token TOKEN_RETURN
%token TOKEN_BREAK
%token TOKEN_REFERENCE
%token TOKEN_CONTINUE
%token TOKEN_ROBOT
%token<op> TOKEN_OPTION

/* delimiters */
%token TOKEN_SEMICOLON
%token TOKEN_DOT
%token TOKEN_COMMA
%token TOKEN_LPAR
%token TOKEN_RPAR
%token TOKEN_LSBRA
%token TOKEN_RSBRA
%token TOKEN_ASSIGN
%token TOKEN_BEGIN
%token TOKEN_END
%token<of> TOKEN_OBJECT_FEATURE

/* literals */
%token<ident> TOKEN_IDENTIFIER
%token<number> TOKEN_UINT
%token<f_number> TOKEN_REAL

/* target of game*/
%token TOKEN_VISIT
%token TOKEN_VISIT_SEQUENCE
%token TOKEN_KILLED
%token TOKEN_START

/* group tokens */
%token<operation> TOKEN_OPER_REL
%token<operation> TOKEN_OPER_SIGNADD
%token<operation> TOKEN_OPER_MUL
%token<operation> TOKEN_PLUSPLUS
%token<operation> TOKEN_MINUSMINUS
%token<operation> TOKEN_BOOL_AND
%token<operation> TOKEN_BOOL_OR

%type<idents> names
%type<type> simple_type
%type<type> complex_type
%type<type> type
%type<type> return_type

%type<ranges> ranges

%type<ident> function_header
%type<entries> parameters

%type<instructions> local_variables
%type<instructions> block_of_instructions 
%type<instructions> global_variables
%type<instructions> commands
%type<instructions> command
%type<instructions> matched
%type<instructions> unmatched
%type<instructions> init
%type<instructions> assign
%type<instructions> command_var
%type<instructions> simple_command

%type<output> values
%type<output> variable
%type<output> variable_left
%type<output> number
%type<output> declare_functions
%type<output> declare_function_
%type<output> unary_var
%type<output> expression_bool
%type<output> expression
%type<output> exps
%type<output> expression_base
%type<output> expression_mul
%type<output> expression_add
%type<output> expression_bool_base
%type<output> expression_bool_or
%type<output> call_fce
%type<output> call_parameters
%type<output> array_access

%type<positions> places

%start program
%error-verbose
%pure-parser
%parse-param { Robots *program }
%lex-param { Robots *program }
%locations
%%

program: program robot { program->robots.push_back(program->actualRobot); }
       |robot { program->robots.push_back(program->actualRobot);}
	;

define_bot:TOKEN_ROBOT TOKEN_IDENTIFIER { program->createNew($2); }
	  ;

robot:  define_bot TOKEN_BEGIN options targets global_variables declare_functions TOKEN_MAIN TOKEN_LPAR TOKEN_RPAR block_of_instructions TOKEN_END
	{ 
	  std::vector<Parameter_entry> p;
	  program->actualRobot->add_global($5);
	  reg(program->actualRobot, p, $10); 
	} //skonsoliduje vsetky instrukcie, co sa doteraz vygenerovali
	;
//OK
targets: /* default target */
      	|targets TOKEN_KILLED TOKEN_OPER_REL TOKEN_UINT { program->actualRobot->addKilled(@2,$3,$4);}
	|targets TOKEN_VISIT TOKEN_LPAR places TOKEN_RPAR {program->actualRobot->addVisit($4);}
	|targets TOKEN_VISIT_SEQUENCE TOKEN_LPAR places TOKEN_RPAR {program->actualRobot->addVisitSeq($4);}
	;
//OK
places: TOKEN_LSBRA TOKEN_UINT TOKEN_COMMA TOKEN_UINT TOKEN_RSBRA { $$.push_back(Position($2,$4)); }
	| places TOKEN_COMMA TOKEN_LSBRA TOKEN_UINT TOKEN_COMMA TOKEN_UINT TOKEN_RSBRA {$$ = $1; $$.push_back(Position($4,$6)); }
	| TOKEN_START TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { $$.push_back(Position(-1, $3)); }
	| places TOKEN_COMMA TOKEN_START TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA  {$$ = $1; $$.push_back(Position(-1,$5)); }
	;
//OK
options: // defaultne opsny, normalny default alebo ako boli nadekralovane
	| options TOKEN_OPTION TOKEN_ASSIGN TOKEN_UINT { program->set($2,$4);}
	;
//definicie, iba instrukcie, ziadne kontrolovanie
global_variables:	/*	ziadne parametre	*/ { $$.clear(); }
	|global_variables local_variables { $$=join_instructions($1,$2);}
	;

//vsetky typy, ale moze premenna nadobudnut, token TYPE
type:	  simple_type { $$ = $1;}
	| complex_type { $$ = $1;}
	; 

/* definicie, lokalnych a globalnych premennych, local variables cez command_var */
local_variables:  type names TOKEN_SEMICOLON 
	       {  
			std::cout << "deklarujem premenne" << std::endl;
getc(stdin);
			for(int i =0; i< $2.size(); i++)
			{
				Node * n = program->actualRobot->add($2[i].id, $1); //pridali sme do stromu pre neskorsie vyhladavanie
				std::cout << "zacinam: " << n->type_of_variable->type<<std::endl;
				$$.push_back(new InstructionCreate(n)); 
				if ($2[i].default_set) 
					$$ = join_instructions($$, assign_default(@1,program->actualRobot, n, $2[i]));
			}
			std::cout << "dodeklarovane" << std::endl;
getc(stdin);
		}
	;

//OK
simple_type: TOKEN_VAR_REAL { $$ = program->actualRobot->find_type(TypeReal); } //najdi REAL
    	|TOKEN_VAR_INT { $$ = program->actualRobot->find_type(TypeInteger); }
	|TOKEN_LOCATION{ $$ = program->actualRobot->find_type(TypeLocation);}
	|TOKEN_OBJECT{ $$ = program->actualRobot->find_type(TypeObject); }
	;

//OK
complex_type: simple_type ranges { 
	    Create_type * t = $1; 
	    for(size_t i =0; i< $2.size(); i++) 
		t = program->actualRobot->find_array_type($2.back(),t);
	$$ = t;
	}//FIXME elegantnejsie
	;

ranges: TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { $$.push_back($2); }
      	|ranges TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { $$.push_back($3); }
	;

//pozuite iba u local_variables
names:	TOKEN_IDENTIFIER { $$.push_back(Constr($1)); } //nic loaded
	|TOKEN_IDENTIFIER TOKEN_ASSIGN expression { $$.push_back(Constr($1,$3.ins, $3.output)); std::cout << "pocit instrukcii:" << $3.ins.size(); } 
     	|TOKEN_IDENTIFIER TOKEN_ASSIGN TOKEN_BEGIN values TOKEN_END { $$.push_back(Constr($1, $4.ins, $4.output));std::cout << "pocit instr&&&ukcii:" << $4.ins.size(); } 
     	|names TOKEN_COMMA TOKEN_IDENTIFIER { $1.push_back(Constr($3)); $$ = $1; } //OK, bez inicializacie
     	|names TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN expression { $1.push_back(Constr($3,$5.ins,$5.output));$$ = $1; }  //OK, vysledok z expresny
     	|names TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN TOKEN_BEGIN values TOKEN_END { $1.push_back(Constr($3, $6.ins, $6.output));$$ = $1; } //inizializcia array a Location, laod vsetkych premenntch a poto spotupne storovanie
	;

/*pouzite len pri inicializacii, pravidlo names, preto tu mozu byt len zakladne typy*/
values: expression { $$ = $1; $$.ins.push_back(NULL);} // blabla load nieco, {Instruction, Type}
	| values TOKEN_COMMA expression {$$ = $1; $$.ins.push_back(NULL);$$.ins = join_instructions($$.ins, $3.ins); $$.output.push_back($3.output[0]); std::cout << "heee:" << $$.ins.size();}
	| TOKEN_BEGIN values TOKEN_END { $$ = $2;} //TODO nejak specialne osterit,
	| values TOKEN_COMMA TOKEN_BEGIN values TOKEN_END {$$ = $1; $$.ins = join_instructions($$.ins,$4.ins); for(size_t i=0; i<$4.output.size(); i++)$$.output.push_back($4.output[i]);} //addOputpuTokenNotDefined
	;

//deklarovanie, OK
declare_functions: /*	ziadne deklarovane funkcie	*/ { program->actualRobot->enter("main", program->actualRobot->find_type(TypeVoid)); }
	|declare_function_ { $$ = $1; program->actualRobot->enter("main", program->actualRobot->find_type(TypeVoid));}
	;

//deklarovanie funkcie, ok
function_header:return_type TOKEN_FUNCTION TOKEN_IDENTIFIER { $$ = $3; program->actualRobot->enter($3, $1); } //zatial nepotrebujeme vediet zanoraenie , enter loop pre returny
	;
//deklarovanie typu
return_type:	type { $$ = $1; } //Normalne sa neda premenna taka, ze VOID
	|TOKEN_VOID { $$ = program->actualRobot->find_type(TypeVoid); }
	;
//deklarovane type parametrov
parameters:	type TOKEN_IDENTIFIER { $$.push_back(Parameter_entry($2,PARAMETER_BY_VALUE, program->actualRobot->add($2, $1))); }
	| parameters TOKEN_COMMA type TOKEN_IDENTIFIER { $$ = $1; $$.push_back(Parameter_entry($4,PARAMETER_BY_VALUE,program->actualRobot->add($4, $3)));}
	| TOKEN_REFERENCE type TOKEN_IDENTIFIER { $$.push_back(Parameter_entry($3,PARAMETER_BY_REFERENCE, program->actualRobot->add($3, $2))); }
	| parameters TOKEN_COMMA TOKEN_REFERENCE type TOKEN_IDENTIFIER 
		{ $$.push_back(Parameter_entry($5,PARAMETER_BY_REFERENCE, program->actualRobot->add($5, $4))); }
	;
//deklarovanie tela funkcie
declare_function_:	function_header TOKEN_LPAR parameters TOKEN_RPAR block_of_instructions  
		 { 
		   reg(program->actualRobot,$3,$5);
		   program->actualRobot->leave();
		 } 
	|declare_function_ function_header TOKEN_LPAR parameters TOKEN_RPAR block_of_instructions 
		{ 
		  reg(program->actualRobot,$4,$6); 
		  program->actualRobot->leave();
		  program->actualRobot->end_loop();
		}
	|function_header TOKEN_LPAR TOKEN_RPAR block_of_instructions 
		{ 
		  std::vector<Parameter_entry> a; 
		  reg(program->actualRobot, a, $4); 
		  program->actualRobot->leave();
		} 
	|declare_function_ function_header TOKEN_LPAR TOKEN_RPAR block_of_instructions 
		{
		  set_breaks(program->actualRobot, $5);
		  std::vector<Parameter_entry> a; 
		  reg(program->actualRobot, a, $5);
		  program->actualRobot->leave(); 
		}
	;
//Load ciala, na output sa dostava REAL alno INT, OK
number:		TOKEN_OPER_SIGNADD TOKEN_REAL { if (TOKEN_OPER_SIGNADD == OperationMinus ) {$2*=-1;} $$.ins.push_back(new InstructionLoad($2));$$.output.push_back(*program->actualRobot->find_type(TypeReal)); } 
      	|TOKEN_OPER_SIGNADD TOKEN_UINT { if (TOKEN_OPER_SIGNADD == OperationMinus) {$2*=-1;} $$.ins.push_back(new InstructionLoad($2)); $$.output.push_back( *program->actualRobot->find_type(TypeInteger));} 
      	|TOKEN_REAL { $$.ins.push_back(new InstructionLoad($1)); $$.output.push_back(*program->actualRobot->find_type(TypeReal)); } 
      	|TOKEN_UINT { $$.ins.push_back(new InstructionLoad($1)); $$.output.push_back(*program->actualRobot->find_type(TypeInteger)); } 
	;
//tu by mal byt prazdny output
begin:	TOKEN_BEGIN { program->actualRobot->core->depth++; }
     	;
//tu by mal byt prazdny output
end:	TOKEN_END { program->actualRobot->core->depth--; }
   	;
//tu by mal byt prazdny output
block_of_instructions: begin end { $$.push_back(new InstructionBegin()); $$.push_back(new InstructionEndBlock());}
	|begin TOKEN_SEMICOLON end  { $$.clear();$$.push_back(new InstructionBegin()); $$.push_back(new InstructionEndBlock()); }
	|begin commands end { $$.push_back(new InstructionBegin()); $$ = join_instructions($$, $2);$$.push_back(new InstructionEndBlock()); }
	;
//pradny output
commands: matched {$$ = $1;}
	| commands matched { $$ = join_instructions($1, $2); }
	| unmatched {$$ = $1;}
	| commands unmatched { $$ = join_instructions($1, $2); }
	;
//tu by mal byt prazdny output
forcycle:	TOKEN_FOR { program->actualRobot->enter_loop();}
	;
//tu by mal byt prazdny output
do_cycle:	TOKEN_DO { program->actualRobot->enter_loop();}
	;
//tu by mal byt prazdny output
while_cycle:	TOKEN_WHILE { program->actualRobot->enter_loop();}
	;
//tu by mal byt prazdny output
command:	forcycle TOKEN_LPAR init expression_bool TOKEN_SEMICOLON simple_command TOKEN_RPAR block_of_instructions 
       		{ 
		  $8 = join_instructions($8, $6); 
		  $3.push_back(new InstructionMustJump($8.size())); 
		  $4.ins.push_back(new InstructionJump(-1*$8.size()-$4.ins.size()-1,0));
		  $8 = join_instructions($8,$4.ins);
		  $$ = join_instructions($3,$8);
		  set_breaks(program->actualRobot, $$);
		  program->actualRobot->end_loop();
		}
	|do_cycle block_of_instructions TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR TOKEN_SEMICOLON 
		{ $$ = join_instructions($2,$5.ins); 
		  $$.push_back(new InstructionJump(-1*$$.size()-1,0));
		  set_breaks(program->actualRobot, $$);
		  program->actualRobot->end_loop();
		}
	|while_cycle TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions
		{
			$$.push_back(new InstructionMustJump($5.size()));
			$3.ins = join_instructions($5,$3.ins);
			$$ = join_instructions($$, $3.ins);
			$$.push_back(new InstructionJump(-1*$$.size(),0));
		  	set_breaks(program->actualRobot, $$);
		  	program->actualRobot->end_loop();
		}
	|TOKEN_RETURN expression TOKEN_SEMICOLON
		{
			$$ = $2.ins;
			std::cout << program->actualRobot->core->nested_function << "--Tu dorazim---"<<program->actualRobot->core->nested_function->return_var->type_of_variable << std::endl;
			$$.insert($$.begin(), new InstructionLoadLocal(program->actualRobot->core->nested_function->return_var));
			if (($2.output.back().type == TypeInteger) && (program->actualRobot->core->nested_function->return_var->type_of_variable->type == TypeReal))
{
				$2.output.back() = *program->actualRobot->find_type(TypeReal);
				$$.push_back(new InstructionConversionToReal());
}
			else if (($2.output.back().type == TypeReal) && (program->actualRobot->core->nested_function->return_var->type_of_variable->type == TypeInteger))
{
				$2.output.back() = *program->actualRobot->find_type(TypeInteger);
				$$.push_back(new InstructionConversionToInt());
}
			if ($2.output.back()!=program->actualRobot->core->nested_function->return_var->type_of_variable->type)
{
				program->actualRobot->error(@1, Robot::ErrorConversionImpossible);
}
else{
			Node * nn = $2.ins.back()->get_node();
			switch($2.output.back().type)
			{
				case TypeInteger:
					$$.push_back(new InstructionStoreInteger()); //budu vedla seba, takze by to malo prejst
					break;
				case TypeReal:
					$$.push_back(new InstructionStoreReal());
					break;
				case TypeObject:
					$$.push_back(new InstructionStoreObject());
					break;
				case TypeLocation: //mame tam loadnutu iba jedno hodnotu, takze mozem zduplikovat
					$$.push_back(new InstructionLoad(0));	
					$$.push_back(new InstructionStoreInteger());
					if (nn->nested == Local)
						$$.push_back(new InstructionLoadLocal(nn));	
					else
						$$.push_back(new InstructionLoadGlobal(nn));	
					$$.push_back(new InstructionLoad(1));	
					$$.push_back(new InstructionStoreInteger());
					break;
				default://TODO predavanie arrayov?
				       program->actualRobot->error(@1,Robot::ErrorOperationNotSupported);
					break;
			}
			$$.push_back(new InstructionReturn(program->actualRobot->core->depth));
}
		}
	|TOKEN_RETURN TOKEN_SEMICOLON {$$.push_back(new InstructionReturn(program->actualRobot->core->depth));} //v node zostane predchadzajuca hodnota
	|TOKEN_BREAK TOKEN_SEMICOLON 
		{
			std::cout << "Adding break to in depth" <<program->actualRobot->core->depth << std::endl;
			$$.push_back(new InstructionBreak(program->actualRobot->last_loop_number, program->actualRobot->core->depth));
		}
	|TOKEN_CONTINUE TOKEN_SEMICOLON {$$.push_back(new InstructionContinue(program->actualRobot->last_loop_number, program->actualRobot->core->depth));}//TODO fistit, ci funguje
	|simple_command TOKEN_SEMICOLON {$$ = $1;}
      	;
//tu by mal byt prazdny output
command_var: local_variables { $$ = $1;} //tu nebude ziadny output, vyriesene v Locale;
	| command { $$ = $1;} //vyriesene v commande
	;
//mal by byt prazdy output
simple_command:	assign {$$ = $1;} //tu nie je ziadne output
	|unary_var { $$ = $1.ins; for (size_t i =0; i<$1.output.size(); i++); $$.push_back(new InstructionPop());} //Plus Plus Plus neee:)
	;
//pozor na to, co sa assignuje
assign: variable_left TOKEN_ASSIGN expression 
      		{
		std::cout << "Vstupujem do assignu" << $1.output.size()<<" " <<$3.output.size() << std::endl;
		Node * n = $3.ins.back()->get_node();
		if (($1.output.back().type == TypeInteger)&&($3.output.back().type == TypeReal))
			$3.ins.push_back(new InstructionConversionToInt());
		else if	(($1.output.back().type == TypeReal)&&($3.output.back().type == TypeInteger))
			$3.ins.push_back(new InstructionConversionToReal());
		else if ($1.output.back()!=$3.output.back())
			program->actualRobot->error(@2, Robot::ErrorConversionImpossible);
		$$ = join_instructions($1.ins, $3.ins); 
		switch ($1.output.back().type)
		{
			case TypeInteger:
				$$.push_back(new InstructionStoreInteger());
				break;
			case TypeReal:
				$$.push_back(new InstructionStoreReal());
				break;
			case TypeObject:
				$$.push_back(new InstructionStoreObject());
				break;
			case TypeLocation:
				$$.push_back(new InstructionLoad(0));
				$$.push_back(new InstructionStoreInteger());
				if (n->nested == Local)
					$$.push_back(new InstructionLoadLocal(n));
				else 
					$$.push_back(new InstructionLoadGlobal(n));
				$$.push_back(new InstructionLoad(1));
				$$.push_back(new InstructionStoreInteger()); //TODO type array
				break;
			default: program->actualRobot->error(@2, Robot::ErrorOperationNotSupported);
			}
		std::cout << "Vystupujem do assignu" << std::endl;
		 }
	;

variable_left: TOKEN_IDENTIFIER { $$ = ident_load(@1,program->actualRobot, $1);}
	| TOKEN_IDENTIFIER array_access { $$ = ident_load(@1,program->actualRobot, $1);
 $$.ins = join_instructions($$.ins, $2.ins);Create_type t = $$.output.back();
	for (size_t i =0; i< $2.output.size();i++)
		{ 
std::cout << "hhhh" ;
   getc(stdin);
			if (t.data_type == NULL)
			{
			std::cout<<"Tu sa dostanem" << std::endl;
				program->actualRobot->error(@1,Robot::ErrorOutOfRange);
				break;
			}
			else
				t = *t.data_type;	
		}
	$$.output.push_back(t);
 } //TODO v loade checkovat, ci sa nestavam mimo rame.
	;

call_fce:	TOKEN_IDENTIFIER TOKEN_LPAR call_parameters TOKEN_RPAR 
		{ $$ = $3; Function * f =program->actualRobot->find_f($1); 
		if (f == NULL)
			program->actualRobot->error(@1,Robot::ErrorFunctionNotDefined); 
		else {
			if (f->parameters.size()!=$3.output.size()) 
				program->actualRobot->error(@1,Robot::ErrorWrongNumberOfParameters);
			$$.ins.push_back(new Call(f));
			if (f->return_var->type_of_variable->type !=TypeVoid) 
				$$.output.push_back(*f->return_var->type_of_variable);
			}
		}
	|TOKEN_OBJECT_FEATURE TOKEN_LPAR call_parameters TOKEN_RPAR { 
		if ($3.output.size()!=1) program->actualRobot->error(@1,Robot::ErrorWrongNumberOfParameters);
			 $$.ins = feature(@1,program->actualRobot, $1, $3.output.back());
		$$.output.push_back(Create_type(TypeInteger));
		} 
	;

//Ok
call_parameters: expression {$$ = $1;} //loaded
	 | /* ziadny parameter */ {$$.ins.clear();}
	 |call_parameters TOKEN_COMMA expression 
	{$$.ins = join_instructions($3.ins,$1.ins);
		$$.output = $3.output;
		for (int i =0; i< $1.output.size();i++) 
			$$.output.push_back($1.output[i]);
	}
	;

//ziaden output
matched:TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE matched 
       		{
		  $5.push_back(new InstructionMustJump($7.size()));
		  $3.ins.push_back(new InstructionJump(0,$5.size()));
		  $$ =join_instructions($3.ins,$5);
		  $$ =join_instructions($$,$7);
		}
	| command_var {$$ = $1;} //prazdy output
	|block_of_instructions { $$ = $1;}
	;
//ziaden output
unmatched:	TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions {$3.ins.push_back(new InstructionJump(0,$5.size()));$$ = join_instructions($3.ins,$5);}
	 |TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR command {$3.ins.push_back(new InstructionJump(0,$5.size()));$$ = join_instructions($3.ins,$5);}

	 |TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE unmatched 
		{
		  $5.push_back(new InstructionMustJump($7.size())); //outputy sa tymto znicia
		  $3.ins.push_back(new InstructionJump(0,$5.size()));
		  $$ = join_instructions($3.ins,$5);
		  $$ = join_instructions($$,$7);
		}
	;
//ziadny output nema zostat
init: 	local_variables { $$ = $1;}
	| assign TOKEN_SEMICOLON {$$ = $1;}
	;

unary_var: variable {$$ = $1;}
	|variable TOKEN_PLUSPLUS {$$ = $1; if($$.output.back() == TypeReal) $$.ins.push_back(new InstructionPlusPlusReal());
						else if ($$.output.back() == TypeInteger) $$.ins.push_back(new InstructionPlusPlusInteger());
						else program->actualRobot->error(@2,Robot::ErrorOperationNotSupported);} 
	|variable TOKEN_MINUSMINUS { $$ = $1; if($$.output.back() == TypeReal)$$.ins.push_back(new InstructionMinusMinusReal());
						else if ($$.output.back() == TypeInteger) $$.ins.push_back(new InstructionMinusMinusInteger());
						else program->actualRobot->error(@2,Robot::ErrorOperationNotSupported);}

variable: TOKEN_IDENTIFIER { $$ = ident_load(@1,program->actualRobot, $1);}
	|TOKEN_IDENTIFIER array_access { $$ = ident_load(@1,program->actualRobot, $1);
		$$.ins = join_instructions($$.ins,$2.ins);
		for (size_t i =0; i<$2.output.size(); i++) 
			$$.output.push_back($2.output[i]);
		}
	|call_fce {$$ = $1;} //TODO ak je to funkci a s navratovou hodnotou, kontrola vsetkych vetvi, ci obsahuju return; main je procedura:)
	|variable TOKEN_DOT TOKEN_IDENTIFIER { for ( int i =0; i<$$.output.back().nested_vars.size(); i++)
						if ($$.output.back().nested_vars[i].name == $3)
						{ Create_type t = *$$.output.back().nested_vars[i].type;
						 $$.output.pop_back();
						 $$.output.push_back(t);
						}
					}
	;

array_access: TOKEN_LSBRA exps TOKEN_RSBRA { $$ = $2; $$.ins.push_back(new InstructionLoad());} //vezme zo stacku dve a odnoty pouzije, TODO check real
	|array_access TOKEN_LSBRA exps TOKEN_RSBRA {$$.output = $1.output;
 for ( size_t i = 0; i < $3.output.size();i++)
	$$.output.push_back($3.output[i]);
	$$.ins = join_instructions($1.ins, $3.ins);
	$$.ins.push_back(new InstructionLoad());
}  
	;


exps: expression {$$ = $1;}
	| exps TOKEN_COMMA expression { $$.ins = join_instructions($1.ins, $3.ins);
 $$.output = $1.output;
 for (int i =0;
 i<$1.output.size();
 i++)
$$.output.push_back($1.output[i]);
 }
	;

expression_base: unary_var { $$ = $1;}
	|number{$$ = $1; std::cout << "number, type" << $$.output.back().type << std::endl;}
	|TOKEN_LPAR expression TOKEN_RPAR {$$ = $2;}
	;

expression_mul:expression_base { $$ = $1; std::cout << "u expressny"<<$$.output.back().type;}
	|expression_mul TOKEN_OPER_MUL expression_base { 
	$$.ins = join_instructions($1.ins, $3.ins);
	Element e = operMul(@2, program->actualRobot, $2, $1.output.back(), $3.output.back());
	$$.ins = join_instructions($$.ins, e.ins);
	$$.output = e.output;
 }
	;

expression_add: expression_mul { $$ = $1; }
	|expression_add TOKEN_OPER_SIGNADD expression_mul
		{
		 $$.ins = join_instructions($1.ins, $3.ins);
		 Element e = (operAdd(@2, program->actualRobot,$2,$1.output.back(), $3.output.back()));
		 $$.ins = join_instructions($$.ins, e.ins);
		 $$.output = e.output;
 		}
	;

expression:	expression_add { $$ = $1; }
	;

expression_bool_base: expression { $$ = $1;}
	|expression TOKEN_OPER_REL expression {$$.ins = join_instructions($1.ins, $3.ins);
 Element e = operRel(@2,program->actualRobot,$2,$3.output.back(),$1.output.back());
	$$.ins = join_instructions($$.ins, e.ins);
 $$.output = e.output;
 }
	;


expression_bool_or: expression_bool_base {$$ = $1; }
	| expression_bool_or TOKEN_BOOL_OR TOKEN_LPAR expression_bool TOKEN_RPAR 
	{$$.ins = join_instructions($1.ins, $4.ins);
	 Element e = operOr(@2,program->actualRobot,$2,$1.output.back(),$4.output.back());
	 $$.output = e.output; //aj tak by tu vzy mal byt integer
 }
	;

//OK
expression_bool: expression_bool_or { $$ = $1; } //OK
	| expression_bool TOKEN_BOOL_AND expression_bool_or {$$.ins = join_instructions($1.ins, $3.ins); if ($1.output.back().type == TypeReal) $$.ins.push_back(new InstructionConversionToInt());
		else if ($$.output.back().type!= TypeInteger) program->actualRobot->error(@2,Robot::ErrorConversionImpossible); 
		else {$$.ins.push_back(new InstructionBinaryAnd());$$.output.push_back(Create_type(TypeInteger));}} //OK
	;
%%

extern FILE * yyin; //TODO zmenit na spravne nacitanie z editora

static void yyerror(unsigned *line, Robots* ctx, const char *message)
{
	printf("Syntax Error %s, line %d\n", message, *line);
}

int main(int argc, char ** argv)
{
	if(argc<2)
    	{
		puts("Input nor found\n");
		return 16;
    	}

	if((yyin=fopen(argv[1], "r"))==0)
    	{
		puts("Unable to open input\n");
		return 16;
    	}

	GamePoints points;
	Robots q(points); //TODO namiesto tohoto robot
	Create_type t;
	yyparse(&q);
    	fclose(yyin);
	std::cout << "-------------------------------------END---------------------------------------------------------------" << std::endl;
/*	q.actualRobot->output(&q.actualRobot->defined);
	for (int i =0; i<q.actualRobot->instructions.size(); i++)
		std::cout << q.actualRobot->instructions[i]->name_<<std::endl;
	q.actualRobot->save_to_xml();
	std::cout << "haho!" << std::endl;
   	q.actualRobot->execute();
*/
	for(int i =0; i<q.actualRobot->defined_types.size(); i++)
	{
		std::cout<<"adresa prvku" <<i << q.actualRobot->defined_types[i] << ", datatype address:" << q.actualRobot->defined_types[i]->data_type << std::endl;
	}
	if(q.actualRobot->errors)
		std::cout << q.actualRobot->errorList << std::endl;
	else
		q.actualRobot->save_to_xml();
	return 0;	
}
