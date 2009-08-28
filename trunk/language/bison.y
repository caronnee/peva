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
%type<type> ranges
%type<type> type
%type<type> return_type

%type<ident> function_header
%type<entries> parameters

%type<instructions> commands
%type<instructions> command
%type<instructions> matched
%type<instructions> unmatched
%type<instructions> local_variables
%type<instructions> variable
%type<instructions> variable_left
%type<instructions> block_of_instructions 
%type<instructions> values
%type<instructions> number
%type<instructions> init
%type<instructions> expression_bool
%type<instructions> expression
%type<instructions> exps
%type<instructions> expression_base
%type<instructions> expression_mul
%type<instructions> expression_add
%type<instructions> expression_bool_base
%type<instructions> expression_bool_or
%type<instructions> assign
%type<instructions> simple_command
%type<instructions> call_fce
%type<instructions> call_parameters
%type<instructions> array_access
%type<instructions> declare_functions
%type<instructions> declare_function_
%type<instructions> global_variables
%type<instructions> command_var

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
targets: /* default target */
      	|targets TOKEN_KILLED TOKEN_OPER_REL TOKEN_UINT
	|targets TOKEN_VISIT TOKEN_LPAR places TOKEN_RPAR
	|targets TOKEN_VISIT_SEQUENCE TOKEN_LPAR places TOKEN_RPAR
	;

places: TOKEN_LSBRA TOKEN_UINT TOKEN_COMMA TOKEN_UINT TOKEN_RSBRA { $$.push_back(Position($2,$4)); }
	| places TOKEN_LSBRA TOKEN_UINT TOKEN_COMMA TOKEN_UINT TOKEN_RSBRA {$$ = $1; $$.push_back(Position($3,$5));}
	| TOKEN_START TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA /* START[8] */ { $$.push_back(program->get_start_position($3));}
	| places TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA // START[8]
	;

options: // defaultne opsny
       | options TOKEN_OPTION TOKEN_ASSIGN TOKEN_UINT { program->set($2,$4);}
	;
global_variables:	/*	ziadne parametre	*/ { $$.clear(); }
	|global_variables local_variables { $$=join_instructions($1,$2);}
	;

type:	  simple_type { $$ = $1;}
	| complex_type { $$ = $1; }
	; //vsetky typy, ale moze premenna nadobudnut

local_variables:  type names TOKEN_SEMICOLON 
	       {  
			for(int i =0; i< $2.size(); i++)
			{
				Node * n = program->actualRobot->add($2[i].id, $1); //pridali sme do stromu pre neskorsie vyhladavanie
				$$.push_back(new InstructionCreate(program->actualRobot->find_var($2[i].id))); 
				if ($2[i].default_set){ //ak bola zadana defaultna hodnota 
					if (n->nested == Local) //toto  je vnode, lebo sa to pre premennu nemeni
						$$.push_back(new InstructionLoadLocal(n));
					else
						$$.push_back(new InstructionLoadGlobal(n));
					$$ = join_instructions($$, $2[i].ins);
					$$.push_back(new InstructionStore());
					}
			}
		}
	;

//OK
simple_type: TOKEN_VAR_REAL { $$ = Create_type(TypeReal); }
    	|TOKEN_VAR_INT { $$ = Create_type(TypeInteger); }
	|TOKEN_LOCATION{ $$ = Create_type(TypeLocation); }
	|TOKEN_OBJECT{ $$ = Create_type(TypeObject); }
	;

complex_type: simple_type ranges { $$ = $2.composite($1); }
	;

ranges: TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { $$ = Create_type(TypeArray,$2); }
      	|ranges TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { Create_type t(TypeArray,$3); $$ = $1.composite(t); }
	;

names:	TOKEN_IDENTIFIER { $$.push_back(Constr($1)); }
	|TOKEN_IDENTIFIER TOKEN_ASSIGN expression { $$.push_back(Constr($1,$3)); }
     	|names TOKEN_COMMA TOKEN_IDENTIFIER { $1.push_back(Constr($3)); $$ = $1; }
     	|names TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN expression { $1.push_back(Constr($3,$5));$$ = $1; } //TODO stejne ako predtym, instrukcia
     	|names TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN TOKEN_BEGIN values TOKEN_END { $1.push_back($3);$$ = $1; } //TODO stejne ako predtym, instrukcia
	;

values: number { $$=$1;}
      	| TOKEN_IDENTIFIER { 
				Node *n = program->actualRobot->find_var($1); 
				if (n == NULL)
					{
						std::cout << "nenaslo mi premennu" <<std::endl;
					}
				if(n->nested == Local)
					$$.push_back(new InstructionLoadLocal(n));
				else  
					$$.push_back(new InstructionLoadGlobal(n));
			}
	| values TOKEN_COMMA TOKEN_IDENTIFIER {$1.push_back(instruction_load(program->actualRobot, $3));$$ = $1;}
	| values TOKEN_COMMA number {$$ = join_instructions($1, $3);}
	;

declare_functions: /*	ziadne deklarovane funkcie	*/ { $$.clear(); program->actualRobot->enter("main", Create_type(TypeVoid)); }
	|declare_function_ { $$ = $1; program->actualRobot->enter("main", Create_type(TypeVoid));}
	;

function_header:return_type TOKEN_FUNCTION TOKEN_IDENTIFIER { $$ = $3; program->actualRobot->enter($3, $1); } //zatial nepotrebujeme vediet zanoraenie , enter loop pre returny
	;

return_type:	type { $$ = $1; }
	|TOKEN_VOID { $$ = Create_type(TypeVoid); }
	;

parameters:	type TOKEN_IDENTIFIER { $$.push_back(Parameter_entry($2,PARAMETER_BY_VALUE, program->actualRobot->add($2, $1))); }
	| parameters TOKEN_COMMA type TOKEN_IDENTIFIER { $$ = $1; $$.push_back(Parameter_entry($4,PARAMETER_BY_VALUE,program->actualRobot->add($4, $3)));}
	;

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

number:		TOKEN_OPER_SIGNADD TOKEN_REAL { if (TOKEN_OPER_SIGNADD == OperationMinus ) {$2*=-1;} $$.push_back(new InstructionLoad($2)); } 
      	|TOKEN_OPER_SIGNADD TOKEN_UINT { if (TOKEN_OPER_SIGNADD == OperationMinus) {$2*=-1;} $$.push_back(new InstructionLoad($2)); } 
      	|TOKEN_REAL { $$.push_back(new InstructionLoad($1)); } 
      	|TOKEN_UINT { $$.push_back(new InstructionLoad($1)); } 
	;

begin:	TOKEN_BEGIN { program->actualRobot->core->depth++; }
     	;

end:	TOKEN_END { program->actualRobot->core->depth--; }
   	;

block_of_instructions: begin end { $$.push_back(new InstructionBegin()); $$.push_back(new InstructionEndBlock());}
	|begin TOKEN_SEMICOLON end  { $$.clear();$$.push_back(new InstructionBegin()); $$.push_back(new InstructionEndBlock()); }
	|begin commands end { $$.push_back(new InstructionBegin()); $$ = join_instructions($$, $2);$$.push_back(new InstructionEndBlock()); }
	;

commands: matched {$$ = $1;}
	| commands matched { $$ = join_instructions($1, $2); }
	| unmatched {$$ = $1;}
	| commands unmatched { $$ = join_instructions($1, $2); }
	;
forcycle:	TOKEN_FOR { program->actualRobot->enter_loop();}
	;
do_cycle:	TOKEN_DO { program->actualRobot->enter_loop();}
	;
while_cycle:	TOKEN_WHILE { program->actualRobot->enter_loop();}
	;
command:	forcycle TOKEN_LPAR init expression_bool TOKEN_SEMICOLON simple_command TOKEN_RPAR block_of_instructions 
       		{ 
		  $8 = join_instructions($8, $6); 
		  $3.push_back(new InstructionMustJump($8.size())); 
		  $4.push_back(new InstructionJump(-1*$8.size()-$4.size()-1,0));
		  $8 = join_instructions($8,$4);
		  $$ = join_instructions($3,$8);
		  set_breaks(program->actualRobot, $$);
		  program->actualRobot->end_loop();
		}
	|do_cycle block_of_instructions TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR TOKEN_SEMICOLON 
		{ $$ = join_instructions($2,$5); 
		  $$.push_back(new InstructionJump(-1*$$.size()-1,0));
		  set_breaks(program->actualRobot, $$);
		  program->actualRobot->end_loop();
		}
	|while_cycle TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions
		{
			$$.push_back(new InstructionMustJump($5.size()));
			$3 = join_instructions($5,$3);
			$$ = join_instructions($$, $3);
			$$.push_back(new InstructionJump(-1*$$.size(),0));
		  	set_breaks(program->actualRobot, $$);
		  	program->actualRobot->end_loop();
		}
	|TOKEN_RETURN expression TOKEN_SEMICOLON
		{
			$$ = $2;
			std::cout << program->actualRobot->core->nested_function << "-----"<< std::endl;
			getc(stdin);
			$$.insert($$.begin(), new InstructionLoadLocal(program->actualRobot->core->nested_function->return_var));
			$$.push_back(new InstructionStore()); //budu vedla seba, takze by to malo prejst
			$$.push_back(new InstructionReturn(program->actualRobot->core->depth));
		}
	|TOKEN_RETURN TOKEN_SEMICOLON {$$.push_back(new InstructionReturn(program->actualRobot->core->depth));} //v node zostane predchadzajuca hodnota
	|TOKEN_BREAK TOKEN_SEMICOLON 
		{
			std::cout << "Adding break to in depth" <<program->actualRobot->core->depth << std::endl;
			getc(stdin);
			$$.push_back(new InstructionBreak(program->actualRobot->last_loop_number, program->actualRobot->core->depth));
		}
	|simple_command TOKEN_SEMICOLON {$$ = $1;}
      	;

command_var: local_variables { $$ = $1;}
	| command { $$ = $1;}
	;
simple_command:	assign {$$ = $1;}
	|variable TOKEN_PLUSPLUS { $$.push_back(new InstructionPlusPlus());} 
	|variable TOKEN_MINUSMINUS { $$.push_back(new InstructionMinusMinus());}
	|variable { $$ = $1; } 
	;

assign: variable_left TOKEN_ASSIGN expression { $$ = join_instructions($1, $3); $$.push_back(new InstructionStore()) }
	;

variable_left: TOKEN_IDENTIFIER { $$.push_back(instruction_load(program->actualRobot, $1));}
	| TOKEN_IDENTIFIER array_access { $$.push_back(instruction_load(program->actualRobot, $1)); $$ = join_instructions($$, $2); }
	;

call_fce:	TOKEN_IDENTIFIER TOKEN_LPAR call_parameters TOKEN_RPAR { $$ = $3; $$.push_back(new Call(program->actualRobot->find_f($1)));} //TODO check parameters
	|TOKEN_OBJECT_FEATURE TOKEN_LPAR call_parameters TOKEN_RPAR { $$ = $3;$$.push_back(feature($1));}
	;

call_parameters: expression {$$ = $1;} //loaded
	 | /* ziadny parameter */ {$$.clear();}
	 |call_parameters TOKEN_COMMA expression {$$ = join_instructions($3,$1); }
	;

matched:TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE matched 
       		{
		  $5.push_back(new InstructionMustJump($7.size()));
		  $3.push_back(new InstructionJump(0,$5.size()));
		  $$ =join_instructions($3,$5);
		  $$ =join_instructions($$,$7);
		}
	| command_var {$$ = $1;}
	|block_of_instructions { $$ = $1;}
	;

unmatched:	TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions {$3.push_back(new InstructionJump(0,$5.size()));$$ = join_instructions($3,$5);}
	 |TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR command {$3.push_back(new InstructionJump(0,$5.size()));$$ = join_instructions($3,$5);}

	 |TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE unmatched 
		{
		  $5.push_back(new InstructionMustJump($7.size()));
		  $3.push_back(new InstructionJump(0,$5.size()));
		  $$ = join_instructions($3,$5);
		  $$ = join_instructions($$,$7);
		}
	;

init: 	local_variables { $$ = $1;}
	| assign TOKEN_SEMICOLON {$$ = $1;}
	;

variable: TOKEN_IDENTIFIER { $$.push_back(instruction_load(program->actualRobot, $1));}
	|TOKEN_IDENTIFIER array_access { $$.push_back(instruction_load(program->actualRobot, $1)); $$=join_instructions($$,$2);}
	|call_fce {$$ = $1;} //TODO ak je to funkci a s navratovou hodnotou, kontrola vsetkych vetvi, ci obsahuju return; main je procedura:)
	|variable TOKEN_DOT call_fce //{ if ($1.output.has_function($3.name)) join, else error} //znici value, z ktoreho to bolo volane a zavola clensku funkciu 
	|variable TOKEN_DOT TOKEN_IDENTIFIER //{}
	;

array_access: TOKEN_LSBRA exps TOKEN_RSBRA { $$ = $2; $$.push_back(new InstructionLoad());} //vezme zo stacku dve a odnoty pouzije, TODO check real
	|array_access TOKEN_LSBRA exps TOKEN_RSBRA { $$ = join_instructions($1, $3); $$.push_back(new InstructionLoad());}  
	;

exps: expression {$$ = $1;}
	| exps TOKEN_COMMA expression { $$ = join_instructions($1, $3); }
	;

expression_base: variable { $$ = $1;}
	|number{$$ = $1;}
	|variable TOKEN_MINUSMINUS {$$ = $1; $$.push_back(new InstructionMinusMinus());}
	|variable TOKEN_PLUSPLUS {$$ = $1; $$.push_back(new InstructionPlusPlus());}
	|TOKEN_LPAR expression TOKEN_RPAR {$$ = $2;}
	;

expression_mul:expression_base { $$ = $1; }
	|expression_mul TOKEN_OPER_MUL expression_base { $$ = join_instructions($1, $3); $$.push_back(operMul($2)); }
	;

expression_add: expression_mul { $$ = $1; }
	|expression_add TOKEN_OPER_SIGNADD expression_mul { $$ = join_instructions($1, $3); $$.push_back(operAdd($2)); }
	;

expression:	expression_add { $$ = $1; }
	;

expression_bool_base: expression { $$ = $1;}
	|expression TOKEN_OPER_REL expression { $$ = join_instructions($1,$3); $$.push_back(operRel($2)); }
	;

expression_bool_or: expression_bool_base {$$ = $1; }
	| expression_bool_or TOKEN_BOOL_OR TOKEN_LPAR expression_bool TOKEN_RPAR {$$ = join_instructions($1,$4); $$.push_back((operOr($2)));}
	;

expression_bool: expression_bool_or { $$ = $1; }
	| expression_bool TOKEN_BOOL_AND expression_bool_or { $$ = join_instructions($1,$3); $$.push_back(new InstructionBinaryAnd()); }
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
	std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
/*	q.actualRobot->output(&q.actualRobot->defined);
	for (int i =0; i<q.actualRobot->instructions.size(); i++)
		std::cout << q.actualRobot->instructions[i]->name_<<std::endl;
	q.actualRobot->save_to_xml();
	std::cout << "haho!" << std::endl;
   	q.actualRobot->execute();
*/
	return 0;	
}
