%{
	#include "header1.h"
	#include "./tree/my_stack.h"
	#include <iostream>
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
%token TOKEN_FUNCTION
%token TOKEN_ARRAY
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_WHILE
%token TOKEN_DO
%token TOKEN_FOR
%token TOKEN_BOOL_AND
%token TOKEN_BOOL_OR
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

%type<idents> names
%type<type> simple_type
%type<type> complex_type
%type<type> ranges

%type<ident> function_header
%type<node> values

%type<instructions> commands
%type<instructions> matched
%type<instructions> unmatched
%type<instructions> local_variables

%start program
%error-verbose
%pure-parser
%parse-param { Program *program }
%lex-param { Program *program }
%locations
%%

//OK
program	: global_variables declare_functions TOKEN_MAIN TOKEN_LPAR TOKEN_RPAR block_of_instructions { reg_main(program, block_of_instructions); }
	;

//OK, neprepaguje sa hore
global_variables:	/*	ziadne parametre	*/ 
	|global_variables local_variables /*Uz pridane parametre*/
	;

//OK, instrukcie s tym uz nic nerobia
type:	  simple_type { $$ = $1;}
	| complex_type { $$ = $1; }
	;
//OK
local_variables:  type names TOKEN_SEMICOLON 
	       {  
			add_variables(program, $2, $1);
			for(int i =0; i< $2.size(); i++)
			{
				$$.push_back(new InstructionCreate($2[i]));
			}
		}
	;

//OK
simple_type: TOKEN_VAR_REAL { $$ = Create_type(TypeReal); }
    	|TOKEN_VAR_INT { $$ = Create_type(TypeInteger); }
	|TOKEN_LOCATION{ $$ = Create_type(TypeLocation); }
	|TOKEN_OBJECT{ $$ = Create_type(TypeObject); }
	;

//OK
complex_type: simple_type ranges { $$ = $2.composite($1); }
	;

//OK
ranges: TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { $$ = Create_type(TypeArray,$2); }
      	|ranges TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { Create_type t(TypeArray,$3); $$ = $1.composite(t); }
	;

//OK
names:	TOKEN_IDENTIFIER { $$.push_back($1); }
	|TOKEN_IDENTIFIER TOKEN_ASSIGN number { $$.push_back($1); } //TODO pridat instrukciu
     	|names TOKEN_COMMA TOKEN_IDENTIFIER { $1.push_back($3); $$ = $1; }
     	|names TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN number { $1.push_back($3);$$ = $1; } //TODO stejne ako predtym, instrukcia
     	|names TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN TOKEN_BEGIN values TOKEN_END { $1.push_back($3);$$ = $1; } //TODO stejne ako predtym, instrukcia
	;

//OK
values: number { $$.push_back(new InstructionLoad($1));}
      	| TOKEN_IDENTIFIER { $$.push_back(new InstructionLoad($1)); }
	| values TOKEN_COMMA TOKEN_IDENTIFIER {$1.push_back(new InstructionLoad($3));$$ = $1;}
	| values TOKEN_COMMA number {$1.push_back(new IntructionLoad($3));}
	;

//OK
declare_functions: /*	ziadne deklarovane funkcie	*/
	|declare_function_
	;

//OK
function_header:TOKEN_FUNCTION TOKEN_IDENTIFIER { $$ = $2; } //zatial nepotrebujeme vediet zanoraenie 
	;

//OK
declare_function_:	function_header TOKEN_LPAR names TOKEN_RPAR block_of_instructions  { reg($1, $3, $5);} //register name, parameter_list, block
	|declare_function_ function_header TOKEN_LPAR names TOKEN_RPAR block_of_instructions { reg($2, $4, $6); }
	|function_header TOKEN_LPAR TOKEN_RPAR block_of_instructions { reg($1, $4); } 
	|declare_function_ function_header TOKEN_LPAR TOKEN_RPAR block_of_instructions { reg($2,NULL, $5); }
	;

//OK
number:		TOKEN_OPER_SIGNADD TOKEN_REAL { if (TOKEN_OPER_SIGNADD == OperationMinus ) $2*=-1; $$.push_back(new IntructionLoad($2)); } //load realu do 
      	|TOKEN_OPER_SIGNADD TOKEN_UINT { if (TOKEN_OPER_SIGNADD == OperationMinus) {$2*=-1;} $$.push_back(new IntructionLoad($2)); } 
      	|TOKEN_REAL { $$.push_back(new IntructionLoad($1)); } 
      	|TOKEN_UINT { $$.push_back(new IntructionLoad($1)); } 
	;

//OK, niet co zkazit
block_of_instructions: TOKEN_BEGIN TOKEN_END { $$.clear(); }
	|TOKEN_BEGIN TOKEN_SEMICOLON TOKEN_END  { $$.clear(); }
	|TOKEN_BEGIN commands TOKEN_END { $$ = $2; }
	;

//OK
commands: matched {$$ = $1;}
	| commands matched { $$ = join_instructions($1, $2); }
	| unmatched {$$ = $1;}
	| commands unmatched { $$ = join_instructions($1, $2); }
	;

//OK
command:	TOKEN_FOR TOKEN_LPAR init TOKEN_SEMICOLON expression_bool TOKEN_SEMICOLON simple_command TOKEN_RPAR block_of_instructions 
       		{ $9 = join_instructions($9, $7); 
		  $3.push_back(new InstructionMustJump($9.size())); 
		  $5.push_back(new InstructionJump(-1*$9.size()-$5.size()));
		  $$ = join_instructions($3,$9);
		}
	|TOKEN_DO block_of_instructions TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR TOKEN_SEMICOLON 
		{ $$ = join_instructions($2,$5); 
		  $$.push_back(new InstructionJump(-1*$$.size())); 
		}
	|TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions
		{
			$3 = join_instructions($5,$3);
			$$.push_back(new InstructionMustJump($3.size());
			$$ = join_instructions($$, $3);
			$$.push_back(new InstructionJump(-1*$$.size()));
		}
	|TOKEN_RETURN expression TOKEN_SEMICOLON
		{
			$$ = $2;
			$$.push_back(new InstructionStore());
		}
	|TOKEN_RETURN TOKEN_SEMICOLON {} //v node zostane predchadzajuca hodnota
	|TOKEN_BREAK TOKEN_SEMICOLON 
		{
			$$.push_back(new InstructionSkip());
		}
	|local_variables { $$ = $1; } //deklarovanie novej premennej
	|simple_command TOKEN_SEMICOLON {$$ = $1;}
      	;
simple_command:	assign {$$ = $1;}
	|variable TOKEN_PLUSPLUS { $$.push_back(new IntructionLoad($1));$$.push_back(new IntructionPlusPlus());} //switch type & load + instruction ++ 
	|variable TOKEN_MINUSMINUS { $$.push_back(new IntructionLoad($1)); $$.push_back(new IntructionMinusMinus);}
	|variable { $$ = $1; } 
	;
assign: variable_left TOKEN_ASSIGN expression { $$ = $1; $$.push_back(new IntructionStore()) }
	;

//OK
variable_left: TOKEN_IDENTIFIER { $$.push_back(new InstructionLoad($1));}
	| TOKEN_IDENTIFIER array_access { $$.push_back(new InstructionLoad($1)); $$=join_instructions($$, $2); }
	;

call_fce:	TOKEN_IDENTIFIER TOKEN_LPAR call_parameters TOKEN_RPAR
	;
call_parameters: expression
	 | /* ziadny parameter */
	 |call_parameters TOKEN_COMMA expression
	;
matched:TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE matched 
       		{ $5.push_back(new InstructionMustJump($7.size()));
		  $3.push_back(new InstructionJump(1,$5.size()));join_instructions($3,$);}
	| command {$$ = $1;}
	|block_of_instructions { $$ = $1;}
	;
unmatched:	TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions {}
	 |TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR command 
	 |TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE unmatched
	;
init: 		TOKEN_VAR_INT TOKEN_IDENTIFIER TOKEN_ASSIGN expression
    	|TOKEN_VAR_REAL TOKEN_IDENTIFIER TOKEN_ASSIGN expression
	|TOKEN_IDENTIFIER TOKEN_ASSIGN expression
	|TOKEN_IDENTIFIER TOKEN_LSBRA expression TOKEN_RSBRA TOKEN_ASSIGN expression
    	;
variable: TOKEN_IDENTIFIER { $$.push_back(new InstructionLoad($1));}
	|TOKEN_IDENTIFIER array_access { $$.push_back(new InstructionLoad($1)); $$=join_instructions($$,$1);}
	|call_fce {$$ = $1;}
	|variable TOKEN_DOT TOKEN_IDENTIFIER {}//tuto musi byt funkcia, co odpoveda danemu identifierovi, napr see(3).IsMoving()
	|variable TOKEN_DOT call_fce
	;
array_access: TOKEN_LSBRA exps TOKEN_RSBRA { $$ = $3;}
	|array_access TOKEN_LSBRA exps TOKEN_RSBRA { $$ = join_instructions($1, $3);  
	;
//OK
exps: expression {$$ = $1;}
	| exps TOKEN_COMMA expression { $$ = join_instructions($1, $3); }
	;
//OK
expression_base: variable { $$ = $1;}
	|number{$$ = $1;}
	|variable TOKEN_MINUSMINUS {$$ = $1; $$.push_back(new InstructionMinusMinus());}
	|variable TOKEN_PLUSPLUS {$$ = $1; $$.push_back(new InstructionPlusPlus();)}
	|TOKEN_LPAR expression TOKEN_RPAR {$$ = $2;}
	;
//OK
expression_mul:expression_base { $$ = $1; }
	|expression_mul TOKEN_OPER_MUL expression_base { $$ = join_instructions($1, $3); $$.push_back(operMul($2)); }
	;
//OK
expression_add: expression_mul { $$ = $1; }
	|expression_add TOKEN_OPER_SIGNADD expression_mul { $$ = join_instructions($1, $3); $$.push_back(operAdd($2)); }
	;
//OK
expression:	expression_add { $$ = $1; }
	;
//OK
expression_bool_base: expression { $$ = $1;}
	|expression TOKEN_OPER_REL expression { $$ = join_instructions($1,$3); $$.push_back(operRel($2)); }
	;
//OK
expression_bool_or: expression_bool_base {$$ = $1; }
	| expression_bool_or TOKEN_BOOL_OR TOKEN_LPAR expression_bool TOKEN_RPAR {$$ = join_instructions($1,$3); $$.push_back((operOr($2)));}
	;
//OK
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
	return 0;	
}
