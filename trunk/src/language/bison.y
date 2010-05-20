//TODO zrusit loadGlobal
//TODO do funkcii kopirovat cez load/sotre a hned za tym pridavat remove tempy kvoli pamat
//FIXME pri for-e odtranit vytvorenie premennej, spravit skor  defauult temp

%{
#include <iostream>
#include <queue>
#include "../h/lval.h"
#include "../h/robot.h"
#include "../h/parser_functions.h"
#include "../h/hflex.h"
#include "../../add-ons/h/macros.h"

#define YYSTYPE Lval 
#define YYLTYPE unsigned
#define YYLLOC_DEFAULT(cur, rhs, n)	do { if(n) (cur)=(rhs)[1]; else (cur)=(rhs)[0]; } while(0)
#define YYERROR_VERBOSE 1		

static void yyerror(YYLTYPE *line, Robots* ctx, const char *m);

%}

/* keywords */
%token TOKEN_MAIN "main function"
%token TOKEN_LOCATION "word location"
%token TOKEN_OBJECT "keyword object"
%token TOKEN_VAR_REAL "keyword real"
%token TOKEN_VAR_INT "keyword integer"
%token TOKEN_VOID "keyword void"
%token TOKEN_FUNCTION "keyword function"
%token TOKEN_IF "keyword if"
%token TOKEN_ELSE "keyword else"
%token TOKEN_WHILE "keyword while"
%token TOKEN_DO "keyword do"
%token TOKEN_FOR "keyword for"
%token TOKEN_RETURN "keyword return"
%token TOKEN_BREAK "keyword break"
%token TOKEN_REFERENCE "keyword var"
%token TOKEN_NULL "keyword null"
%token TOKEN_THIS "keyword this"
%token TOKEN_CONTINUE "keyword continue"
%token TOKEN_ROBOT "keyword robot"
%token TOKEN_RND "random function"
%token TOKEN_RET_TARGET "function get_target"
%token<op> TOKEN_OPTION "robot setings"
%token<of> TOKEN_OBJECT_FEATURE "function asking about state"

/* delimiters */
%token TOKEN_SEMICOLON ";"
%token TOKEN_DOT "."
%token TOKEN_COMMA ","
%token TOKEN_LPAR "("
%token TOKEN_RPAR ")"
%token TOKEN_LSBRA "["
%token TOKEN_RSBRA "]"
%token TOKEN_ASSIGN "="
%token TOKEN_BEGIN "{"
%token TOKEN_END "}"

/* literals */
%token<ident> TOKEN_IDENTIFIER " name of variable or function"
%token<number> TOKEN_UINT "integer number"
%token<f_number> TOKEN_REAL "real number"
%token TOKEN_SEEN "seen function"

/* target of game*/
%token TOKEN_VISIT "keyword visit"
%token TOKEN_VISIT_SEQUENCE "keyword visit_seq"
%token TOKEN_KILLED "keyword killed"
%token TOKEN_SKIN "keyword skin"
%token TOKEN_KILL "keyword kill"
%token TOKEN_START "keyword start"

/* group tokens */
%token<operation> TOKEN_OPER_REL "<, >, >=, =<"
%token<operation> TOKEN_OPER_SIGNADD "sign or additive operator"
%token<operation> TOKEN_OPER_MUL "multiplicative operator"
%token<operation> TOKEN_PLUSPLUS "++"
%token<operation> TOKEN_MINUSMINUS "--"
%token<operation> TOKEN_BOOL_AND "&&"
%token<operation> TOKEN_BOOL_OR "|| or !"

%type<ident> function_name "function name"

%type<type> simple_type "simple variable type"
%type<type> complex_type "complex variable type"
%type<type> type "variable type"
%type<type> return_type "return type"

%type<ranges> ranges "range"
%type<ident> function_header "function header"

%type<entries> parameters_empty "zero or more paramaters"
%type<entries> parameters "paramaters"

%type<instructions> names "inicializations"
%type<instructions> names_ "inicialization"
%type<instructions> cycle_for "for cycle"
%type<instructions> local_variables "local variable(s)"
%type<instructions> block_of_instructions "block of instructions"
%type<instructions> global_variables "global variable(s)"
%type<instructions> commands "block of commands"
%type<instructions> command "command"
%type<instructions> matched "if/else block"
%type<instructions> unmatched "if block"
%type<instructions> init "create or assign"
%type<instructions> assign "assign"
%type<instructions> command_var "command or vvariable declaring"
%type<instructions> simple_command "simple command"
%type<instructions> commands_and_empty "nothing or command"

%type<array_access> array_access "[number(,number)*]"

%type<defVal> values "values expression"

%type<output> array "array declaring"
%type<output> variable "variable declaring"
%type<output> variable_left "variable to be assigned to "
%type<output> number "number"
%type<output> declare_functions "declaring function(s)"
%type<output> declare_function_ "declare function"
%type<output> unary_var "unary variable"
%type<output> expression_bool "expression with boolean result"
%type<output> expression "expression"
%type<output> exps "expressions"
%type<output> expression_base "variable or constant"
%type<output> expression_mul "multiplying expression"
%type<output> expression_add "plus expression"
%type<output> expression_bool_base "variable or constant acting as boolean"
%type<output> expression_bool_or "|| expresion"
%type<output> call_fce "calling function"
%type<output> call_parameters "parameters of function being called"
%type<places> places "defining target places"
%type<target> place "defining target place"

%start program

%error-verbose

%pure-parser

%parse-param { Robots *program }

%lex-param { Robots *program }

%locations

%%

program: program robot 
	|robot 
	;
define_bot:TOKEN_ROBOT TOKEN_IDENTIFIER 
	{ 	
		program->createNew($2); 
	}
	;
robot:  define_bot TOKEN_BEGIN options targets global_variables declare_functions TOKEN_MAIN TOKEN_LPAR TOKEN_RPAR block_of_instructions TOKEN_END
	{ 
		program->robots.back()->add_global($5);
		program->robots.back()->add_function($10); 
	}
	;
targets: /* default target */  
	|targets TOKEN_KILLED TOKEN_OPER_REL TOKEN_UINT 
	{ 
		program->robots.back()->getBody()->addKilled(@2,$3,$4);
	}
	|targets TOKEN_VISIT TOKEN_LPAR places TOKEN_RPAR 
	{ 
		Body * b = program->robots.back()->getBody();
		for(size_t i = 0; i< $4.size();i++)
			b->addVisit($4[i]);
	}
	|targets TOKEN_KILL TOKEN_IDENTIFIER
	{ 
		ResolveName n;
		n.prefix = program->input;
		n.robot = program->robots.back();
		n.name = $3;
		n.line = @3;
		program->resolveName.push_back(n);
	}
	|targets TOKEN_VISIT_SEQUENCE TOKEN_LPAR places TOKEN_RPAR 
	{
		Body *b = program->robots.back()->getBody();
		b->addVisitSeq($4);
	}
	;
place: TOKEN_UINT 
	{ 
		$$ = new TargetVisit($1); 
	}
	|TOKEN_LSBRA TOKEN_UINT TOKEN_COMMA TOKEN_UINT TOKEN_RSBRA
	{
		$$ = new TargetVisit(-1);
		$$->initPosition(Rectangle($2,$4,15,15)); //TODO makro
	}
	| TOKEN_START TOKEN_LSBRA TOKEN_IDENTIFIER TOKEN_RSBRA 
	{
		$$ = new TargetVisit(-1);
		ResolveStart r;
		r.prefix = program->input;
		r.name = $3;
		r.line = @3;
		r.target = $$;
		program->resolveStart.push_back(r);
	}
	;
places: place
	{ 
		$$.clear(); 
		$$.push_back($1); 
	}
	| places TOKEN_COMMA place
	{
		$$ = $1; 
		$$.push_back($3); 
	}
	;
options: /* defaultne opsny, normalny default alebo ako boli nadekralovane */	
	| options TOKEN_OPTION TOKEN_ASSIGN TOKEN_UINT 
	{ 
		program->set($2,$4); 
	}	
	| options TOKEN_SKIN TOKEN_IDENTIFIER 
	{	
		program->robots.back()->setSkin(program->addSkin($3)); 
	}
	;
global_variables:	/*	ziadne parametre	*/ 
	{
		$$.clear();
	}
	| global_variables local_variables 
	{ 
		$$=$1; 
		$$.insert($$.end(), $2.begin(), $2.end());
	}
	;
type: simple_type 
	{ 
		$$ = $1; 
		program->robots.back()->declare_type();
	}
	| complex_type 
	{ 
		$$ = $1;
		program->robots.back()->declare_type();
	}
	; 
local_variables: type names TOKEN_SEMICOLON 
	{
		$$ = $2;	
		program->robots.back()->leave_type();
	}
	;
simple_type: TOKEN_VAR_REAL { $$ = program->robots.back()->find_type(TypeReal); } 
	|TOKEN_VAR_INT { $$ = program->robots.back()->find_type(TypeInteger); }
	|TOKEN_LOCATION{ $$ = program->robots.back()->find_type(TypeLocation);}
	|TOKEN_OBJECT{ $$ = program->robots.back()->find_type(TypeObject); }
	;
complex_type: simple_type ranges 
	{ 
		Create_type * t = $1; 
		while(!$2.empty())
		{
			t = program->robots.back()->find_array_type($2.back(),t);
			$2.pop_back();
		}
		Create_type y= *t;
		while (y.data_type!=NULL)
		{
			y = *y.data_type;
		}
		$$ = t;
	}
	;

ranges: TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { $$.push_back($2); }
	|ranges TOKEN_LSBRA TOKEN_UINT TOKEN_RSBRA { $$.push_back($3); }
	;

names_:	TOKEN_IDENTIFIER
	{ 
		$$.clear();
		Node *n = program->robots.back()->add($1);
		$$.push_back(new InstructionCreate(n)); 
	} 
	|TOKEN_IDENTIFIER TOKEN_ASSIGN expression 
	{ 
		$$.clear();
		Node *n = program->robots.back()->add($1);
		$$.push_back(new InstructionCreate(n)); 

		$$.push_back(new InstructionLoadLocal(n));
		Instructions ins = get_load_type(*program->robots.back()->active_type.top());
		$$.insert($$.end(), ins.begin(), ins.end());
		$$.insert($$.end(), $3.ins.begin(), $3.ins.end()); //naloadovana espresna
		Instruction * in = possible_conversion(program->robots.back()->active_type.top()->type,$3.output.back().type);
		if (in)
		{
			$$.push_back(in);
			$3.output.back() = *program->robots.back()->active_type.top();
		}
		ins = get_store_type( $3.output.back() );
		$$.insert($$.end(),ins.begin(), ins.end()); 
	} 
	|TOKEN_IDENTIFIER TOKEN_ASSIGN begin_type values end_type
	{ 
		$$.clear();
		Node *n = program->robots.back()->add($1);
		$$.push_back(new InstructionCreate(n)); 
		$$.push_back(new InstructionLoadLocal(n)); 
		for (int i = 1; i< $4.level; i++)
			$$.push_back(new InstructionDuplicate());

		$$.insert($$.end(), $4.ins.begin(), $4.ins.end());
	} 
	;
names: names_ { $$ = $1; }
	|names names_ { $$ = $1; $$.insert($$.end(), $2.begin(), $2.end()); }
	;
begin_type: TOKEN_BEGIN { program->robots.back()->declare_next(@1); }
	;
end_type: TOKEN_END { program->robots.back()->leave_type(); }
	;
values:	expression 
	{ 
		$$.ins.clear();
		$$.ins.push_back(new InstructionLoad(0));
		$$.ins.push_back(new InstructionLoad());
		$$.ins.insert($$.ins.end(),$1.ins.begin(), $1.ins.end());
		Instruction * in = possible_conversion( program->robots.back()->active_type.top()->type,$1.output.back().type);
		if (in)
		{
			$$.ins.push_back(in);
			$1.output.back() = *program->robots.back()->active_type.top();
		}
		if ($1.output.back()!=*program->robots.back()->active_type.top())
		{
			program->robots.back()->error(@1, Robot::ErrorConversionImpossible);
		}
		else
		{
			//loadneme to, kde sme sa dostali
			Instructions ins = get_load_type(*program->robots.back()->active_type.top());
			$$.ins.insert($$.ins.end(), ins.begin(), ins.end());
			//a storneme
			ins = get_store_type($1.output.back());
			$$.ins.insert($$.ins.end(), ins.begin(), ins.end());
			$$.level = 1;
		}
	} 
	| values TOKEN_COMMA expression 
	{
		$$.ins.clear();
		$$.ins = $1.ins;
		$$.ins.push_back(new InstructionLoad($1.level));
		$$.ins.push_back(new InstructionLoad());
		$$.ins.insert($$.ins.end(), $3.ins.begin(), $3.ins.end());
		Instruction * in = possible_conversion(program->robots.back()->active_type.top()->type,$3.output.back().type );
		if (in)
		{
			$$.ins.push_back(in);
			$3.output.back() = *program->robots.back()->active_type.top();
		}
		Instructions ins = get_store_type( $3.output.back());
		$$.ins.insert($$.ins.end(), ins.begin(), ins.end());
		if ($3.temp.back())
		{
			$$.ins.push_back(new InstructionRemoveTemp());
		}	
		$$.level = $1.level + 1;
	}
	| begin_type values end_type
	{ 
		$$.ins.clear();	
		$$.ins.push_back(new InstructionLoad(0)); 
		$$.ins.push_back(new InstructionLoad());
		for (int i = 1; i < $2.level; i++)
		{
			$$.ins.push_back(new InstructionDuplicate());
		}
		$$.ins.insert($$.ins.end(), $2.ins.begin(), $2.ins.end());
		$$.level = 1;
	}
	| values TOKEN_COMMA begin_type values end_type
	{
		$$.ins.clear();
		$$ = $1; 
		$$.ins.push_back(new InstructionLoad($1.level));
		$$.ins.push_back(new InstructionLoad());
		for (int i = 1; i < $4.level; i++)
		{
			$$.ins.push_back(new InstructionDuplicate());
		}
		$$.ins.insert($$.ins.end(),$4.ins.begin(), $4.ins.end());
		$$.level++;
	} // TODO addOputpuTokenNotDefined?
	;
declare_functions: /*	ziadne deklarovane funkcie	*/ 
			{ 
				std::vector<Parameter_entry> em;
				program->robots.back()->enter("main", em,program->robots.back()->find_type(TypeVoid)); 	
			}
		|declare_function_ 
		{ 
			$$ = $1;std::vector<Parameter_entry> em;
			program->robots.back()->enter("main", em, program->robots.back()->find_type(TypeVoid));
		}
		;

function_header:return_type function_name TOKEN_LPAR parameters_empty TOKEN_RPAR 
		{
			 $$ = $2;
			 program->robots.back()->enter($2,$4, $1); 
		} 
		;
function_name:	TOKEN_FUNCTION TOKEN_IDENTIFIER
		{
			$$ = $2;
			program->robots.back()->nested += $2 + DELIMINER_CHAR;
		}
		;
return_type:	TOKEN_VOID { $$ = program->robots.back()->find_type(TypeVoid);program->robots.back()->declare_type();}
		|type { $$ = $1; }
		;

parameters_empty:	{ $$.clear(); }
		| parameters { $$ = $1;}
		;
parameters:	type TOKEN_IDENTIFIER { $$.push_back(Parameter_entry($2,PARAMETER_BY_VALUE, program->robots.back()->add($2, $1))); }
		| parameters TOKEN_COMMA type TOKEN_IDENTIFIER { $$ = $1; $$.push_back(Parameter_entry($4,PARAMETER_BY_VALUE,program->robots.back()->add($4, $3))); }
		| TOKEN_REFERENCE type TOKEN_IDENTIFIER { $$.push_back(Parameter_entry($3,PARAMETER_BY_REFERENCE, program->robots.back()->add($3, $2))); }
		| parameters TOKEN_COMMA TOKEN_REFERENCE type TOKEN_IDENTIFIER 
		{ 
			$$.push_back(Parameter_entry($5,PARAMETER_BY_REFERENCE, program->robots.back()->add($5, $4))); 
		}
		;
declare_function_:	function_header block_of_instructions  
		{ 
			program->robots.back()->add_function($2);
			program->robots.back()->leave();
		} 
		|declare_function_ function_header block_of_instructions 
		{ 
			program->robots.back()->add_function($3); 
			program->robots.back()->leave();
		}
		;
number:		TOKEN_OPER_SIGNADD TOKEN_REAL 
		{ 
			if ($1 == OperationMinus ) 
			{
				$2*=-1;
			} 
			$$.ins.push_back(new InstructionLoad($2));
			$$.output.push_back(*program->robots.back()->find_type(TypeReal)); 
			$$.temp.push_back(false);
		} 
		|TOKEN_OPER_SIGNADD TOKEN_UINT 
		{ 
			if ($1 == OperationMinus) 
			{
				$2*=-1;
			} 
			$$.ins.push_back(new InstructionLoad($2)); 
			$$.output.push_back( *program->robots.back()->find_type(TypeInteger));
			$$.temp.push_back(false);
		}
		|TOKEN_REAL 
		{ 
			$$.ins.push_back(new InstructionLoad($1)); 
			$$.output.push_back(*program->robots.back()->find_type(TypeReal));
			$$.temp.push_back(false); 
		} 
		|TOKEN_UINT 
		{ 
			$$.ins.push_back(new InstructionLoad($1)); 
			$$.output.push_back(*program->robots.back()->find_type(TypeInteger));
			$$.temp.push_back(false); 
		} 
		|TOKEN_RND
		{
			$$.ins.push_back(new InstructionRandom()); 
			$$.output.push_back(*program->robots.back()->find_type(TypeInteger));
			$$.temp.push_back(true); 
		}
		;

begin:	TOKEN_BEGIN { program->robots.back()->core->depth++; program->robots.back()->defined.new_block();}
		;

end:	TOKEN_END { program->robots.back()->core->depth--; program->robots.back()->defined.leave_block();}
		;

block_of_instructions: begin commands_and_empty end 
		{ 
			$$.push_back(new InstructionBegin()); 
			$$.insert($$.end(), $2.begin(), $2.end());
			$$.push_back(new InstructionEndBlock()); 
		}
		;
commands_and_empty:  /* empty */ {$$.clear();}
		| commands {  $$ = $1; }
		;

commands: 	TOKEN_SEMICOLON { $$.clear(); }
		| matched {$$ = $1;}
		| commands matched { $$ = $1; $$.insert($$.end(), $2.begin(), $2.end()); }
		| unmatched { $$ = $1; }
		| commands unmatched { $$ = $1; $$.insert($$.end(), $2.begin(), $2.end()); }
		;
//FIXME dalo by sa aj inteligentjsie? Rozlisovat, ci som vytvorila premennu a potom oachat cyklus
cycle_for: TOKEN_FOR { program->robots.back()->core->depth++; $$.push_back(new InstructionBegin());program->robots.back()->defined.new_block();}
		;
command:	cycle_for TOKEN_LPAR init expression_bool TOKEN_SEMICOLON simple_command TOKEN_RPAR begin commands end 
		{ 
		//	INIT, BLOCK, COMMAND CONDITION
			if ($4.temp.back())
			{
				$4.ins.push_back(new InstructionRemoveTemp());
			}
			$9.push_back(new InstructionEndBlock($4.ins.size()+$6.size()+1));
			$9.insert($9.end(), $6.begin(), $6.end()); 
			$3.push_back(new InstructionMustJump($9.size()+1)); 
			$3.push_back(new InstructionBegin(program->robots.back()->core->depth));
			$4.ins.push_back(new InstructionJump(-1*$9.size()-$4.ins.size()-2,0));
			$9.insert($9.end(),$4.ins.begin(), $4.ins.end());
			$$ = $3;
			$$.insert($$.end(),$9.begin(), $9.end());
			$$.push_back(new InstructionEndBlock());
			$$.insert($$.begin(), $1.begin(), $1.end() );
			program->robots.back()->core->depth--;
			program->robots.back()->defined.leave_block();
		}
		|TOKEN_DO begin commands end TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR TOKEN_SEMICOLON 
		{ 
			if ($7.temp.back())
			{
				$7.ins.push_back(new InstructionRemoveTemp());
			}
			$$.push_back(new InstructionBegin(program->robots.back()->core->depth));
			$3.push_back(new InstructionEndBlock($7.ins.size()+1));
			$$.insert( $$.end(), $3.begin(), $3.end());
			$$.insert($$.end(),$7.ins.begin(), $7.ins.end()); 
			$$.push_back(new InstructionJump(-1*$$.size()-1,0));
		}
		|TOKEN_WHILE TOKEN_LPAR expression_bool TOKEN_RPAR begin commands end
		{
			if ($3.temp.back())
			{
				$3.ins.push_back(new InstructionRemoveTemp());
			}
			$$.push_back(new InstructionMustJump($6.size()+2));
			$$.push_back(new InstructionBegin(program->robots.back()->core->depth));
			$6.push_back(new InstructionEndBlock($3.ins.size()+1));
			$$.insert($$.end(),$6.begin(), $6.end());
			$$.insert($$.end(),$3.ins.begin(), $3.ins.end());
			$$.push_back(new InstructionJump(-1*$$.size(),0));
		}
		|TOKEN_RETURN expression TOKEN_SEMICOLON
		{
			$$.clear();
			$$.push_back(new InstructionLoadLocal(program->robots.back()->core->nested_function->return_var));
			Instructions ins = get_load_type(*program->robots.back()->core->nested_function->return_var->type_of_variable);
			$$.insert($$.end(), ins.begin(), ins.end());
			$$.insert($$.end(),$2.ins.begin(), $2.ins.end());
			
			/* Check for types compatibility */
			if (($2.output.back().type == TypeInteger) && (program->robots.back()->core->nested_function->return_var->type_of_variable->type == TypeReal))
			{
				if ($2.temp.back())
				{
					$$.push_back(new InstructionRemoveTemp());
				}
				$2.output.back() = *program->robots.back()->find_type(TypeReal);
				$$.push_back(new InstructionConversionToReal());
				$2.temp.back() = true;
			}
			else if (($2.output.back().type == TypeReal) && (program->robots.back()->core->nested_function->return_var->type_of_variable->type == TypeInteger))
			{
				if ($2.temp.back())
				{
					$$.push_back(new InstructionRemoveTemp());
				}
				$2.output.back() = *program->robots.back()->find_type(TypeInteger);
				$$.push_back(new InstructionConversionToInt());
				$2.temp.back() = true;
			}

			/* Check for types equality */
			if ($2.output.back()!= *program->robots.back()->core->nested_function->return_var->type_of_variable)
			{
				program->robots.back()->error(@1, Robot::ErrorConversionImpossible);
			}
			else
			{
				ins = get_store_type($2.output.back());
				$$.insert($$.end(), ins.begin(), ins.end());
			}
			if ($2.temp.back())
			{
				$$.push_back(new InstructionRemoveTemp());
			}
			$$.push_back(new InstructionLoadLocal(program->robots.back()->core->nested_function->return_var));// da sa dat aj na konci, vestko  uz je upratane
			$$.push_back(new InstructionReturn(program->robots.back()->core->depth));	
		}
		|TOKEN_RETURN TOKEN_SEMICOLON 
		{
			$$.push_back(new InstructionReturn(program->robots.back()->core->depth));
		} //v node zostane predchadzajuca hodnota//TODO ocheckovat vsetky vetvy
		
		|TOKEN_BREAK TOKEN_SEMICOLON 
		{
			$$.push_back(new InstructionBreak(program->robots.back()->core->depth));
		}
		|TOKEN_CONTINUE TOKEN_SEMICOLON  //TODO nobreakable veci?
		{
			$$.push_back(new InstructionContinue(program->robots.back()->core->depth));
		}
		|simple_command TOKEN_SEMICOLON {$$ = $1;}
		;
command_var: local_variables { $$ = $1;} //tu nebude ziadny output, vyriesene v Locale;
		| command { $$ = $1;} //vyriesene v commande
		;
simple_command:	assign {$$ = $1;} //tu nie je ziadne output
		|unary_var 
		{ 
			$$ = $1.ins; 
			if($1.output.size()>0)
			{
				$$.push_back(new InstructionPop());
				if($1.temp.back())
					$$.push_back(new InstructionRemoveTemp());
			}
		} //Plus Plus Plus neee:)
		;
assign: variable_left TOKEN_ASSIGN expression 
	{
		if (($1.output.back().type == TypeInteger)&&($3.output.back().type == TypeReal))
		{
			if ($3.temp.back())
			{
				$$.push_back(new InstructionRemoveTemp());
			}
			$3.ins.push_back(new InstructionConversionToInt());
			$3.temp.back() = true;
		}
		else if	(($1.output.back().type == TypeReal)&&($3.output.back().type == TypeInteger))
		{
			if ($3.temp.back())
			{
				$$.push_back(new InstructionRemoveTemp());
			}
			$3.ins.push_back(new InstructionConversionToReal());
			$3.temp.back() = true;
		}
		else if ($1.output.back()!=$3.output.back())
		{
			program->robots.back()->error(@2, Robot::ErrorConversionImpossible);
		}
		$$ = $1.ins;
		Instructions ins = get_load_type( $1.output.back() );
		$$.insert($$.end(), ins.begin(), ins.end()); 
		$$.insert($$.end(), $3.ins.begin(), $3.ins.end());
		ins = get_store_type( $3.output.back() );
		$$.insert($$.end(),ins.begin(), ins.end());

		if ($3.temp.back())
			$$.push_back(new InstructionRemoveTemp());
		}
		;
array: TOKEN_IDENTIFIER array_access 
		{
			$$ = ident_load(@1,program->robots.back(), $1);
			$$.ins.insert($$.ins.end(), $2.ins.begin(), $2.ins.end());
			$$.temp.push_back(false);
			Create_type tt = $$.output.back();	
			for(int i =$2.dimension; i>0; i--) 
			{
				if ($$.output.back().data_type == NULL)
				{
					program->robots.back()->error(@1,Robot::ErrorOutOfRange);
					break;
				}
				
				Create_type * t = $$.output.back().data_type;
				$$.output.back() = *t;
			}
		}
		|TOKEN_SEEN TOKEN_LSBRA expression TOKEN_RSBRA
		{
			$$.clear();
			$$.ins = $3.ins;
			$$.output.push_back(*program->robots.back()->find_type(TypeObject));
			Instruction * in = possible_conversion($3.output.back().type, TypeInteger);
			if (in!=NULL)
			{
				$$.ins.push_back(in);
			}
			$$.ins.push_back(new InstructionEye());
			$$.temp.push_back(true);
		}
		;

call_fce:	TOKEN_IDENTIFIER TOKEN_LPAR call_parameters TOKEN_RPAR 
		{ 
			Function * f =program->robots.back()->find_f($1); 
			if (f == NULL)
			{
				program->robots.back()->error(@1,Robot::ErrorFunctionNotDefined,$1); 
				$$.clear();
				$$.output.push_back(*program->robots.back()->find_type(TypeUndefined));
				$$.temp.push_back(true);
			}
			else 
			{
				if (f->parameters.size()!=$3.output.size()) 
				{
					program->robots.back()->error(@1,Robot::ErrorWrongNumberOfParameters);
				}
				else
				{
					size_t last = 0;
					for (size_t i= 0; i< f->parameters.size(); i++)
					{
						if (f->parameters[i].val_type == PARAMETER_BY_VALUE)
						{
							$$.ins.push_back(new InstructionCreate(f->parameters[i].node));
							$$.ins.push_back(new InstructionLoadLocal(f->parameters[i].node));
							Instructions ins = get_load_type(*f->parameters[i].node->type_of_variable);
							$$.ins.insert($$.ins.end(), ins.begin(), ins.end());
						}
						while ( last < $3.ins.size()) //od i-teho az po i+1 NULL
						{
							if ($3.ins[last] == NULL)
							{
								last++;
								break;
							}
							$$.ins.push_back($3.ins[last]);
							last++;
						}
						//we finished loading parameter value
						if (($3.output[i].type == TypeReal)
								&&(f->parameters[i].node->type_of_variable->type == TypeInteger))
						{
							if ($3.temp[i])
							{
								$$.ins.push_back(new InstructionRemoveTemp());
							}
							$$.ins.push_back(new InstructionConversionToInt());
							$3.temp[i] = true;
							$3.output[i] = *program->robots.back()->find_type(TypeInteger);
						}
						if (($3.output[i].type == TypeInteger)
								&&(f->parameters[i].node->type_of_variable->type == TypeReal))
						{
							if ($3.temp[i])
							{
								$$.ins.push_back(new InstructionRemoveTemp());
							}
							$3.temp[i] = true;
							$$.ins.push_back(new InstructionConversionToReal());
							$3.output[i] = *program->robots.back()->find_type(TypeReal);
						}
						if ($3.output[i] != *f->parameters[i].node->type_of_variable)
						{
							program->robots.back()->error(@1, Robot::ErrorConversionImpossible);
							break;
						}

						if (f->parameters[i].val_type == PARAMETER_BY_VALUE)
						{
							Instructions ins = get_store_type($3.output[i]);
							$$.ins.insert($$.ins.end(), ins.begin(), ins.end());
						}
						else
							$$.ins.push_back(new InstructionStoreRef(f->parameters[i].node));
					}
					$$.ins.push_back(new Call(f));
					if (f->return_var->type_of_variable->type == TypeVoid)
						$$.output.clear();
					else
						$$.output.push_back(*f->return_var->type_of_variable);
				}
				for (size_t i =0; i< $3.temp.size(); i++)
				{
					if ($3.temp[i])
						$$.ins.push_back(new InstructionRemoveTemp()); //likvidovnie premennyh obsadenych v pamati

				}
				if (f->return_var->type_of_variable->type!= TypeVoid)
					$$.temp.push_back(true);
				else 
					$$.temp.push_back(false);
			}
		}
		|TOKEN_OBJECT_FEATURE TOKEN_LPAR call_parameters TOKEN_RPAR 
		{
			$$.clear();
			$$ = feature(@1,program->robots.back(), $1, $3);
			$$.temp.push_back(true);
		} 
		;

call_parameters: expression 
		{
			$$ = $1; 
			$$.ins.push_back(NULL);
		} 
		| /* ziadny parameter */ { $$.clear(); }
		|call_parameters TOKEN_COMMA expression 
		{
			$$.clear();
			$3.ins.push_back(NULL); //zalozka, po kolkatich instrukciach mi konci output, TODO zmenit
			$$.ins = $1.ins;
			$$.ins.insert($$.ins.end(),$3.ins.begin(), $3.ins.end());
			$$.output = $1.output;
			for (size_t i =0; i< $3.output.size();i++) 
			{
				$$.output.push_back($3.output[i]);
				$$.temp.push_back($3.temp[i]);
			}
		}
		;
matched:TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE matched 
	{
		$$.clear();
		if ($3.temp.back())
			{
				$3.ins.push_back(new InstructionRemoveTemp());
			}
		$5.push_back(new InstructionMustJump($7.size()));
		$3.ins.push_back(new InstructionJump(0,$5.size()));
		$$ = $3.ins;
		$$.insert($$.end(),$5.begin(), $5.end());
		$$.insert($$.end(),$7.begin(), $7.end());
	}
	| command_var {$$ = $1;} //prazdy output
	|block_of_instructions { $$ = $1;}
	;
unmatched:	TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR block_of_instructions 
		{
			if ($3.temp.back())
			{
				$3.ins.push_back(new InstructionRemoveTemp());
			}
			$3.ins.push_back(new InstructionJump(0,$5.size()));
			$$ = $3.ins;
			$$.insert($$.end(),$5.begin(), $5.end());
		}
	|TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR command 
	{
		if ($3.temp.back())
			{
				$3.ins.push_back(new InstructionRemoveTemp());
			}
		$3.ins.push_back(new InstructionJump(0,$5.size()));
		$$ = $3.ins;
		$$.insert($$.end(),$5.begin(), $5.end());
	}
	|TOKEN_IF TOKEN_LPAR expression_bool TOKEN_RPAR matched TOKEN_ELSE unmatched 
	{
		if ($3.temp.back())
			{
				$3.ins.push_back(new InstructionRemoveTemp());
			}
		$5.push_back(new InstructionMustJump($7.size())); //outputy sa tymto znicia
		$3.ins.push_back(new InstructionJump(0,$5.size()));
		$$ = $3.ins;
		$$.insert($$.end(),$5.begin(), $5.end());
		$$.insert($$.end(),$7.begin(), $5.end());
	}
	;
init: 	local_variables { $$ = $1;}
		| assign TOKEN_SEMICOLON {$$ = $1;}
		;
unary_var: variable {$$ = $1;}
		|variable TOKEN_PLUSPLUS 
		{
			$$ = $1; 
			if($$.output.back() == TypeReal) 
				$$.ins.push_back(new InstructionPlusPlusReal());
			else if ($$.output.back() == TypeInteger) 
				$$.ins.push_back(new InstructionPlusPlusInteger());
			else program->robots.back()->error(@2,Robot::ErrorOperationNotSupported);
			$$.temp.push_back($1.temp.back());
		} 
		|variable TOKEN_MINUSMINUS 
		{
			 $$ = $1; 
			 if($$.output.back() == TypeReal)
				 $$.ins.push_back(new InstructionMinusMinusReal());
			else if ($$.output.back() == TypeInteger) 
				$$.ins.push_back(new InstructionMinusMinusInteger());
			else program->robots.back()->error(@2,Robot::ErrorOperationNotSupported);
			$$.temp.push_back($1.temp.back());
		}
		;
variable_left:TOKEN_IDENTIFIER 
		{
			$$ = ident_load(@1,program->robots.back(), $1); //ale moze byt aj array alebo location
			$$.temp.push_back(false);
		}
		|variable_left TOKEN_DOT TOKEN_IDENTIFIER 
		{ 
			
			for ( size_t i =0; i<$$.output.back().nested_vars.size(); i++)
				if ($$.output.back().nested_vars[i].name == $3)
				{ 
					Create_type t = *$$.output.back().nested_vars[i].type; 
					$$.output.pop_back();
					$$.output.push_back(t);
					$$.ins.push_back(new InstructionLoad((int)i));
					$$.ins.push_back(new InstructionLoad());
					break;
				}
			$$.temp.push_back($1.temp.back());
		}
		|array { $$ = $1; }
		;
variable: 	TOKEN_THIS 
		{
			$$ = ident_load(@1,program->robots.back(), "this");
			$$.temp.push_back(false);
		}
		| TOKEN_NULL
		{
			$$ = ident_load(@1,program->robots.back(), "NULL");
			$$.temp.push_back(false);
		}
		|call_fce { $$ = $1; //TODO ak je to funkci a s navratovou hodnotou, kontrola vsetkych vetvi, ci obsahuju return; main je procedura:)
		}	
		|variable_left { $$ = $1; }
		;
		
array_access: TOKEN_LSBRA exps TOKEN_RSBRA 
		{ 
			$$.dimension = 0;
			$$.ins.clear(); //exps musia by integery
			for (size_t i =0; i< $2.ins.size(); i++)
			{
				if ($2.ins[i] == NULL)
				{
					$$.ins.push_back(new InstructionLoad());
					if ($2.temp[i])
						$$.ins.push_back(new InstructionRemoveTemp());
					$$.dimension++;
				}
				else
					$$.ins.push_back($2.ins[i]);
			}

		} //vezme zo stacku dve hodnoty, pouzije a na stack prihodi novu z tempu
		|array_access TOKEN_LSBRA exps TOKEN_RSBRA 
		{
			$$ = $1;
			for ( size_t i = 0; i < $3.ins.size();i++)
			{
				if ($3.ins[i] == NULL)
				{
					$$.ins.push_back(new InstructionLoad());
					if ($3.temp[i])
						$$.ins.push_back(new InstructionRemoveTemp());
					$$.dimension++;
				}
				else
					$$.ins.push_back($3.ins[i]);
			}
		} 
		;
exps: expression {$$ = $1;$$.ins.push_back(NULL);} //Hack
		| exps TOKEN_COMMA expression 
		{ 
			$$.clear();
			$1.ins.push_back(NULL);
			$$.ins = $1.ins;
			$$.ins.insert($$.ins.end(), $3.ins.begin(), $3.ins.end());
			$$.output = $1.output;
			for (size_t i =0; i<$1.output.size(); i++)
				$$.output.push_back($1.output[i]); //aj tak tu bude len jeden output, TODO
		}
		;
expression_base: unary_var { $$ = $1; }
		|number{$$ = $1;}
		|TOKEN_LPAR expression_bool TOKEN_RPAR {$$ = $2;}
		;
expression_mul:expression_base { $$ = $1; }
		|expression_mul TOKEN_OPER_MUL expression_base { 
			$$.clear();
			$$.ins = $1.ins;
			$$.ins.insert($$.ins.end(), $3.ins.begin(), $3.ins.end());
			if ($1.temp.back())
			{
				$$.ins.push_back(new InstructionRemoveTemp());
			}
			if ($3.temp.back())
				$$.ins.push_back(new InstructionRemoveTemp());
			Element e = operMul(@2, program->robots.back(), $2, $1.output.back(), $3.output.back());
			$$.ins.insert($$.ins.end(), e.ins.begin(),e.ins.end());
			$$.output = e.output;
			$$.temp.push_back(true);
		}
		;
expression_add: expression_mul { $$ = $1;}
		|expression_add TOKEN_OPER_SIGNADD expression_mul
		{
			$$.clear();
			$$.ins = $1.ins;
			$$.ins.insert($$.ins.end(), $3.ins.begin(), $3.ins.end());
			if ($1.temp.back())
			{
				$$.ins.push_back(new InstructionRemoveTemp());
			}
			if ($3.temp.back())
				$$.ins.push_back(new InstructionRemoveTemp());
			Element e = (operAdd(@2, program->robots.back(),$2,$1.output.back(), $3.output.back()));
			$$.ins.insert($$.ins.end(), e.ins.begin(), e.ins.end());
			$$.output = e.output;
			$$.temp.push_back(true);
		}
		;
expression:	expression_add { $$ = $1; }
		;
expression_bool_base: expression { $$ = $1;}
		|expression TOKEN_OPER_REL expression 
		{
			$$.clear();
			$$.ins = $1.ins;
			$$.ins.insert($$.ins.end(), $3.ins.begin(), $3.ins.end());
			if ($1.temp.back())
				$$.ins.push_back(new InstructionRemoveTemp());
			if ($3.temp.back())
				$$.ins.push_back(new InstructionRemoveTemp());
			Element e = operRel(@2,program->robots.back(),$2,$3.output.back(),$1.output.back());
			$$.ins.insert($$.ins.end(), e.ins.begin(), e.ins.end());
			$$.output = e.output;
			$$.temp.push_back(true);
		}
		;
expression_bool_or: expression_bool_base {$$ = $1; }
		| expression_bool_or TOKEN_BOOL_OR expression_bool_base
		{
			$$.clear();
			$$.ins = $1.ins;
			$$.ins.insert($$.ins.end(), $3.ins.begin(), $3.ins.end());
			Element e = operOr(@2,program->robots.back(),$2,$1.output.back(),$3.output.back());
			$$.ins.insert($$.ins.end(), e.ins.begin(),e.ins.end());
			$$.output = e.output; //aj tak by tu vzy mal byt integer
			$$.temp.push_back(true);
		}
		;
expression_bool:	expression_bool_or { $$ = $1;}
		| expression_bool TOKEN_BOOL_AND expression_bool_or 
		{
			$$.clear();
			$$.ins = $1.ins;
			$$.ins.insert($$.ins.end(), $3.ins.begin(), $3.ins.end()); 
			if ($1.output.back().type == TypeReal) 
			{
				if ($1.temp.back())
				{
					$$.ins.push_back(new InstructionRemoveTemp());
				}
				$$.ins.push_back(new InstructionConversionToInt());
				$$.output.push_back(Create_type(TypeInteger));
			}
			else if ($1.output.back().type!= TypeInteger) 
				program->robots.back()->error(@2,Robot::ErrorConversionImpossible); 

			if ($3.output.back().type == TypeReal) 
			{
				if ($3.temp.back())
				{
					$$.ins.push_back(new InstructionRemoveTemp());
				}
				$$.ins.push_back(new InstructionConversionToInt());
				$$.output.push_back(Create_type(TypeInteger));
			}
			else if ($3.output.back().type!= TypeInteger) 
				program->robots.back()->error(@2,Robot::ErrorConversionImpossible); 
			$$.ins.push_back(new InstructionAnd);
			$$.temp.push_back(true);
		}
	;
%%

static void yyerror(unsigned *line, Robots* ctx, const char *message)
{
	ctx->parseError( deconvert<const char *>(message) +" at line " + deconvert<int>(*line) +"\n");
}

