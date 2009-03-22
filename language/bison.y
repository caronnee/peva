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
%token TOKEN_LITERAL
%token TOKEN_IDENTIFIER
%token TOKEN_UINT
%token TOKEN_REAL

/* delimiters */
%token TOKEN_DELIMITER
%token TOKEN_SEMICOLON
%token TOKEN_DOT
%token TOKEN_COMMA
%token TOKEN_EQ
%token TOKEN_COLON
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

program:	{printf("bleblebl");}
       	|TOKEN_VAR	{printf("muheheh");}
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

