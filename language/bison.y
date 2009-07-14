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

%start program
%error-verbose
%pure-parser
%parse-param { Program *program }
%lex-param { Program *program }
%locations
%%

program	: global_variables declare_functions TOKEN_MAIN TOKEN_LPAR TOKEN_RPAR block_of_instructions // { add_main_code(program, block_of_instructions); }
	;
//OK, neprepaguje sa hore
global_variables:	/*	ziadne parametre	*/ 
	|global_variables local_variables /*Uz pridane parametre*/
	;
//OK
local_variables:  simple_type names TOKEN_SEMICOLON // { add(program,$2, $1); }
	| complex_type names TOKEN_SEMICOLON // { set_element_type(program, $3, $2); }
	;

simple_type: TOKEN_VAR_REAL
    	|TOKEN_VAR_INT
	|TOKEN_LOCATION
	|TOKEN_OBJECT
	;
complex_type: simple_type ranges
	|complex_type simple_type ranges
	;

ranges: TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA //{ $$.clear();$$.push_back($2); }
      	|ranges TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA //{ $1.push_back($3); $$ = $1; }
	;
names:	TOKEN_IDENTIFIER //{ $$.push_back($1); }
	|TOKEN_IDENTIFIER TOKEN_ASSIGN number { $$.push_back($1); } //TODO pridat instrukciu
     	|names TOKEN_COMMA TOKEN_IDENTIFIER //{ $1.push_back($2);$$ = $1; }
     	|names TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN number //{ $1.push_back($2);$$ = $1; } //TODO stejne ako predtym, instrukcia
     	|names TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN TOKEN_BEGIN values TOKEN_END //{ $1.push_back($2);$$ = $1; } //TODO stejne ako predtym, instrukcia
	;

values: number
      	| TOKEN_IDENTIFIER
	| values TOKEN_COMMA TOKEN_IDENTIFIER
	| values TOKEN_COMMA number
	;
declare_functions: /*	ziadne deklarovane funkcie	*/
	|declare_function_ //nic pridane, vyriesilo sa predtym
	;
function_header:TOKEN_FUNCTION TOKEN_IDENTIFIER //{ $$ = $2; }
	;

declare_function_:	function_header TOKEN_LPAR names TOKEN_RPAR block_of_instructions  //{ reg($1, $3, $5); } //register name, parameter_list, block
	|declare_function_ function_header TOKEN_LPAR names TOKEN_RPAR block_of_instructions //{ reg($2, $4, $6); } /* pozor! parameter uz definovany!*/
	|function_header TOKEN_LPAR TOKEN_RPAR block_of_instructions //{ reg($1, $4); } 
	|declare_function_ function_header TOKEN_LPAR TOKEN_RPAR block_of_instructions //{ reg($2, $5); } /* pozor! parameter uz definovany!*/
	;
number:		TOKEN_OPER_SIGNADD TOKEN_REAL 
      	|TOKEN_OPER_SIGNADD TOKEN_UINT 
      	|TOKEN_REAL
      	|TOKEN_UINT
	;
block_of_instructions: TOKEN_BEGIN TOKEN_END /* prazdno */ //{ $$.clear(); }
	|TOKEN_BEGIN TOKEN_SEMICOLON TOKEN_END  /* ziadna instrukcia */ //{ $$.clear(); }
	|TOKEN_BEGIN commands TOKEN_END /* neprazdne instrukcie*/ //{ $$ = $2; }
	;
commands: matched
	| commands matched
	| unmatched
	| commands unmatched
	;
command:	TOKEN_FOR TOKEN_LPAR init TOKEN_SEMICOLON expression_bool TOKEN_SEMICOLON simple_command TOKEN_RPAR block_of_instructions 
	|TOKEN_DO block_of_instructions TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR TOKEN_SEMICOLON
	|TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions
	|TOKEN_RETURN expression TOKEN_SEMICOLON
	|TOKEN_RETURN TOKEN_SEMICOLON
	|TOKEN_BREAK TOKEN_SEMICOLON
	|local_variables
	|simple_command TOKEN_SEMICOLON
      	;
simple_command:	assign 
	|variable TOKEN_PLUSPLUS 
	|variable TOKEN_MINUSMINUS 
	|variable 
	;
assign: variable_left TOKEN_ASSIGN variable
	|variable_left TOKEN_ASSIGN number //{ add_instuction(new IntructionLoad(variable_left)) } 
	;
variable_left: TOKEN_IDENTIFIER /* musi byt pole, location alebo nejaka ina shopna struktura */
	| TOKEN_IDENTIFIER array_access
	;

call_fce:	TOKEN_IDENTIFIER TOKEN_LPAR call_parameters TOKEN_RPAR
	;
call_parameters: expression
	 | /* ziadny parameter */
	 |call_parameters TOKEN_COMMA expression
	;
matched:TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE matched
	| command
	|block_of_instructions
	;
unmatched:	TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions
	 |TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR command 
	 |TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE unmatched
	;
init: 		TOKEN_VAR_INT TOKEN_IDENTIFIER TOKEN_ASSIGN expression
    	|TOKEN_VAR_REAL TOKEN_IDENTIFIER TOKEN_ASSIGN expression
	|TOKEN_IDENTIFIER TOKEN_ASSIGN expression
	|TOKEN_IDENTIFIER TOKEN_LSBRA expression TOKEN_RSBRA TOKEN_ASSIGN expression
    	;
variable: TOKEN_IDENTIFIER
	|TOKEN_IDENTIFIER array_access
	|call_fce
	|variable TOKEN_DOT TOKEN_IDENTIFIER //tuto musi byt funkcia, co odpoveda danemu identifierovi, napr see(3).IsMoving()
	|variable TOKEN_DOT call_fce
	;
array_access: TOKEN_LSBRA exps TOKEN_RSBRA
	|array_access TOKEN_LSBRA exps TOKEN_RSBRA
	;
exps: expression
	| exps TOKEN_COMMA expression
	;
expression_base: variable 
	|number
	|variable TOKEN_MINUSMINUS
	|variable TOKEN_PLUSPLUS
	|TOKEN_LPAR expression TOKEN_RPAR
	;
expression_mul:expression_base
	|expression_mul TOKEN_OPER_MUL expression_base
	;
expression_add: expression_mul
	|expression_add TOKEN_OPER_SIGNADD expression_mul
	;
expression:	expression_add
	;
expression_bool_base: expression
	|expression TOKEN_OPER_REL expression
	;
expression_bool_or: expression_bool_base
	| expression_bool_or TOKEN_BOOL_OR TOKEN_LPAR expression_bool TOKEN_RPAR
	;
expression_bool: expression_bool_or
	| expression_bool TOKEN_BOOL_AND expression_bool_or
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
	Node n(TypeUndefined);
	q.add(".", &n);//anonymna premenna
	yyparse(&q);
    	fclose(yyin);
	std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
	q.output(&q.defined);
	return 0;	
}
