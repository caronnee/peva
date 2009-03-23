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
	#include "bison.hpp"

int line = 1;
%}

WHITESPACE		[ \r\t\f]

%%

{WHITESPACE}+					;

main						return TOKEN_MAIN;
point 						return TOKEN_POINT;
var 						return TOKEN_VAR;
function	 	 	 	 	return TOKEN_FUNCTION;
array 						return TOKEN_ARRAY;
else 						return TOKEN_ELSE;
while 						return TOKEN_WHILE;
do						return TOKEN_DO;		/* do */
for 						return TOKEN_FOR;
if						return TOKEN_IF;		/* if */
not 						return TOKEN_NOT;
return						return TOKEN_RETURN;
\; 						return TOKEN_SEMICOLON;
\, 						return TOKEN_COMMA;
\.						return TOKEN_DOT;
\=\= 						return TOKEN_EQ;		
\( 						return TOKEN_LPAR;
\) 						return TOKEN_RPAR;
\[						return TOKEN_LSBRA;
\] 						return TOKEN_RSBRA;
= 						return TOKEN_ASSIGN;
run|shoot|wait|walk|see				return TOKEN_BOT_ACTION;
[A-Za-z]+[A-Z_a-z0-9]* 				return TOKEN_IDENTIFIER;
[0-9]+		 	 	 	 	return TOKEN_UINT;
[0-9]+(\.[0-9]+)?([Ee][\+\-]?[0-9]+)?		return TOKEN_REAL;
\<|\>|\<=|\>=|!= 				return TOKEN_OPER_REL;
\+|\- 						return TOKEN_OPER_SIGNADD;
\*|\/|\%|&|\|					return TOKEN_OPER_MUL;
&&						return TOKEN_BOOL_AND;
\|\|						return TOKEN_BOOL_OR;
\{						return TOKEN_BEGIN;
\}						return TOKEN_END;
\/\/		BEGIN(COMMENT_LINE);
<COMMENT_LINE>
{
\n	{BEGIN(INITIAL);line++;}
.	;
}
<COMMENT>
{
\*\/	BEGIN(INITIAL);
}
\n	line++;
.	printf("ERROR!Line %d, %s\n", line, yylex);
