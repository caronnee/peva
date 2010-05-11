/*TODO! mohol by oznamovat aj presne slovo, ktore je vadne*/
%option noyywrap
%option nostdinit
%option never-interactive
%option 8bit
%option nounput

%x COMMENT_LINE
%x COMMENT
%{
	#include "../h/lval.h"
	#include "../h/bison.h"
	#include "../../add-ons/h/macros.h"

int line = 1;

%}

WHITESPACE		[ \r\t\f]

%%

<<EOF>>						{ line = 1;TEST("OK, zmenuila som na 1"); yyterminate(); }

{WHITESPACE}+					;

\/\/						BEGIN(COMMENT_LINE);
\/\*						BEGIN(COMMENT);

[rR][oO][bB][oO][tT]				{*l = line; return TOKEN_ROBOT; }
[hH][eE][aA][lL][tT][hH] 			{*l = line; lv->op = OptionHealth; return TOKEN_OPTION; }
[aA][tT][tT][aA][cC][kK]			{*l = line; lv->op = OptionAttack; return TOKEN_OPTION; }
[dD][eE][fF][eE][nN][sS][eE]			{*l = line; lv->op = OptionDefense;return TOKEN_OPTION; }
[mM][aA][tT][tT][aA][cC][kK] 			{*l = line; lv->op = OptionMisilleAttack; return TOKEN_OPTION; }
[mM][hH][eE][aA][lL][tT][hH]			{*l = line; lv->op = OptionMisilleHealth; return TOKEN_OPTION; }
[aA][nN][gG][lL][eE]				{*l = line; lv->op = OptionSee; return TOKEN_OPTION;}
[sS][tT][eE][pP]				{*l = line; lv->op = OptionStep; return TOKEN_OPTION;}
[mM][eE][mM][oO][rR][yY]			{*l = line; lv->op = OptionMemory; return TOKEN_OPTION;}
                                	
[vV][iI][sS][iI][tT]				{*l = line; return TOKEN_VISIT; }
[vV][iI][sS][iI][tT]_[sS][eE][qQ]		{*l = line; return TOKEN_VISIT_SEQUENCE; }
[kK][iI][lL][lL][eE][dD]			{*l = line; return TOKEN_KILLED; }
[sS][kK][iI][nN]				{*l = line; return TOKEN_SKIN;}
[kK][iI][lL][lL]				{*l = line; return TOKEN_KILL;}
[sS][tT][aA][rR][tT]				{*l = line; return TOKEN_START; }
                                	
[iI][sS][pP][lL][aA][yY][eE][rR]		{*l = line;lv->of = FeatureIsPlayer;return TOKEN_OBJECT_FEATURE;}
[iI][sS][wW][aA][lL][lL]			{*l = line;lv->of = FeatureIsWall;return TOKEN_OBJECT_FEATURE;}
[iI][sS][mM][iI][sS][sS][iI][lL][lL][eE]	{*l = line;lv->of = FeatureIsMissille;return TOKEN_OBJECT_FEATURE;}
[iI][sS][mM][oO][vV][iI][nN][gG]		{*l = line;lv->of = FeatureIsMoving;return TOKEN_OBJECT_FEATURE;}
[lL][oO][cC][aA][tT][eE]			{*l = line;lv->of = FeatureLocate;return TOKEN_OBJECT_FEATURE;}
[sS][eE][eE]					{*l = line;lv->of = FeatureSee;return TOKEN_OBJECT_FEATURE;}
[hH][iI][tT]					{*l = line;lv->of = FeatureHit;return TOKEN_OBJECT_FEATURE;}
[tT][uU][rR][nN]				{*l = line;lv->of = FeatureTurn;return TOKEN_OBJECT_FEATURE;}
[tT][uU][rR][nN]L				{*l = line;lv->of = FeatureTurnL;return TOKEN_OBJECT_FEATURE;}
[tT][uU][rR][nN]R				{*l = line;lv->of = FeatureTurnR;return TOKEN_OBJECT_FEATURE;}
[wW][aA][iI][tT]				{*l = line;lv->of = FeatureWait;return TOKEN_OBJECT_FEATURE;}
[sS][hH][oO][oO][tT]				{*l = line;lv->of = FeatureShoot;return TOKEN_OBJECT_FEATURE;}
[mM][oO][vV][eE]				{*l = line;lv->of = FeatureStep;return TOKEN_OBJECT_FEATURE;}
[gG][eE][tT][tT][aA][rR][gG][eE][tT]		{*l = line;lv->of = FeatureTarget; return TOKEN_OBJECT_FEATURE;}
[dD][iI][rR][eE][cC][tT][iI][oO][nN]		{*l = line;lv->of = FeatureDirection; return TOKEN_OBJECT_FEATURE;}

[mM][aA][iI][nN]				{*l = line; return TOKEN_MAIN; }
[vV][aA][rR]					{*l = line; return TOKEN_REFERENCE;}
[vV][oO][iI][dD]				{*l = line; return TOKEN_VOID; }
[lL][oO][cC][aA][tT][iI][oO][nN]		{*l = line;return TOKEN_LOCATION; }
[rR][eE][aA][lL] 				{*l = line;return TOKEN_VAR_REAL; }
[sS][eE][eE][nN] 				{*l = line;return TOKEN_SEEN; }
[iI][nN][tT][eE][gG][eE][rR]			{*l = line;return TOKEN_VAR_INT; }
[fF][uU][nN][cC][tT][iI][oO][nN]		{*l = line;return TOKEN_FUNCTION; }
[eE][lL][sS][eE] 				{*l = line;return TOKEN_ELSE; }
[wW][hH][iI][lL][eE] 				{*l = line;return TOKEN_WHILE; }
[dD][oO]					{*l = line;return TOKEN_DO;		/* do */ }
[fF][oO][rR] 					{*l = line;return TOKEN_FOR; }
[iI][fF]					{*l = line;return TOKEN_IF;		/* if */ }
[oO][bB][jJ][eE][cC][tT]			{*l = line;return TOKEN_OBJECT; }
[rR][eE][tT][uU][rR][nN]			{*l = line;return TOKEN_RETURN; }
[bB][rR][eE][aA][kK]				{*l = line;return TOKEN_BREAK; }
[cC][oO][nN][tT][iI][nN][uU][eE]		{*l = line;return TOKEN_CONTINUE; }
this						{*l = line; return TOKEN_THIS;	}
NULL						{*l = line; return TOKEN_NULL; }
\; 						{*l = line;return TOKEN_SEMICOLON; }
\, 						{*l = line;return TOKEN_COMMA; }
\.						{*l = line;return TOKEN_DOT; }
\( 						{*l = line;return TOKEN_LPAR; }
\) 						{*l = line;return TOKEN_RPAR; }
\[						{*l = line;return TOKEN_LSBRA; }
\] 						{*l = line;return TOKEN_RSBRA; }
= 						{*l = line;return TOKEN_ASSIGN; }
\+\+						{*l = line;return TOKEN_PLUSPLUS; }
\-\-						{*l = line;return TOKEN_MINUSMINUS; }
[A-Za-z]+[A-Z_a-z0-9]* 				{*l = line;lv->ident = yytext; return TOKEN_IDENTIFIER; }
[0-9]+		 	 	 	 	{*l = line;lv->ident = yytext; lv->number = atoi(yytext);return TOKEN_UINT; }
[0-9]+[A-Za-z0-9]* 	 	 	 	{*l = line;lv->ident = yytext; 
							if (!robots->robots.empty()) 
								robots->robots.back()->error(line, Robot::WarningMalformedInteger); 
							lv->number = atoi(yytext);
							return TOKEN_UINT;
						 }
[0-9]+(\.[0-9]+)?([Ee][\+\-]?[0-9]+)?		{*l = line;lv->ident = yytext; lv->f_number = atof(yytext);return TOKEN_REAL; }
[0-9]+(\.[0-9]+)?([Ee][\+\-]?[0-9]+)?[A-Za-z0-9]*	{*l = line;
							lv->ident = yytext; 
							lv->f_number = atof(yytext);
							if (!robots->robots.empty()) 
								robots->robots.back()->error(line, Robot::WarningMalformedReal); 
							return TOKEN_REAL; 
							} 
\<		 				{lv->operation = OperationLess;*l = line;return TOKEN_OPER_REL; }
\<=		 				{lv->operation = OperationLessEqual;*l = line;return TOKEN_OPER_REL; }
\>		 				{lv->operation = OperationGreater;*l = line;return TOKEN_OPER_REL; }
\>=		 				{lv->operation = OperationGreaterEqual;*l = line;return TOKEN_OPER_REL; }
\!						{lv->operation = OperationBoolNot;*l = line;return TOKEN_BOOL_OR; }
\!=		 				{lv->operation = OperationNotEqual;*l = line;return TOKEN_OPER_REL; }
\=\=		 				{lv->operation = OperationEqual;*l = line;return TOKEN_OPER_REL; }
\+ 						{lv->operation = OperationPlus; *l = line;return TOKEN_OPER_SIGNADD; }
\- 						{lv->operation = OperationMinus; *l = line;return TOKEN_OPER_SIGNADD; }
\*						{lv->operation = OperationMultiply;*l = line;return TOKEN_OPER_MUL; }
\/						{lv->operation = OperationDivide; *l = line;return TOKEN_OPER_MUL; }
\%						{lv->operation = OperationModulo; *l = line;return TOKEN_OPER_MUL; }
&						{lv->operation = OperationAnd;*l = line;return TOKEN_OPER_MUL; }
\|						{lv->operation = OperationOr;*l = line;return TOKEN_OPER_MUL; }
\~						{lv->operation = OperationNot;*l = line;return TOKEN_OPER_MUL; }
&&						{lv->operation = OperationBoolAnd;*l = line;return TOKEN_BOOL_AND; }
\|\|						{lv->operation = OperationBoolOr;*l = line;return TOKEN_BOOL_OR; }
\{						{*l = line;return TOKEN_BEGIN; }
\}						{*l = line;return TOKEN_END; }
<COMMENT_LINE>
{
\n						{BEGIN(INITIAL);line++;}
.						;
}
<COMMENT>
{
\*\/	BEGIN(INITIAL);
\n	{line++;}
.	;
}
\n	line++;
.	printf("Unrecognized token!Ignoring.Line %d, %s\n", line, yytext);
%%
void my_destroy()
{ 
	yylex_destroy ();
	line = 1;
}
