#ifndef HEADER_H_
#define HEADER_H_

#include <string>
#include "./tree/my_stack.h"

enum Operation
{
	OperationPlus,
	OperationMinus,
	OperationMultiply,
	OperationDivide,
	OperationModulo,

	OperationLess,
	OperationLessEqual,
	OperationGreater,
	OperationGreaterEqual,
	OperationEqual,
	OperationNotEqual,

	OperationAnd,
	OperationOr,
	OperationNot,

	OperationBoolAnd,
	OperationBoolOr,
	OperationBoolNot
};
struct expr
{
	Type output;
};

struct Constr
{
	std::string id;
	Instructions ins;
	bool default_set;
	Constr()
	{
		default_set = false;
		id ="";
	}
	Constr(std::string a)
	{
		id = a;
		default_set = false;
	}
	Constr(std::string a, int def)
	{
		id  = a;
		default_set = true;
		ins.push_back(new InstructionLoad(def));
	}
	Constr(std::string a, Instructions i)
	{
		id = a;
		ins = i;
		default_set = true;
	}
};

struct Lval {
	Operation operation;
	int number;

	std::string ident; 
	std::vector<Constr> idents;

	float f_number;

	std::vector<int> ranges;

	Instructions block;

	Node * node;
	std::vector<Node *> nodes;

	std::vector< Array *> arrays;
	Array * array;

	Create_type type;

	Instructions instructions;
};

// lex interface
#define YY_DECL	    int yylex(Lval *lv, unsigned *l, Program *c)
YY_DECL;

// parser interface
int yyparse();

#endif
