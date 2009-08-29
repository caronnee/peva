#ifndef HEADER_H_
#define HEADER_H_

#include <string>
#include "./robot.h"
#include "position.h"
#include "enums.h"

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
	
	Position position;
	std::vector<Position> positions;
};

// lex interface
#define YY_DECL	    int yylex(Lval *lv, unsigned *l, Robots *c)
YY_DECL;

// parser interface
int yyparse();

#endif
