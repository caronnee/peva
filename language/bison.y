%{
	#include <iostream>
	#include "header1.h"
	#include "program.h"
	#include "parser_functions.h"

	#define YYSTYPE Lval 
	#define YYLTYPE unsigned
	#define YYLLOC_DEFAULT(cur, rhs, n)	do { if(n) (cur)=(rhs)[1]; else (cur)=(rhs)[0]; } while(0)

	#define YYERROR_VERBOSE 1		
	static void yyerror(YYLTYPE *line, Program* ctx, const char *m);

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

%start program
%error-verbose
%pure-parser
%parse-param { Program *program }
%lex-param { Program *program }
%locations
%%

program	: global_variables declare_functions TOKEN_MAIN TOKEN_LPAR TOKEN_RPAR block_of_instructions 
		{ 
	  std::vector<Parameter_entry> p;
	  program->add_global($1);
	  reg(program, Create_type(TypeVoid),"main", p, $6); 
		} //skonsoliduje vsetky instrukcie, co sa doteraz vygenerovali
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
				Node * n = program->add($2[i].id, $1); //pridali sme do stromu pre neskorsie vyhladavanie
				$$.push_back(new InstructionCreate(program->find_var($2[i].id))); //treba este aktivovat, na to sluzi tato instrukcia
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
				Node *n = program->find_var($1); 
				if (n == NULL)
					{
						std::cout << "aekfuhak" <<std::endl;
					}
				if(n->nested == Local)
					$$.push_back(new InstructionLoadLocal(n));
				else  
					$$.push_back(new InstructionLoadGlobal(n));
			}
	| values TOKEN_COMMA TOKEN_IDENTIFIER {$1.push_back(instruction_load(program, $3));$$ = $1;}
	| values TOKEN_COMMA number {$$ = join_instructions($1, $3);}
	;

declare_functions: /*	ziadne deklarovane funkcie	*/ { $$.clear(); program->enter("main"); }
	|declare_function_ { $$ = $1; program->enter("main");}
	;

function_header:TOKEN_FUNCTION TOKEN_IDENTIFIER { $$ = $2; program->enter($2); } //zatial nepotrebujeme vediet zanoraenie 
	;

return_type:	type { $$ = $1; }
	|TOKEN_VOID { $$ = Create_type(TypeVoid); }
	;

parameters:	type TOKEN_IDENTIFIER { $$.push_back(Parameter_entry($2,PARAMETER_BY_VALUE, $1)); program->add($2, $1); }
	| parameters TOKEN_COMMA type TOKEN_IDENTIFIER { $$ = $1; $$.push_back(Parameter_entry($4,PARAMETER_BY_VALUE,$3));program->add($4, $3);}
	;
declare_function_:	return_type function_header TOKEN_LPAR parameters TOKEN_RPAR block_of_instructions  { reg(program,$1,$2, $4, $6);program->leave();} 
	|declare_function_ return_type function_header TOKEN_LPAR parameters TOKEN_RPAR block_of_instructions { reg(program,$2,$3,$5,$7); program->leave();}
	|return_type function_header TOKEN_LPAR TOKEN_RPAR block_of_instructions {std::vector<Parameter_entry> a; reg(program,$1, $2, a, $5); program->leave();} 
	|declare_function_ return_type function_header TOKEN_LPAR TOKEN_RPAR block_of_instructions {std::vector<Parameter_entry> a; reg(program, $2, $3, a, $6);program->leave(); }
	;

number:		TOKEN_OPER_SIGNADD TOKEN_REAL { if (TOKEN_OPER_SIGNADD == OperationMinus ) {$2*=-1;} $$.push_back(new InstructionLoad($2)); } //load realu do 
      	|TOKEN_OPER_SIGNADD TOKEN_UINT { if (TOKEN_OPER_SIGNADD == OperationMinus) {$2*=-1;} $$.push_back(new InstructionLoad($2)); } 
      	|TOKEN_REAL { $$.push_back(new InstructionLoad($1)); } 
      	|TOKEN_UINT { $$.push_back(new InstructionLoad($1)); } 
	;

block_of_instructions: TOKEN_BEGIN TOKEN_END { $$.clear(); }
	|TOKEN_BEGIN TOKEN_SEMICOLON TOKEN_END  { $$.clear(); }
	|TOKEN_BEGIN commands TOKEN_END { $$.push_back(new InstructionBegin()); $$ = join_instructions($$, $2);$$.push_back(new InstructionEndBlock()); }
	;

commands: matched {$$ = $1;}
	| commands matched { $$ = join_instructions($1, $2); }
	| unmatched {$$ = $1;}
	| commands unmatched { $$ = join_instructions($1, $2); }
	;
forcycle:	TOKEN_FOR { program->enter_loop();}
	;
do_cycle:	TOKEN_DO { program->enter_loop();}
	;
while_cycle:	TOKEN_WHILE { program->enter_loop();}
	;
command:	forcycle TOKEN_LPAR init TOKEN_SEMICOLON expression_bool TOKEN_SEMICOLON simple_command TOKEN_RPAR block_of_instructions 
       		{ 
		  $9 = join_instructions($9, $7); 
		  $3.push_back(new InstructionMustJump($9.size())); 
		  $5.push_back(new InstructionJump(-1*$9.size()-$5.size(),1));
		  $9 = join_instructions($9,$5);
		  $$ = join_instructions($3,$9);
		  set_breaks(program, $5);
		  program->end_loop();
		}
	|do_cycle block_of_instructions TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR TOKEN_SEMICOLON 
		{ $$ = join_instructions($2,$5); 
		  $$.push_back(new InstructionJump(-1*$$.size(),1)); 
		  program->end_loop();
		}
	|while_cycle TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions
		{
			$$.push_back(new InstructionMustJump($3.size()));
			$3 = join_instructions($5,$3);
			$$ = join_instructions($$, $3);
			$$.push_back(new InstructionJump(-1*$$.size(),1));
		  	program->end_loop();
		}
	|TOKEN_RETURN expression TOKEN_SEMICOLON
		{
			$$ = $2;
			$$.push_back(new InstructionStore()); //budu vedla seba, takze by to malo prejst
			$$.push_back(new InstructionReturn());
		}
	|TOKEN_RETURN TOKEN_SEMICOLON {$$.push_back(new InstructionReturn());} //v node zostane predchadzajuca hodnota
	|TOKEN_BREAK TOKEN_SEMICOLON 
		{
			$$.push_back(new InstructionBreak(program->last_loop_number));
		}
	|local_variables { $$ = $1; } //deklarovanie novej premennej
	|simple_command TOKEN_SEMICOLON {$$ = $1;}
      	;

simple_command:	assign {$$ = $1;}
	|variable TOKEN_PLUSPLUS { $$.push_back(new InstructionPlusPlus());} 
	|variable TOKEN_MINUSMINUS { $$.push_back(new InstructionMinusMinus());}
	|variable { $$ = $1; } 
	;

assign: variable_left TOKEN_ASSIGN expression { $$ = join_instructions($1, $3); $$.push_back(new InstructionStore()) }
	;

variable_left: TOKEN_IDENTIFIER { $$.push_back(instruction_load(program, $1));}
	| TOKEN_IDENTIFIER array_access { $$.push_back(instruction_load(program, $1)); $$ = join_instructions($$, $2); }
	;

call_fce:	TOKEN_IDENTIFIER TOKEN_LPAR call_parameters TOKEN_RPAR { $$ = $3; $$.push_back(new Call(program->find_f($1)));} //TODO check parameters
	|TOKEN_OBJECT_FEATURE TOKEN_LPAR call_parameters TOKEN_RPAR { $$ = $3;$$.push_back(feature($1));}
	;

call_parameters: expression {$$ = $1} //loaded
	 | /* ziadny parameter */ {$$.clear();}
	 |call_parameters TOKEN_COMMA expression {$$ = join_instructions($1,$3); }
	;

matched:TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE matched 
       		{
		  $5.push_back(new InstructionMustJump($7.size()));
		  $3.push_back(new InstructionJump(1,$5.size()));
		  $$ =join_instructions($3,$5);
		  $$ =join_instructions($$,$7);
		}
	| command {$$ = $1;}
	|block_of_instructions { $$ = $1;}
	;

unmatched:	TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions {$3.push_back(new InstructionJump(1,$5.size()));$$ = join_instructions($3,$5);}
	 |TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR command {$3.push_back(new InstructionJump(1,$5.size()));$$ = join_instructions($3,$5);}

	 |TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE unmatched 
		{
		  $5.push_back(new InstructionMustJump($7.size()));
		  $3.push_back(new InstructionJump(1,$5.size()));
		  $$ = join_instructions($3,$5);
		  $$ = join_instructions($$,$7);
		}
	;

init: 	local_variables { $$ = $1;}
	| assign    {$$ = $1;}
	;

variable: TOKEN_IDENTIFIER { $$.push_back(instruction_load(program, $1));}
	|TOKEN_IDENTIFIER array_access { $$.push_back(instruction_load(program, $1)); $$=join_instructions($$,$2);}
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

extern FILE * yyin;

static void yyerror(unsigned *line,Program* ctx, const char *message)
{
	printf("Co to, co to? %s, line %d\n", message, *line);
}

int main(int argc, char ** argv)
{
	if(argc<2)
    	{
		puts("Kde mam vstup, ha?\n");
		return 16;
    	}

	if((yyin=fopen(argv[1], "r"))==0)
    	{
		puts("Vstup je divny\n");
		return 16;
    	}

	Program q;
	Create_type t;
	q.add(".", t);//anonymna premenna
	yyparse(&q);
    	fclose(yyin);
	std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
	q.output(&q.defined);
	for (int i =0; i<q.instructions.size(); i++)
		std::cout << q.instructions[i]->name_<<std::endl;
	q.save_to_xml();
	return 0;	
}
