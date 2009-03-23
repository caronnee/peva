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
%token TOKEN_OR
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

/* group tokens */
%token TOKEN_OPER_REL
%token TOKEN_OPER_SIGNADD
%token TOKEN_OPER_MUL
%token TOKEN_BOT_ACTION

%start program
%error-verbose
%pure-parser
%locations

%%

program	: params declare_functions TOKEN_MAIN TOKEN_LPAR TOKEN_RPAR TOKEN_BEGIN block_of_instructions TOKEN_END
	;
params:	/*	ziadne parametre	*/
      	| TOKEN_VAR names TOKEN_SEMICOLON
	| TOKEN_ARRAY array_names TOKEN_SEMICOLON
	| TOKEN_POINT names TOKEN_SEMICOLON
	;
array_names: TOKEN_IDENTIFIER
	   |array_names TOKEN_COMMA TOKEN_IDENTIFIER
	|TOKEN_IDENTIFIER TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA
	|array_names TOKEN_IDENTIFIER TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA
	;
names:	TOKEN_IDENTIFIER
	|TOKEN_IDENTIFIER TOKEN_ASSIGN number
     	|names TOKEN_COMMA TOKEN_IDENTIFIER 
     	|names TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN number 
	;
declare_functions: /*	ziadne deklarovane funkcie	*/
	|TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAR names TOKEN_RPAR block_of_instructions /* pozor! parameter uz definovany!*/
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
command:	TOKEN_BOT_ACTION TOKEN_SEMICOLON
	|TOKEN_FOR TOKEN_LPAR init TOKEN_SEMICOLON expression_bool TOKEN_SEMICOLON command TOKEN_RPAR block_of_instructions 
	|TOKEN_DO block_of_instructions TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR TOKEN_SEMICOLON
	|TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions
	|TOKEN_RETURN number TOKEN_SEMICOLON
	|TOKEN_RETURN TOKEN_IDENTIFIER TOKEN_SEMICOLON
	|TOKEN_RETURN call_fce
	|TOKEN_BREAK TOKEN_SEMICOLON
	|call_fce
      	;
call_fce:	TOKEN_IDENTIFIER TOKEN_LPAR call_parameters TOKEN_RPAR TOKEN_SEMICOLON
	;
call_parameters: expression
	 |call_parameters TOKEN_COMMA expression
	;
matched:TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE matched
       | command
	;
unmatched:	TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions
	 |TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR TOKEN_LPAR expression TOKEN_RPAR matched TOKEN_ELSE unmatched
	;
init: TOKEN_VAR TOKEN_IDENTIFIER TOKEN_ASSIGN expression
	|TOKEN_IDENTIFIER TOKEN_ASSIGN expression
	|TOKEN_IDENTIFIER TOKEN_LSBRA expression TOKEN_RSBRA TOKEN_ASSIGN expression
    	;
expression_base: TOKEN_IDENTIFIER
	|number
	|call_fce
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
expression_bool:expression
	|expression TOKEN_OPER_REL expression
	|expression TOKEN_EQ expression
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

