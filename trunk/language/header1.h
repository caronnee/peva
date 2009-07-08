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

	std::string ident; 
	std::vector<std::string> idents;

	float f_number;

	std::vector<int> ranges;

	Instructions block;

	Node * node;
	std::vector<Node *> nodes;
};

// lex interface
#define YY_DECL	    int yylex(Lval *lv, unsigned *l, Program *c)
YY_DECL;

// parser interface
int yyparse();

#endif
