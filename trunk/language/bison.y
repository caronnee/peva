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
%token TOKEN_REPEAT
%token TOKEN_UNTIL
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
	|TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAR names TOKEN_RPAR TOKEN_BEGIN block_of_instructions TOKEN_END /* pozor! parameter uz definovany!*/
	;
number:TOKEN_OPER_SIGNADD TOKEN_REAL
      |TOKEN_OPER_SIGNADD TOKEN_UINT
      |TOKEN_REAL
      |TOKEN_UINT
	;
block_of_instructions: /* ZIADNA INSTRUKCIA */
	|matched
	|unmatched
	;
command:	/* ziadny command */
       |TOKEN_BOT_ACTION
	;
matched:TOKEN_IF matched TOKEN_ELSE matched
       | command TOKEN_SEMICOLON
	;
unmatched:	TOKEN_IF block_of_instructions
	 |TOKEN_IF matched TOKEN_ELSE unmatched
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

