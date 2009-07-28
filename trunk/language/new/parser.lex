/*TODO! mohol by oznamovat aj presne slovo, ktore je vadne*/
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

\/\/						BEGIN(COMMENT_LINE);
\/\*						BEGIN(COMMENT);
main						{*l = line; return TOKEN_MAIN; };
void						{*l = line; return TOKEN_VOID; };
location					{*l = line;return TOKEN_LOCATION; };
real 						{*l = line;return TOKEN_VAR_REAL; };
IsPlayer					{*l = line;lv->og = FeatureIsPlayer;return TOKEN_OBJECT_FEATURE;}
IsWall						{*l = line;lv->og = FeatureIsWall;return TOKEN_OBJECT_FEATURE;}
IsMissille					{*l = line;lv->og = FeatureIsMissille;return TOKEN_OBJECT_FEATURE;}
IsMoving					{*l = line;lv->og = FeatureIsMoving;return TOKEN_OBJECT_FEATURE;}
Locate						{*l = line;lv->og = FeatureLocate;return TOKEN_OBJECT_FEATURE;}
integer						{*l = line;return TOKEN_VAR_INT; };
function	 	 	 	 	{*l = line;return TOKEN_FUNCTION; };
else 						{*l = line;return TOKEN_ELSE; };
while 						{*l = line;return TOKEN_WHILE; };
do						{*l = line;return TOKEN_DO;		/* do */ };
for 						{*l = line;return TOKEN_FOR; };
if						{*l = line;return TOKEN_IF;		/* if */ };
object						{*l = line;return TOKEN_OBJECT; };
return						{*l = line;return TOKEN_RETURN; };

\; 						{*l = line;return TOKEN_SEMICOLON; };
\, 						{*l = line;return TOKEN_COMMA; };
\.						{*l = line;return TOKEN_DOT; };
\( 						{*l = line;return TOKEN_LPAR; };
\) 						{*l = line;return TOKEN_RPAR; };
\[						{*l = line;return TOKEN_LSBRA; };
\] 						{*l = line;return TOKEN_RSBRA; };
= 						{*l = line;return TOKEN_ASSIGN; };
\+\+						{*l = line;return TOKEN_PLUSPLUS; };
\-\-						{*l = line;return TOKEN_MINUSMINUS; };
[A-Za-z]+[A-Z_a-z0-9]* 				{*l = line;lv->ident = yytext; return TOKEN_IDENTIFIER; };
[0-9]+		 	 	 	 	{*l = line;lv->ident = yytext; lv->number = atoi(yytext);return TOKEN_UINT; };
[0-9]+[A-Za-z0-9]* 	 	 	 	{*l = line;lv->ident = yytext; lv->number = atoi(yytext);return TOKEN_UINT; };
[0-9]+(\.[0-9]+)?([Ee][\+\-]?[0-9]+)?		{*l = line;lv->ident = yytext; lv->f_number = atof(yytext);return TOKEN_REAL; };
[0-9]+(\.[0-9]+)?([Ee][\+\-]?[0-9]+)?[A-Za-z0-9]*	;
\<		 				{ lv->operation = OperationLess;*l = line;return TOKEN_OPER_REL; };
\<=		 				{ lv->operation = OperationLessEqual;*l = line;return TOKEN_OPER_REL; };
\>		 				{ lv->operation = OperationGreater;*l = line;return TOKEN_OPER_REL; };
\>=		 				{ lv->operation = OperationGreaterEqual;*l = line;return TOKEN_OPER_REL; };
\!						{ lv->operation = OperationBoolNot;*l = line;return TOKEN_BOOL_OR; };
\!=		 				{ lv->operation = OperationNotEqual;*l = line;return TOKEN_OPER_REL; };
\=\=		 				{ lv->operation = OperationEqual;*l = line;return TOKEN_OPER_REL; };
\+ 						{ lv->operation = OperationPlus; *l = line;return TOKEN_OPER_SIGNADD; };
\- 						{ lv->operation = OperationMinus; *l = line;return TOKEN_OPER_SIGNADD; };
\*						{ lv->operation = OperationMultiply;*l = line;return TOKEN_OPER_MUL; };
\/						{ lv->operation = OperationDivide; *l = line;return TOKEN_OPER_MUL; };
\%						{ lv->operation = OperationModulo; *l = line;return TOKEN_OPER_MUL; };
&						{ lv->operation = OperationAnd;*l = line;return TOKEN_OPER_MUL; };
\|						{ lv->operation = OperationOr;*l = line;return TOKEN_OPER_MUL; };
\~						{ lv->operation = OperationNot;*l = line;return TOKEN_OPER_MUL; };
&&						{ lv->operation = OperationBoolAnd;*l = line;return TOKEN_BOOL_AND; };
\|\|						{ lv->operation = OperationBoolOr;*l = line;return TOKEN_BOOL_OR; };
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
.	printf("Unrecognized token!Ignoring.Line %d, %s\n", line, yytext);
