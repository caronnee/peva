%{
	#include "header1.h"
	#include <stdio.h>
	#include "parser_functions.h"

	#define YYSTYPE Lval 
	#define YYLTYPE unsigned
	#define YYLLOC_DEFAULT(cur, rhs, n)	do { if(n) (cur)=(rhs)[1]; else (cur)=(rhs)[0]; } while(0)

	#define YYERROR_VERBOSE 1		
	static void yyerror(YYLTYPE *line, Program* ctx, const char *m);

%}

/* keywords */
%token TOKEN_MAIN
%token TOKEN_LOCATION
%token TOKEN_OBJECT
%token TOKEN_VAR_REAL
%token TOKEN_VAR_INT
%token TOKEN_FUNCTION
%token TOKEN_ARRAY
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_WHILE
%token TOKEN_DO
%token TOKEN_FOR
%token TOKEN_BOOL_AND
%token TOKEN_BOOL_OR
%token TOKEN_RETURN
%token TOKEN_BREAK

/* literals */
%token<ident> TOKEN_IDENTIFIER
%token<number> TOKEN_UINT
%token<f_number> TOKEN_REAL

/* delimiters */
%token TOKEN_SEMICOLON
%token TOKEN_DOT
%token TOKEN_COMMA
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
%token<operation> TOKEN_OPER_REL

%token<operation> TOKEN_OPER_SIGNADD
%token<operation> TOKEN_OPER_MUL

%type<names> params
%type<block> block_of_instructions
%type<names> names
%type<names> point_name
%type<names> array_names
%type<node> number
%type<ranges> ranges

%start program
%error-verbose
%pure-parser
%parse-param {Program *program}
%lex-param {Program *program}
%locations

%%

program	: params declare_functions TOKEN_MAIN TOKEN_LPAR TOKEN_RPAR block_of_instructions // {add_main_code(program, block_of_instructions);}
	;
params:	/*	ziadne parametre	*/ {$$.clear()}
      	| params TOKEN_VAR_REAL names TOKEN_SEMICOLON {add(program,$3, TypeInteger);}
      	| params TOKEN_VAR_INT names TOKEN_SEMICOLON {add(program,$3, TypeInteger);}
	| params TOKEN_LOCATION point_name TOKEN_SEMICOLON {}//tot sa vyriesi samo, kedze vieme, ze ide o point
	| params TOKEN_OBJECT names TOKEN_SEMICOLON {add(program, $3, TypeObject);}
	| params TOKEN_ARRAY TOKEN_LOCATION array_names TOKEN_SEMICOLON  {add_array($4, TypeLocation);}
	| params TOKEN_ARRAY TOKEN_VAR_REAL array_names TOKEN_SEMICOLON // {add_array(program,$2,$4, TYPE_LOCATION);}
	| params TOKEN_ARRAY TOKEN_VAR_INT array_names TOKEN_SEMICOLON // {add_array(program,$2,$4, TYPE_LOCATION);}
	| params TOKEN_ARRAY TOKEN_OBJECT array_names TOKEN_SEMICOLON // {add_array(program,$2,$4, TYPE_LOCATION);}
	;
//OK
point_name: TOKEN_IDENTIFIER {add(program,$1,TypeLocation);}
	| TOKEN_IDENTIFIER TOKEN_ASSIGN TOKEN_BEGIN TOKEN_UINT TOKEN_COMMA TOKEN_UINT TOKEN_END {add(program,$1,Location($4,$6));}
	| point_name TOKEN_COMMA TOKEN_IDENTIFIER {add(program,$1,TypeLocation);}
	| point_name TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN TOKEN_BEGIN TOKEN_UINT TOKEN_COMMA TOKEN_UINT TOKEN_END  {add(program, $3, Location($6,$8));}
	;
//OK
array_names: TOKEN_IDENTIFIER {$$.push_back(add_array(program, $1));}
	|array_names TOKEN_COMMA TOKEN_IDENTIFIER {$1.push_back(add_array(program,$3));$$=$1;}
	|TOKEN_IDENTIFIER ranges {$$.push_back(add_array(program, $1, $2));}/*pre definovanie kolko pola bude volneho, aby sa nezahltila pamat*/
	|array_names TOKEN_IDENTIFIER ranges {$1.push_back(add_array(program,$2,$3));$$ = $1;}
	;
//OK
ranges: TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA {$$.clear();$$.push_back($2);}
      	|ranges TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { $1.push_back($3); $$ = $1;}
	;
names:	TOKEN_IDENTIFIER {add(program, $1, TypeUndefined);}
	|TOKEN_IDENTIFIER TOKEN_ASSIGN number // {add(program, $1);}
     	|names TOKEN_COMMA TOKEN_IDENTIFIER {add(program, $3, TypeUndefined);}
     	|names TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_ASSIGN number 
	;
declare_functions: /*	ziadne deklarovane funkcie	*/
	|declare_function_
	;
declare_function_:	TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAR names TOKEN_RPAR block_of_instructions /* pozor! parameter uz definovany!*/
	|declare_function_ TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAR names TOKEN_RPAR block_of_instructions /* pozor! parameter uz definovany!*/
	|TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAR TOKEN_RPAR block_of_instructions /* pozor! parameter uz definovany!*/
	|declare_function_ TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAR TOKEN_RPAR block_of_instructions /* pozor! parameter uz definovany!*/
	;
number:TOKEN_OPER_SIGNADD TOKEN_REAL
      |TOKEN_OPER_SIGNADD TOKEN_UINT
      |TOKEN_REAL
      |TOKEN_UINT
	;
block_of_instructions: TOKEN_BEGIN TOKEN_END /* prazdno */ {$$.clear();}
	|TOKEN_BEGIN TOKEN_SEMICOLON TOKEN_END  /* ziadna instrukcia */
	|TOKEN_BEGIN commands TOKEN_END /* neprazdne instrukcie*/
	;
commands: matched
	| commands matched
	| unmatched
	| commands unmatched
	;
command:	TOKEN_FOR TOKEN_LPAR init TOKEN_SEMICOLON expression_bool TOKEN_SEMICOLON simple_command TOKEN_RPAR block_of_instructions 
	|TOKEN_DO block_of_instructions TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR TOKEN_SEMICOLON
	|TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions
	|TOKEN_RETURN expression TOKEN_SEMICOLON
	|TOKEN_RETURN TOKEN_SEMICOLON
	|TOKEN_BREAK TOKEN_SEMICOLON
	|TOKEN_VAR_REAL names TOKEN_SEMICOLON
	|TOKEN_VAR_INT names TOKEN_SEMICOLON
	|TOKEN_ARRAY TOKEN_VAR_REAL array_names TOKEN_SEMICOLON
	|TOKEN_ARRAY TOKEN_VAR_INT array_names TOKEN_SEMICOLON
	|TOKEN_ARRAY TOKEN_LOCATION array_names TOKEN_SEMICOLON
	|TOKEN_LOCATION names TOKEN_SEMICOLON
	|simple_command TOKEN_SEMICOLON
      	;
simple_command:	assign 
	|variable TOKEN_PLUSPLUS 
	|variable TOKEN_MINUSMINUS 
	|variable 
	;
assign: variable_left TOKEN_ASSIGN variable
	|variable_left TOKEN_ASSIGN number //TODO anonymna premenna, nestoji mnoho
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
init: 		TOKEN_VAR_INT TOKEN_IDENTIFIER TOKEN_ASSIGN expression
    	|TOKEN_VAR_REAL TOKEN_IDENTIFIER TOKEN_ASSIGN expression
	|TOKEN_IDENTIFIER TOKEN_ASSIGN expression
	|TOKEN_IDENTIFIER TOKEN_LSBRA expression TOKEN_RSBRA TOKEN_ASSIGN expression
    	;
variable: TOKEN_IDENTIFIER
	|TOKEN_IDENTIFIER array_access
	|call_fce
	|variable TOKEN_DOT TOKEN_IDENTIFIER //tuto musi byt funkcia, co odpoveda danemu identifierovi, napr see(3).IsMoving()
	|variable TOKEN_DOT call_fce
	;
array_access: TOKEN_LSBRA exps TOKEN_RSBRA
	|array_access TOKEN_LSBRA exps TOKEN_RSBRA
	;
exps: expression
	| exps TOKEN_COMMA expression
	;
expression_base: variable 
	|number
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
	;
expression_bool_or: expression_bool_base
	| expression_bool_or TOKEN_BOOL_OR TOKEN_LPAR expression_bool TOKEN_RPAR
	;
expression_bool: expression_bool_or
	| expression_bool TOKEN_BOOL_AND expression_bool_or
	;
%%

extern FILE * yyin;

static void yyerror(unsigned *line,Program* ctx, const char *message)
{
	printf("Co to, co to? %s, line %d\n", message, *line);
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

	Program q;
	q.add_string(".", TypeUndefined);//anonymna premenna
	yyparse(&q);
    	fclose(yyin);
//	q.output(&q.defined);
	return 0;	
}

