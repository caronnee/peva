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

\/\/		BEGIN(COMMENT_LINE);
\/\*		BEGIN(COMMENT);
main						{*l = line;return TOKEN_MAIN; };
point 						{*l = line;return TOKEN_POINT; };
var 						{*l = line;return TOKEN_VAR; };
function	 	 	 	 	{*l = line;return TOKEN_FUNCTION; };
array 						{*l = line;return TOKEN_ARRAY; };
else 						{*l = line;return TOKEN_ELSE; };
while 						{*l = line;return TOKEN_WHILE; };
do						{*l = line;return TOKEN_DO;		/* do */ };
for 						{*l = line;return TOKEN_FOR; };
if						{*l = line;return TOKEN_IF;		/* if */ };
not 						{*l = line;return TOKEN_NOT; };
return						{*l = line;return TOKEN_RETURN; };
\; 						{*l = line;return TOKEN_SEMICOLON; };
\, 						{*l = line;return TOKEN_COMMA; };
\.						{*l = line;return TOKEN_DOT; };
\=\= 						{*l = line;return TOKEN_EQ;		 };
\( 						{*l = line;return TOKEN_LPAR; };
\) 						{*l = line;return TOKEN_RPAR; };
\[						{*l = line;return TOKEN_LSBRA; };
\] 						{*l = line;return TOKEN_RSBRA; };
= 						{*l = line;return TOKEN_ASSIGN; };
\+\+						{*l = line;return TOKEN_PLUSPLUS; };
\-\-						{*l = line;return TOKEN_MINUSMINUS; };
[A-Za-z]+[A-Z_a-z0-9]* 				{*l = line;return TOKEN_IDENTIFIER; };
[0-9]+		 	 	 	 	{*l = line;return TOKEN_UINT; };
[0-9]+(\.[0-9]+)?([Ee][\+\-]?[0-9]+)?		{*l = line;return TOKEN_REAL; };
\<|\>|\<=|\>=|!= 				{*l = line;return TOKEN_OPER_REL; };
\+|\- 						{*l = line;return TOKEN_OPER_SIGNADD; };
\*|\/|\%|&|\|					{*l = line;return TOKEN_OPER_MUL; };
&&						{*l = line;return TOKEN_BOOL_AND; };
\|\|						{*l = line;return TOKEN_BOOL_OR; };
\{						{*l = line;return TOKEN_BEGIN; };
\}						{*l = line;return TOKEN_END; };
<COMMENT_LINE>
{
\n	{BEGIN(INITIAL);line++;}
.	;
}
<COMMENT>
{
\*\/	BEGIN(INITIAL);
\n	{line++;};
.	;
}
\n	line++;
.	printf("ERROR!Line %d, %s\n", line, yylex);
