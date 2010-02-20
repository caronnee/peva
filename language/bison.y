//TODO zrusit loadGlobal
//TODO do funkcii kopirovat cez load/sotre a hned za tym pridavat remove tempy kvoli pamat
//TODO pri for-e odtranit vytvorenie premennej, spravit sko  defauult temp
%{
#include <iostream>
#include <queue>
#include "../h/lval.h"
#include "../h/robot.h"
#include "../h/parser_functions.h"
#include "../h/hflex.h"
#include "../../add-ons/h/macros.h"

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
%token<of> TOKEN_OBJECT_FEATURE

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

/* literals */
%token<ident> TOKEN_IDENTIFIER
%token<number> TOKEN_UINT
%token<f_number> TOKEN_REAL
%token TOKEN_SEEN

/* target of game*/
%token TOKEN_VISIT
%token TOKEN_VISIT_SEQUENCE
%token TOKEN_KILLED
%token TOKEN_SKIN
%token TOKEN_KILL
%token TOKEN_START

/* group tokens */
%token<operation> TOKEN_OPER_REL
%token<operation> TOKEN_OPER_SIGNADD
%token<operation> TOKEN_OPER_MUL
%token<operation> TOKEN_PLUSPLUS
%token<operation> TOKEN_MINUSMINUS
%token<operation> TOKEN_BOOL_AND
%token<operation> TOKEN_BOOL_OR

%type<ident> function_name

%type<type> simple_type
%type<type> complex_type
%type<type> type
%type<type> return_type

%type<ranges> ranges
%type<ranges> integers
%type<ident> function_header

%type<entries> parameters_empty
%type<entries> parameters

%type<instructions> names
%type<instructions> names_
%type<instructions> cycle_for
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
%type<instructions> commands_and_empty

%type<array_access> array_access

%type<defVal> values

%type<output> array
%type<output> variable
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
%type<positions> places

%start program
%error-verbose

%pure-parser

%parse-param { Robots *program }

%lex-param { Robots *program }

%locations

%%

program: program robot 
	|robot 
	;
define_bot:TOKEN_ROBOT TOKEN_IDENTIFIER 
	{ 	
		program->createNew($2); 
	}
	;
robot:  define_bot TOKEN_BEGIN options targets global_variables declare_functions TOKEN_MAIN TOKEN_LPAR TOKEN_RPAR block_of_instructions TOKEN_END
	{ 
		program->actualRobot->add_global($5);
		program->actualRobot->add_function($10); 
		program->actualRobot->consolidate();
	}
	;
targets: /* default target */
	|targets TOKEN_KILLED TOKEN_OPER_REL TOKEN_UINT { program->actualRobot->core->body->addKilled(@2,$3,$4);}
	|targets TOKEN_VISIT TOKEN_LPAR places TOKEN_RPAR { program->actualRobot->core->body->addVisit($4);}
	|targets TOKEN_VISIT TOKEN_LPAR integers TOKEN_RPAR 
	{ 
		for (size_t i = 0; i< $4.size(); i++)
		{
			TargetVisit * t = new TargetVisit($4[i]);
			program->resolveTargets.push_back(t);
			program->actualRobot->core->body->addVisit(t);
		}
	}
	|targets TOKEN_VISIT_SEQUENCE TOKEN_LPAR places TOKEN_RPAR {program->actualRobot->core->body->addVisitSeq($4);}
	|targets TOKEN_VISIT_SEQUENCE TOKEN_LPAR integers TOKEN_RPAR 
	{
		std::vector<TargetVisit *> t;
		for (size_t i =0; i<$4.size(); i++)
		{
			t.push_back(new TargetVisit($4[i]));
			program->resolveTargets.push_back(t.back());
		}
		program->actualRobot->core->body->addVisitSeq(t);
	}
	;
places: TOKEN_LSBRA TOKEN_UINT TOKEN_COMMA TOKEN_UINT TOKEN_RSBRA 
	{ 
		$$.clear(); 
		$$.push_back(Position($2,$4)); 
	}
	| places TOKEN_COMMA TOKEN_LSBRA TOKEN_UINT TOKEN_COMMA TOKEN_UINT TOKEN_RSBRA 
	{
		$$ = $1; 
		$$.push_back(Position($4,$6)); 
	}
	| TOKEN_START TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA 
	{ 
		$$.clear(); 
		$$.push_back(Position(-1, $3)); 
	}
	| places TOKEN_COMMA TOKEN_START TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA  
	{
		$$ = $1; 
		$$.push_back(Position(-1,$5)); 
	}
	;
options: /* defaultne opsny, normalny default alebo ako boli nadekralovane */	
	{
		if (program->actualRobot->dev_null == NULL)
		{
			program->actualRobot->variables();
		}
	}
	| options TOKEN_OPTION TOKEN_ASSIGN TOKEN_UINT 
	{ 
		program->set($2,$4); 
	}
	| options TOKEN_KILL TOKEN_IDENTIFIER { 
		ResolveName n;n.robot = program->actualRobot;
		n.name = $3;
		program->resolveName.push_back(n);}
	| options TOKEN_SKIN TOKEN_IDENTIFIER 
	{	
		program->actualRobot->setSkin(program->addSkin($3)); 
		program->actualRobot->setSkin(program->addmSkin($3));
	}
	;
global_variables:	/*	ziadne parametre	*/ { $$.clear(); }
		| global_variables local_variables { $$= join_instructions($1,$2);}
		;
type:	  simple_type { $$ = $1; program->actualRobot->declare_type();}
	| complex_type { $$ = $1;program->actualRobot->declare_type();}
	; 
local_variables:  type names TOKEN_SEMICOLON 
		{
			$$ = $2;
			
			program->actualRobot->leave_type();
		}
		;
simple_type: TOKEN_VAR_REAL { $$ = program->actualRobot->find_type(TypeReal); } //najdi REAL
		|TOKEN_VAR_INT { $$ = program->actualRobot->find_type(TypeInteger); }
		|TOKEN_LOCATION{ $$ = program->actualRobot->find_type(TypeLocation);}
		|TOKEN_OBJECT{ $$ = program->actualRobot->find_type(TypeObject); }
		;
complex_type: simple_type ranges 
		{ 
			Create_type * t = $1; 
			for(size_t i = 0 ; i< $2.size(); i++)
			{
				t = program->actualRobot->find_array_type($2[i],t);
			}
			Create_type y= *t;
			while (y.data_type!=NULL)
			{
				y = *y.data_type;
			}
			$$ = t;
		}//FIXME elegantnejsie
		;
ranges: TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { $$.push_back($2); }
		|ranges TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { $$.push_back($3); }
		;
integers: TOKEN_UINT { $$.clear(); $$.push_back($1); }
	|integers TOKEN_COMMA TOKEN_UINT {$$.push_back($3); }
	;	
names_:	TOKEN_IDENTIFIER 
		{ 
			$$.clear();
			Node *n = program->actualRobot->add($1);
			$$.push_back(new InstructionCreate(n)); 
		} 
		|TOKEN_IDENTIFIER TOKEN_ASSIGN expression 
		{ 
			$$.clear();
			Node *n = program->actualRobot->add($1);
			$$.push_back(new InstructionCreate(n));
			$$.push_back(new InstructionLoadLocal(n));
			$$ = join_instructions($$, $3.ins);
			Instruction * in = possible_conversion(program->actualRobot->active_type.top()->type,$3.output.back().type);
			if (in)
			{
				$$.push_back(in);
				$3.output.back() = *program->actualRobot->active_type.top();
			}
			$$.push_back(get_store_type(@1, program->actualRobot, $3.output.back()));
		} 
		|TOKEN_IDENTIFIER TOKEN_ASSIGN begin_type values end_type
		{ 
			$$.clear();
			Node *n = program->actualRobot->add($1);
			$$.push_back(new InstructionCreate(n));
			$$.push_back(new InstructionLoadLocal(n));
			for (int i =1; i < $4.level; i++)
			{
				$$.push_back(new InstructionDuplicate());
			}
			$$ = join_instructions($$, $4.ins);
		} 
		;
names: names_ { $$ = $1; }
	|names names_ { $$ = join_instructions($1, $2); }
		;
begin_type: TOKEN_BEGIN { program->actualRobot->declare_next(); }
		;
end_type: TOKEN_END { program->actualRobot->leave_type(); }
		;
values:		expression { 
			$$.ins.clear();
			$$.ins.push_back(new InstructionLoad(0));
			$$.ins.push_back(new InstructionLoad());
			$$.ins = join_instructions($$.ins, $1.ins);
			Instruction * in = possible_conversion( program->actualRobot->active_type.top()->type,$1.output.back().type);
			if (in)
			{
				$$.ins.push_back(in);
				$1.output.back() = *program->actualRobot->active_type.top();
			}
			if ($1.output.back()!=*program->actualRobot->active_type.top())
			{
				TEST("nnnnnn?"<<@1 << " " << program->actualRobot->active_type.top()->type);
				program->actualRobot->error(@1, Robot::ErrorConversionImpossible);
			}
			else
			{
				$$.ins.push_back(get_store_type(@1, program->actualRobot, $1.output.back()));
				$$.level = 1;
			}
		} 
		| values TOKEN_COMMA expression 
		{
			$$.ins.clear();
			$$.ins = $1.ins;
			$$.ins.push_back(new InstructionLoad($1.level));
			$$.ins.push_back(new InstructionLoad());
			$$.ins = join_instructions($$.ins , $3.ins);
			Instruction * in = possible_conversion(program->actualRobot->active_type.top()->type,$3.output.back().type );
			if (in)
			{
				$$.ins.push_back(in);
				$3.output.back() = *program->actualRobot->active_type.top();
			}
			$$.ins.push_back(get_store_type(@1, program->actualRobot, $3.output.back()));
			if ($3.temp.back())
			{
				$$.ins.push_back(new InstructionRemoveTemp());
			}	
			$$.level = $1.level + 1;
		}
		| begin_type values end_type
		{ 
			$$.ins.clear();	
			$$.ins.push_back(new InstructionLoad(0)); //todo do actual type pridat, ze sme o type dalej, array dalej atd
			$$.ins.push_back(new InstructionLoad());
			for (int i = 1; i < $2.level; i++)
			{
				$$.ins.push_back(new InstructionDuplicate());
			}
			$$.ins = join_instructions($$.ins, $2.ins);
			$$.level = 1;
		} //TODO nejak specialne osterit, zaborky a podobne vecu u struktur
		| values TOKEN_COMMA begin_type values end_type
		{
			$$.ins.clear();
			$$ = $1; 
			$$.ins.push_back(new InstructionLoad($1.level));
			$$.ins.push_back(new InstructionLoad());
			for (int i = 1; i < $4.level; i++)
			{
				$$.ins.push_back(new InstructionDuplicate());
			}

			$$.ins = join_instructions($$.ins,$4.ins); 
			$$.level++;
		} //addOputpuTokenNotDefined
		;
declare_functions: /*	ziadne deklarovane funkcie	*/ 
			{ 
				std::vector<Parameter_entry> em;
				program->actualRobot->enter("main", em,program->actualRobot->find_type(TypeVoid)); 	
			}
		|declare_function_ 
		{ 
			$$ = $1;std::vector<Parameter_entry> em;
			program->actualRobot->enter("main", em, program->actualRobot->find_type(TypeVoid));
		}
		;

function_header:return_type function_name TOKEN_LPAR parameters_empty TOKEN_RPAR 
		{
			 $$ = $2;
			 program->actualRobot->enter($2,$4, $1); 
		} 
		;
function_name:	TOKEN_FUNCTION TOKEN_IDENTIFIER
		{
			$$ = $2;
			program->actualRobot->nested += $2 + DELIMINER_CHAR;
		}
		;
return_type:	TOKEN_VOID { $$ = program->actualRobot->find_type(TypeVoid);program->actualRobot->declare_type();}
		|type { $$ = $1; }
		;

parameters_empty:	{ $$.clear(); }
		| parameters { $$ = $1;}
		;
parameters:	type TOKEN_IDENTIFIER { $$.push_back(Parameter_entry($2,PARAMETER_BY_VALUE, program->actualRobot->add($2, $1))); }
		| parameters TOKEN_COMMA type TOKEN_IDENTIFIER { $$ = $1; $$.push_back(Parameter_entry($4,PARAMETER_BY_VALUE,program->actualRobot->add($4, $3))); }
		| TOKEN_REFERENCE type TOKEN_IDENTIFIER { $$.push_back(Parameter_entry($3,PARAMETER_BY_REFERENCE, program->actualRobot->add($3, $2))); }
		| parameters TOKEN_COMMA TOKEN_REFERENCE type TOKEN_IDENTIFIER 
		{ 
			$$.push_back(Parameter_entry($5,PARAMETER_BY_REFERENCE, program->actualRobot->add($5, $4))); 
		}
		;
declare_function_:	function_header block_of_instructions  
		{ 
			program->actualRobot->add_function($2);
			program->actualRobot->leave();
		} 
		|declare_function_ function_header block_of_instructions 
		{ 
			program->actualRobot->add_function($3); 
			program->actualRobot->leave();
		}
		;
number:		TOKEN_OPER_SIGNADD TOKEN_REAL 
		{ 
			if ($1 == OperationMinus ) 
			{
				$2*=-1;
			} 
			$$.ins.push_back(new InstructionLoad($2));
			$$.output.push_back(*program->actualRobot->find_type(TypeReal)); 
			$$.temp.push_back(false);
		} 
		|TOKEN_OPER_SIGNADD TOKEN_UINT 
		{ 
			if ($1 == OperationMinus) 
			{
				$2*=-1;
			} 
			$$.ins.push_back(new InstructionLoad($2)); 
			$$.output.push_back( *program->actualRobot->find_type(TypeInteger));
			$$.temp.push_back(false);
		}
		|TOKEN_REAL 
		{ 
			$$.ins.push_back(new InstructionLoad($1)); 
			$$.output.push_back(*program->actualRobot->find_type(TypeReal));
			$$.temp.push_back(false); 
		} 
		|TOKEN_UINT 
		{ 
			$$.ins.push_back(new InstructionLoad($1)); 
			$$.output.push_back(*program->actualRobot->find_type(TypeInteger));
			$$.temp.push_back(false); 
		} 
		;

begin:	TOKEN_BEGIN { program->actualRobot->core->depth++; program->actualRobot->defined.new_block();}
		;

end:	TOKEN_END { program->actualRobot->core->depth--; program->actualRobot->defined.leave_block();}
		;

block_of_instructions: begin commands_and_empty end 
		{ 
			$$.push_back(new InstructionBegin()); 
			$$ = join_instructions($$, $2);
			$$.push_back(new InstructionEndBlock()); 
		}
		;
commands_and_empty:  /* empty */ {$$.clear();}
		| commands {  $$ = $1; }
		;

commands: 	TOKEN_SEMICOLON { $$.clear(); }
		| matched {$$ = $1;}
		| commands matched { $$ = join_instructions($1, $2); }
		| unmatched { $$ = $1; }
		| commands unmatched { $$ = join_instructions($1, $2); }
		;
//FIXME dalo by sa aj inteligentjsie? Rozlisovat, ci som vytvorila premennu a potom oachat cyklus
cycle_for: TOKEN_FOR { program->actualRobot->core->depth++; $$.push_back(new InstructionBegin());program->actualRobot->defined.new_block();}
		;
command:	cycle_for TOKEN_LPAR init expression_bool TOKEN_SEMICOLON simple_command TOKEN_RPAR begin commands end 
		{ 
		//	INIT, BLOCK, COMMAND CONDITION
			if ($4.temp.back())
			{
				$4.ins.push_back(new InstructionRemoveTemp());
			}
			$9.push_back(new InstructionEndBlock($4.ins.size()+$6.size()+1));
			$9 = join_instructions($9, $6); 
			$3.push_back(new InstructionMustJump($9.size()+1)); 
			$3.push_back(new InstructionBegin(program->actualRobot->core->depth));
			$4.ins.push_back(new InstructionJump(-1*$9.size()-$4.ins.size()-2,0));
			$9 = join_instructions($9,$4.ins);
			$$ = join_instructions($3,$9);
			$$.push_back(new InstructionEndBlock());
			$$ = join_instructions($1, $$);
			program->actualRobot->core->depth--;
			program->actualRobot->defined.leave_block();
		}
		|TOKEN_DO begin commands end TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR TOKEN_SEMICOLON 
		{ 
			if ($7.temp.back())
			{
				$7.ins.push_back(new InstructionRemoveTemp());
			}
			$$.push_back(new InstructionBegin(program->actualRobot->core->depth));
			$3.push_back(new InstructionEndBlock($7.ins.size()+1));
			$$ = join_instructions($$, $3);
			$$ = join_instructions($$,$7.ins); 
			$$.push_back(new InstructionJump(-1*$$.size()-1,0));
		}
		|TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR begin commands end
		{
			if ($3.temp.back())
			{
				$3.ins.push_back(new InstructionRemoveTemp());
			}
			$$.push_back(new InstructionMustJump($6.size()+2));
			$$.push_back(new InstructionBegin(program->actualRobot->core->depth));
			$6.push_back(new InstructionEndBlock($3.ins.size()+1));
			$$ = join_instructions($$,$6);
			$$ = join_instructions($$,$3.ins);
			$$.push_back(new InstructionJump(-1*$$.size(),0));
		}
		|TOKEN_RETURN expression TOKEN_SEMICOLON
		{
			$$.push_back(new InstructionLoadLocal(program->actualRobot->core->nested_function->return_var));
			$$ = join_instructions($$,$2.ins);
			
			/* Check for types compatibility */
			if (($2.output.back().type == TypeInteger) && (program->actualRobot->core->nested_function->return_var->type_of_variable->type == TypeReal))
			{
				if ($2.temp.back())
				{
					$$.push_back(new InstructionRemoveTemp());
				}
				$2.output.back() = *program->actualRobot->find_type(TypeReal);
				$$.push_back(new InstructionConversionToReal());
				$2.temp.back() = true;
			}
			else if (($2.output.back().type == TypeReal) && (program->actualRobot->core->nested_function->return_var->type_of_variable->type == TypeInteger))
			{
				if ($2.temp.back())
				{
					$$.push_back(new InstructionRemoveTemp());
				}
				$2.output.back() = *program->actualRobot->find_type(TypeInteger);
				$$.push_back(new InstructionConversionToInt());
				$2.temp.back() = true;
			}

			/* Check for types equality */
			if ($2.output.back()!= *program->actualRobot->core->nested_function->return_var->type_of_variable)
			{
				program->actualRobot->error(@1, Robot::ErrorConversionImpossible);
			}
			else
				$$.push_back(new InstructionStore());
			if ($2.temp.back())
			{
				$$.push_back(new InstructionRemoveTemp());
			}
			$$.push_back(new InstructionLoadLocal(program->actualRobot->core->nested_function->return_var));// da sa dat aj na konci, vestko  uz je upratane
			$$.push_back(new InstructionReturn(program->actualRobot->core->depth));	
		}
		|TOKEN_RETURN TOKEN_SEMICOLON 
		{
			$$.push_back(new InstructionReturn(program->actualRobot->core->depth));
		} //v node zostane predchadzajuca hodnota//TODO ocheckovat vsetky vetvy
		
		|TOKEN_BREAK TOKEN_SEMICOLON 
		{
			std::cout << "Adding break to in depth" <<program->actualRobot->core->depth << std::endl;
			$$.push_back(new InstructionBreak(program->actualRobot->core->depth));
		}
		|TOKEN_CONTINUE TOKEN_SEMICOLON  //TODO nobreakable veci?
		{
			$$.push_back(new InstructionContinue(program->actualRobot->core->depth));
		}
		|simple_command TOKEN_SEMICOLON {$$ = $1;}
		;
command_var: local_variables { $$ = $1;} //tu nebude ziadny output, vyriesene v Locale;
		| command { $$ = $1;} //vyriesene v commande
		;
simple_command:	assign {$$ = $1;} //tu nie je ziadne output
		|unary_var 
		{ 
			$$ = $1.ins; 
			if($1.output.size()>0)
			{
				$$.push_back(new InstructionPop());
				if($1.temp.back())
					$$.push_back(new InstructionRemoveTemp());
			}
		} //Plus Plus Plus neee:)
		;
//pozor na to, co sa assignuje. TODO array/struct, ako by to vyzeralo/struct, ako by to vyzeralo->FIXME
assign: variable TOKEN_ASSIGN expression 
	{
		if (($1.output.back().type == TypeInteger)&&($3.output.back().type == TypeReal))
		{
			if ($3.temp.back())
			{
				$$.push_back(new InstructionRemoveTemp());
			}
			$3.ins.push_back(new InstructionConversionToInt());
			$3.temp.back() = true;
		}
		else if	(($1.output.back().type == TypeReal)&&($3.output.back().type == TypeInteger))
		{
			if ($3.temp.back())
			{
				$$.push_back(new InstructionRemoveTemp());
			}
			$3.ins.push_back(new InstructionConversionToReal());
			$3.temp.back() = true;
		}
		else if ($1.output.back()!=$3.output.back())
		{
			TEST("grrr") 
			program->actualRobot->error(@2, Robot::ErrorConversionImpossible);
		}
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
			case TypeArray:
				$$.push_back(new InstructionStore());
				break;
			case TypeLocation:
				$$.push_back(new InstructionDuplicate());
				$$.push_back(new InstructionLoad(0));
				$$.push_back(new InstructionStoreInteger());
				$$.push_back(new InstructionLoad(1));
				$$.push_back(new InstructionStoreInteger()); //TODO type array
				break;
			default: program->actualRobot->error(@2, Robot::ErrorOperationNotSupported);
		}
		if ($3.temp.back())
			$$.push_back(new InstructionRemoveTemp());
	}
	;
array: TOKEN_IDENTIFIER array_access 
		{
			$$ = ident_load(@1,program->actualRobot, $1);
			$$.ins = join_instructions($$.ins, $2.ins);
			$$.temp.push_back(false);
			Create_type tt = $$.output.back();	
			for(int i =$2.dimension; i>0; i--) 
			{
				if ($$.output.back().data_type == NULL)
				{
					program->actualRobot->error(@1,Robot::ErrorOutOfRange);
					break;
				}
				
				Create_type * t = $$.output.back().data_type;
				$$.output.back() = *t;
			}
		}
		|TOKEN_SEEN TOKEN_LSBRA number TOKEN_RSBRA
		{
			$$.clear();
			$$.ins = $3.ins;
			$$.output.push_back(*program->actualRobot->find_type(TypeObject));
			Instruction * in = possible_conversion($3.output.back().type, TypeInteger);
			if (in!=NULL)
			{
				$$.ins.push_back(in);
			}
			$$.ins.push_back(new InstructionEye());
			$$.temp.push_back(true);
		}
		;

call_fce:	TOKEN_IDENTIFIER TOKEN_LPAR call_parameters TOKEN_RPAR 
		{ 
			Function * f =program->actualRobot->find_f($1); 
			if (f == NULL)
			{
				program->actualRobot->error(@1,Robot::ErrorFunctionNotDefined); 
				$$.clear();
				$$.output.push_back(*program->actualRobot->find_type(TypeUndefined));
				$$.temp.push_back(true);
			}
			else 
			{
				if (f->parameters.size()!=$3.output.size()) 
				{
					program->actualRobot->error(@1,Robot::ErrorWrongNumberOfParameters);
				}
				else
				{
					size_t iter_out = 0;
					for (size_t i= 0; i< $3.ins.size(); i++)
					{
						if ($3.ins[i]!= NULL)
						{
							$$.ins.push_back($3.ins[i]);
							continue;
						}
						if (($3.output[iter_out].type == TypeReal)
								&&(f->parameters[iter_out].node->type_of_variable->type == TypeInteger))
						{
							if ($3.temp[iter_out])
							{
								$$.ins.push_back(new InstructionRemoveTemp());
							}
							$$.ins.push_back(new InstructionConversionToInt());
							$3.temp[iter_out] = true;
							$3.output[iter_out] = *program->actualRobot->find_type(TypeInteger);
						}
						if (($3.output[iter_out].type == TypeInteger)
								&&(f->parameters[iter_out].node->type_of_variable->type == TypeReal))
						{
							if ($3.temp[iter_out])
							{
								$$.ins.push_back(new InstructionRemoveTemp());
							}
							$3.temp[iter_out] = true;
							$$.ins.push_back(new InstructionConversionToReal());
							$3.output[iter_out] = *program->actualRobot->find_type(TypeReal);
						}
						if ($3.output[iter_out] != *f->parameters[iter_out].node->type_of_variable)
						{
							program->actualRobot->error(@1, Robot::ErrorConversionImpossible);
							break;
						}
						iter_out++;	
					}
					$$.ins.push_back(new Call(f));
					if (f->return_var->type_of_variable->type == TypeVoid)
						$$.output.clear();
					else
						$$.output.push_back(*f->return_var->type_of_variable);
				}
				for (size_t i =0; i< $3.temp.size(); i++)
				{
					if ($3.temp[i])
						$$.ins.push_back(new InstructionRemoveTemp()); //likvidovnie premennyh obsadenych v pamati

				}
				if (f->return_var->type_of_variable->type!= TypeVoid)
					$$.temp.push_back(true);
				else 
					$$.temp.push_back(false);
			}
		}
		|TOKEN_OBJECT_FEATURE TOKEN_LPAR call_parameters TOKEN_RPAR 
		{
			$$.clear();
			$$ = feature(@1,program->actualRobot, $1, $3);
			$$.temp.push_back(true);
		} 
		;

call_parameters: expression 
		{
			$$ = $1; 
			$$.ins.push_back(NULL);
		} 
		| /* ziadny parameter */ { $$.clear(); }
		|call_parameters TOKEN_COMMA expression 
		{
			$$.clear();
			$3.ins.push_back(NULL); //zalozka, po kolkatich instrukciach mi konci output, TODO zmenit
			$$.ins = join_instructions($1.ins,$3.ins);
			$$.output = $1.output;
			for (size_t i =0; i< $3.output.size();i++) 
			{
				$$.output.push_back($3.output[i]);
				$$.temp.push_back($3.temp[i]);
			}
		}
		;
matched:TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE matched 
	{
		$$.clear();
		if ($3.temp.back())
			{
				$3.ins.push_back(new InstructionRemoveTemp());
			}
		$5.push_back(new InstructionMustJump($7.size()));
		$3.ins.push_back(new InstructionJump(0,$5.size()));
		$$ =join_instructions($3.ins,$5);
		$$ =join_instructions($$,$7);
	}
	| command_var {$$ = $1;} //prazdy output
	|block_of_instructions { $$ = $1;}
	;
unmatched:	TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions 
		{
			if ($3.temp.back())
			{
				$3.ins.push_back(new InstructionRemoveTemp());
			}
			$3.ins.push_back(new InstructionJump(0,$5.size()));
			$$ = join_instructions($3.ins,$5);
		}
	|TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR command 
	{
		if ($3.temp.back())
			{
				$3.ins.push_back(new InstructionRemoveTemp());
			}
		$3.ins.push_back(new InstructionJump(0,$5.size()));
		$$ = join_instructions($3.ins,$5);
	}
	|TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE unmatched 
	{
		if ($3.temp.back())
			{
				$3.ins.push_back(new InstructionRemoveTemp());
			}
		$5.push_back(new InstructionMustJump($7.size())); //outputy sa tymto znicia
		$3.ins.push_back(new InstructionJump(0,$5.size()));
		$$ = join_instructions($3.ins,$5);
		$$ = join_instructions($$,$7);
	}
	;
init: 	local_variables { $$ = $1;}
		| assign TOKEN_SEMICOLON {$$ = $1;}
		;
unary_var: variable {$$ = $1;}
		|variable TOKEN_PLUSPLUS 
		{
			$$ = $1; 
			if($$.output.back() == TypeReal) 
				$$.ins.push_back(new InstructionPlusPlusReal());
			else if ($$.output.back() == TypeInteger) 
				$$.ins.push_back(new InstructionPlusPlusInteger());
			else program->actualRobot->error(@2,Robot::ErrorOperationNotSupported);
			$$.temp.push_back($1.temp.back());
		} 
		|variable TOKEN_MINUSMINUS 
		{
			 $$ = $1; 
			 if($$.output.back() == TypeReal)
				 $$.ins.push_back(new InstructionMinusMinusReal());
			else if ($$.output.back() == TypeInteger) 
				$$.ins.push_back(new InstructionMinusMinusInteger());
			else program->actualRobot->error(@2,Robot::ErrorOperationNotSupported);
			$$.temp.push_back($1.temp.back());
		}
		;
variable: TOKEN_IDENTIFIER 
		{
			$$ = ident_load(@1,program->actualRobot, $1);
			$$.temp.push_back(false);
		}
		|call_fce { $$ = $1; //TODO ak je to funkci a s navratovou hodnotou, kontrola vsetkych vetvi, ci obsahuju return; main je procedura:)
		}
		|variable TOKEN_DOT TOKEN_IDENTIFIER 
		{ 
			
			for ( size_t i =0; i<$$.output.back().nested_vars.size(); i++)
				if ($$.output.back().nested_vars[i].name == $3)
				{ 
					Create_type t = *$$.output.back().nested_vars[i].type; 
					$$.output.pop_back();
					$$.output.push_back(t);
					$$.ins.push_back(new InstructionLoad((int)i));
					$$.ins.push_back(new InstructionLoad());
					break;
				}
			$$.temp.push_back($1.temp.back());
		}
		|array
		;
		
array_access: TOKEN_LSBRA exps TOKEN_RSBRA 
		{ 
			$$.dimension = 0;
			$$.ins.clear(); //exps musia by integery
			for (size_t i =0; i< $2.ins.size(); i++)
			{
				if ($2.ins[i] == NULL)
				{
					$$.ins.push_back(new InstructionLoad());
					if ($2.temp[i])
						$$.ins.push_back(new InstructionRemoveTemp());
					$$.dimension++;
				}
				else
					$$.ins.push_back($2.ins[i]);
			}

		} //vezme zo stacku dve hodnoty, pouzije a na stack prihodi novu z tempu
		|array_access TOKEN_LSBRA exps TOKEN_RSBRA 
		{
			$$ = $1;
			for ( size_t i = 0; i < $3.ins.size();i++)
			{
				if ($3.ins[i] == NULL)
				{
					$$.ins.push_back(new InstructionLoad());
					if ($3.temp[i])
						$$.ins.push_back(new InstructionRemoveTemp());
					$$.dimension++;
				}
				else
					$$.ins.push_back($3.ins[i]);
			}
		} 
		;
exps: expression {$$ = $1;$$.ins.push_back(NULL);} //Hack
		| exps TOKEN_COMMA expression 
		{ 
			$1.ins.push_back(NULL);
			$$.ins = join_instructions($1.ins, $3.ins);
			$$.output = $1.output;
			for (size_t i =0; i<$1.output.size(); i++)
				$$.output.push_back($1.output[i]); //aj tak tu bude len jeden output, TODO
		}
		;
expression_base: unary_var { $$ = $1; }
		|number{$$ = $1;}
		|TOKEN_LPAR expression_bool TOKEN_RPAR {$$ = $2;}
		;
expression_mul:expression_base { $$ = $1; }
		|expression_mul TOKEN_OPER_MUL expression_base { 
			$$.clear();
			$$.ins = join_instructions($1.ins, $3.ins);
			if ($1.temp.back())
			{
				$$.ins.push_back(new InstructionRemoveTemp());
			}
			if ($3.temp.back())
				$$.ins.push_back(new InstructionRemoveTemp());
			Element e = operMul(@2, program->actualRobot, $2, $1.output.back(), $3.output.back());
			$$.ins = join_instructions($$.ins, e.ins);
			$$.output = e.output;
			$$.temp.push_back(true);
		}
		;
expression_add: expression_mul { $$ = $1;}
		|expression_add TOKEN_OPER_SIGNADD expression_mul
		{
			$$.clear();
			$$.ins = join_instructions($1.ins, $3.ins);
			if ($1.temp.back())
			{
				$$.ins.push_back(new InstructionRemoveTemp());
			}
			if ($3.temp.back())
				$$.ins.push_back(new InstructionRemoveTemp());
			Element e = (operAdd(@2, program->actualRobot,$2,$1.output.back(), $3.output.back()));
			$$.ins = join_instructions($$.ins, e.ins);
			$$.output = e.output;
			$$.temp.push_back(true);
		}
		;
expression:	expression_add { $$ = $1; }
		;
expression_bool_base: expression { $$ = $1;}
		|expression TOKEN_OPER_REL expression 
		{
			$$.clear();
			$$.ins = join_instructions($1.ins, $3.ins);
			if ($1.temp.back())
				$$.ins.push_back(new InstructionRemoveTemp());
			if ($3.temp.back())
				$$.ins.push_back(new InstructionRemoveTemp());
			Element e = operRel(@2,program->actualRobot,$2,$3.output.back(),$1.output.back());
			$$.ins = join_instructions($$.ins, e.ins);
			$$.output = e.output;
			$$.temp.push_back(true);
		}
		;
expression_bool_or: expression_bool_base {$$ = $1; }
		| expression_bool_or TOKEN_BOOL_OR expression_bool_base
		{
			$$.clear();
			$$.ins = join_instructions($1.ins, $3.ins);
			Element e = operOr(@2,program->actualRobot,$2,$1.output.back(),$3.output.back());
			$$.output = e.output; //aj tak by tu vzy mal byt integer
			$$.temp.push_back(true);
		}
		;
expression_bool:	expression_bool_or { $$ = $1;}
		| expression_bool TOKEN_BOOL_AND expression_bool_or 
		{
			$$.clear();
			$$.ins = join_instructions($1.ins, $3.ins); 
			if ($1.output.back().type == TypeReal) 
			{
				if ($1.temp.back())
				{
					$$.ins.push_back(new InstructionRemoveTemp());
				}
				$$.ins.push_back(new InstructionConversionToInt());
				$$.output.push_back(Create_type(TypeInteger));
			}
			else if ($1.output.back().type!= TypeInteger) 
				program->actualRobot->error(@2,Robot::ErrorConversionImpossible); 

			if ($3.output.back().type == TypeReal) 
			{
				if ($3.temp.back())
				{
					$$.ins.push_back(new InstructionRemoveTemp());
				}
				$$.ins.push_back(new InstructionConversionToInt());
				$$.output.push_back(Create_type(TypeInteger));
			}
			else if ($3.output.back().type!= TypeInteger) 
				program->actualRobot->error(@2,Robot::ErrorConversionImpossible); 
			$$.ins.push_back(new InstructionAnd);
			$$.temp.push_back(true);
		}
	;
%%

static void yyerror(unsigned *line, Robots* ctx, const char *message)
{
	printf("Syntax Error %s, line %d\n", message, *line);
}

