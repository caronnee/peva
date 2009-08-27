#ifndef HEADER_H_
#define HEADER_H_

#include <string>
#include "./robot.h"

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
enum Options
{
	OptionHealth,
	OptionSeeX,
	OptionSeeY,
	OptionMemory,
	OptionAttack,
	OptionDefense,
	OptionMisilleAttack,
	OptionMisilleHealth,
	OptionId
};

enum ObjectFeatures
{
	FeatureIsPlayer,
	FeatureIsWall,
	FeatureIsMissille,
	FeatureIsMoving,
	FeatureLocate,
	FeatureStep,
	FeatureShoot,
	FeatureHit,
	FeatureTurn,
	FeatureTurnL,
	FeatureTurnR,
	FeatureWait,
	FeatureSee
};
struct Expr
{
	Instructions ins;
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
	Options op;
	Expr e;
};

// lex interface
#define YY_DECL	    int yylex(Lval *lv, unsigned *l, Program *c)
YY_DECL;

// parser interface
int yyparse();

#endif
