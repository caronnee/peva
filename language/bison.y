%{
	#include "header1.h"
	#include <stdio.h>

	#define YYSTYPE Lval 
	#define YYLTYPE unsigned
	#define YYLLOC_DEFAULT(cur, rhs, n)	do { if(n) (cur)=(rhs)[1]; else (cur)=(rhs)[0]; } while(0)
	#define YYERROR_VERBOSE 1
    static void yyerror( const char *m);

%}

/* keywords */
%token TOKEN_MAIN
%token TOKEN_POINT
%token TOKEN_VAR
%token TOKEN_FUNCTION
%token TOKEN_ARRAY
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_WHILE
%token TOKEN_DO
%token TOKEN_FOR
%token TOKEN_BOOL_AND
%token TOKEN_BOOL_OR
%token TOKEN_NOT
%token TOKEN_RETURN
%token TOKEN_BREAK

/* literals */
%token TOKEN_IDENTIFIER
%token TOKEN_UINT
%token TOKEN_REAL

/* delimiters */
%token TOKEN_SEMICOLON
%token TOKEN_DOT
%token TOKEN_COMMA
%token TOKEN_EQ
%token TOKEN_LPAR
%token TOKEN_RPAR
%token TOKEN_LSBRA
%token TOKEN_RSBRA
%token TOKEN_ASSIGN
%token TOKEN_BEGIN
%token TOKEN_END
%token TOKEN_PLUSPLUS
%token TOKEN_MINUSMINUS

/* group tokens */
%token TOKEN_OPER_REL
%token TOKEN_OPER_SIGNADD
%token TOKEN_OPER_MUL

%start program
%error-verbose
%pure-parser
%locations

%%

program	: params declare_functions TOKEN_MAIN TOKEN_LPAR TOKEN_RPAR block_of_instructions
	;
params:	/*	ziadne parametre	*/
      	| params TOKEN_VAR names TOKEN_SEMICOLON
	| params TOKEN_ARRAY TOKEN_POINT array_names TOKEN_SEMICOLON
	| params TOKEN_ARRAY TOKEN_VAR array_names TOKEN_SEMICOLON
	| params TOKEN_POINT names TOKEN_SEMICOLON
	;
array_names: TOKEN_IDENTIFIER
	|array_names TOKEN_COMMA TOKEN_IDENTIFIER
	|TOKEN_IDENTIFIER TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA /*pre definovanie kolko pola bude volneho, aby sa nezahltila pamat*/
	|array_names TOKEN_IDENTIFIER TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA
	;
names:	TOKEN_IDENTIFIER
	|TOKEN_IDENTIFIER TOKEN_ASSIGN number
     	|names TOKEN_COMMA TOKEN_IDENTIFIER 
     	|names TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN number 
	;
declare_functions: /*	ziadne deklarovane funkcie	*/
	|d_f
	;
d_f:	TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAR names TOKEN_RPAR block_of_instructions /* pozor! parameter uz definovany!*/
	|d_f TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAR names TOKEN_RPAR block_of_instructions /* pozor! parameter uz definovany!*/
	|TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAR TOKEN_RPAR block_of_instructions /* pozor! parameter uz definovany!*/
	|d_f TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAR TOKEN_RPAR block_of_instructions /* pozor! parameter uz definovany!*/
	;
number:TOKEN_OPER_SIGNADD TOKEN_REAL
      |TOKEN_OPER_SIGNADD TOKEN_UINT
      |TOKEN_REAL
      |TOKEN_UINT
	;
block_of_instructions: TOKEN_BEGIN TOKEN_END /* prazdno */ 
	|TOKEN_BEGIN TOKEN_SEMICOLON TOKEN_END  /* ziadna instrukcia */
	|TOKEN_BEGIN commands TOKEN_END /* neprazdne instrukcie*/
	;
commands: matched
	| commands matched
	| unmatched
	| commands unmatched
	;
command:TOKEN_FOR TOKEN_LPAR init TOKEN_SEMICOLON expression_bool TOKEN_SEMICOLON command TOKEN_RPAR block_of_instructions 
	|TOKEN_DO block_of_instructions TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR TOKEN_SEMICOLON
	|TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions
	|TOKEN_RETURN expression TOKEN_SEMICOLON
	|TOKEN_BREAK TOKEN_SEMICOLON
	|call_fce TOKEN_SEMICOLON
	|TOKEN_VAR names TOKEN_SEMICOLON
	|TOKEN_ARRAY TOKEN_VAR array_names TOKEN_SEMICOLON
	|TOKEN_ARRAY TOKEN_POINT array_names TOKEN_SEMICOLON
	|TOKEN_POINT names TOKEN_SEMICOLON
	|assign TOKEN_SEMICOLON
	|variable TOKEN_PLUSPLUS
	|variable TOKEN_MINUSMINUS
      	;
assign: variable_left TOKEN_ASSIGN variable
	|variable_left TOKEN_ASSIGN number
	;
variable_left: TOKEN_IDENTIFIER /* musi byt pole, point alebo nejaka ina shopna struktura */
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
init: TOKEN_VAR TOKEN_IDENTIFIER TOKEN_ASSIGN expression
	|TOKEN_IDENTIFIER TOKEN_ASSIGN expression
	|TOKEN_IDENTIFIER TOKEN_LSBRA expression TOKEN_RSBRA TOKEN_ASSIGN expression
    	;
variable: TOKEN_IDENTIFIER
	|TOKEN_IDENTIFIER array_access
	|TOKEN_IDENTIFIER TOKEN_DOT call_fce //tuto musi byt funkcia, co odpoveda danemu identifierovi, napr see(3).IsMoving()
	|TOKEN_IDENTIFIER array_access TOKEN_DOT call_fce
	|call_fce TOKEN_DOT call_fce // prave na tie veci ako see(3).isplayer
	;
array_access: TOKEN_LSBRA exps TOKEN_RSBRA
	|array_access TOKEN_LSBRA exps TOKEN_RSBRA
	;
exps: expression
	| exps TOKEN_COMMA expression
	;
expression_base: variable 
	|number
	|call_fce
	|variable TOKEN_MINUSMINUS
	|variable TOKEN_PLUSPLUS
	|TOKEN_LPAR expression TOKEN_RPAR
	;
expression_mul:expression_base
	|expression_mul TOKEN_OPER_MUL expression_base
	;
expression_add: expression_mul
	|expression_add TOKEN_OPER_SIGNADD expression_base
	;
expression:	expression_add
	;
expression_bool_base: expression
	|expression TOKEN_OPER_REL expression
	|expression TOKEN_EQ expression
	|expression TOKEN_NOT expression
	;
expression_bool_or: expression_bool_base
	| expression_bool_or TOKEN_BOOL_OR TOKEN_LPAR expression_bool TOKEN_RPAR
	;
expression_bool: expression_bool_or
	| expression_bool TOKEN_BOOL_AND expression_bool_or
	;
%%

extern FILE * yyin;
static void yyerror(const char * message)
{
	printf("Co to, co to? %s\n", message);
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

yyparse();
    fclose(yyin);
	return 0;	
}

