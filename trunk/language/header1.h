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

struct Lval {
	Operation operation;
	int number;
	std::string ident; //+mozno este nejake sa njdu
	float f_number;
	std::vector<Array> arrays;
	//block
	Instructions block;
	std::vector<Node *> names;
	bool is_integer;
	Node * node;
};

// lex interface
#define YY_DECL	    int yylex(Lval *lv, unsigned *l, Program *c)
YY_DECL;

// parser interface
int yyparse();

#endif
