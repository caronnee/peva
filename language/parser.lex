%option noyywrap
%option nostdinit
%option never-interactive
%option 8bit
%option nounput

%x COMMENT_LINE
%x COMMENT
%{
	#include "tokens.h"
	#include "header1.h"
%}

WHITESPACE		[ \r\n\t\f]

%%

{WHITESPACE}+	printf("whitespace!");	

point 	return TOKEN_POINT;
var 	return TOKEN_VAR;
function 	return TOKEN_FUNCTION;
array 	return TOKEN_ARRAY;
else 	return TOKEN_ELSE;
while 	return TOKEN_WHILE;
do	return TOKEN_DO;		/* do */
repeat 	return TOKEN_REPEAT;
until 	return TOKEN_UNTIL;
for 	return TOKEN_FOR;
\|\|	return TOKEN_OR;		/* or */
if	return TOKEN_IF;		/* if */
not 	return TOKEN_NOT;
return return TOKEN_RETURN;
\; 	return TOKEN_SEMICOLON;
\, 	return TOKEN_COMMA;
\=\= 	return TOKEN_EQ;		
\: 	return TOKEN_COLON;
\( 	return TOKEN_LPAR;
\) 	return TOKEN_RPAR;
\[	return TOKEN_LSBRA;
\] 	return TOKEN_RSBRA;
= 	return TOKEN_ASSIGN;
run|shoot|wait|walk|see	return TOKEN_BOT;
[A-Za-z]+[A-Z_a-z0-9] 	return TOKEN_IDENTIFIER;
[0-9]+		 	return TOKEN_UINT;
[0-9]+(\.[0-9]+)?([Ee][\+\-]?[0-9]+)?	return TOKEN_REAL;
\<|\>|\<=|\>=|!= 	return TOKEN_OPER_REL;
\+|\- 	return TOKEN_OPER_SIGNADD;
\*|\/|\%|&&	return TOKEN_OPER_MUL;
\/\/		BEGIN(COMMENT_LINE);
<COMMENT_LINE>
{
\n	BEGIN(INITIAL);
}
<COMMENT>
{
\*\/	BEGIN(INITIAL);
}
.	printf("ERROR!\n");
%%

int main(int argc, char ** argv)
{
	if((yyin = fopen(argv[1],"r"))==0)
		return -1;
	int tok;
	while((tok == yylex())!=0)
	{
		printf("mam token %d\n", tok);
	}
	return 0;
}
