%option noyywrap
%option nostdinit
%option never-interactive
%option 8bit
%option nounput

%{
	#include "tokens.h"
	#include "header1.h"
%}

DIGIT			[0-9]
WHITESPACE		[ \r\n\t\f]

%%

{DIGIT}*			printf("cislo\n");

{WHITESPACE}+	printf("whitespace!");	
\<		return TOKEN_LT;
\<\= 	return TOKEN_LE;
\!\= 	return TOKEN_NE;
\>\= 	return TOKEN_GE;
\> 	return TOKEN_GT;

\+|\-	return TOKENGE_OPER_SIGNADD;

\*	return TOKENGE_ASTERISK;
\/ 	return TOKENGE_SOLIDUS;
div 	return TOKENGE_DIV;
mod 	return TOKENGE_MOD;
and 	return TOKENGE_AND;

/* keywords */
point 	return TOKEN_POINT;
var 	return TOKEN_VAR;
function 	return TOKEN_FUNCTION;
array 	return TOKEN_ARRAY;
return return TOKEN_RETURN
if	return TOKEN_IF;		/* if */
else 	return TOKEN_ELSE;
while 	return TOKEN_WHILE;
do	return TOKEN_DO;		/* do */
repeat 	return TOKEN_REPEAT;
until 	return TOKEN_UNTIL;
for 	return TOKEN_FOR;
or	return TOKEN_OR;		/* or */
not 	return TOKEN_NOT;

/* bot features */
move	return TOKEN_MOVE;
run	return TOKEN_RUN;
shoot	return TOKEN_SHOOT;
wait	return TOKEN_WAIT;
walk	return TOKEN_WALK;
see	return TOKEN_SEE;

/* object features */
isPlayer	return TOKEN_ISPLAYER;
isMoving	return TOKEN_ISMOVING;
isWall		return TOKEN_ISWALL;
isHit		return TOKEN_ISHIT;
Locate		return TOKEN_LOCATION;
Distance	return TOKEN_DISTANCE;
\.x 		return TOKEN_X;
\.y		return TOKEN_Y;


/* literals */
[A-Za-z]+[A-Z_a-z0-9] 	return TOKEN_IDENTIFIER;
[0-9]+		 	return TOKEN_UINT;
[0-9]+(\.[0-9]+)?([Ee][\+\-]?[0-9]+)?	return TOKEN_REAL;
string 	return TOKEN_STRING;

/* delimiters */

\; 	return TOKEN_SEMICOLON;
\. 	return TOKEN_DOT;
\, 	return TOKEN_COMMA;
\=\= 	return TOKEN_EQ;		
\: 	return TOKEN_COLON;
\( 	return TOKEN_LPAR;
\) 	return TOKEN_RPAR;
\[ 	return TOKEN_LSBRA;
\] 	return TOKEN_RSBRA;
= 	return TOKEN_ASSIGN;

/* group tokens */
\<|\>|\<=|\>=|!= 	return TOKEN_OPER_REL;
\+|\- 	return TOKEN_OPER_SIGNADD;
\*\/	return TOKEN_OPER_MUL;

%%

int main(int argc, char ** argv)
{
	if((yyin = fopen(argv[1],"r"))==0)
		return -1;
	int tok;
	while((tok == yylex())!=0)
	{
		printf("mam token %d", tok);
	}
	return 0;
}
