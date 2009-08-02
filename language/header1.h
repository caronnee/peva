#ifndef HEADER_H_
#define HEADER_H_

#include <string>
#include "./program.h"

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
enum ObjectFeatures
{
	FeatureIsPlayer,
	FeatureIsWall,
	FeatureIsMissille,
	FeatureIsMoving,
	FeatureLocate
};
struct expr
{
	Type output;
};

struct Lval {
	
	int depth;

	Operation operation;
	int number;

	std::string ident; 
	std::vector<Constr> idents;

	float f_number;

	std::vector<int> ranges;

	Instructions block;

	Node * node;
	std::vector<Node *> nodes; //kde su ulozene premenne

	std::vector< Array *> arrays;
	Array * array;

	Create_type type;

	Instructions instructions;

	Parameter_entry entry;
	std::vector<Parameter_entry> entries;

	ObjectFeatures of;
};

// lex interface
#define YY_DECL	    int yylex(Lval *lv, unsigned *l, Program *c)
YY_DECL;

// parser interface
int yyparse();

#endif
