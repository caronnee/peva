#ifndef HEADER_H_
#define HEADER_H_

#include <string>
#include "robot.h"
#include "position.h"
#include "enums.h"
#include "parser_classes.h"

struct Lval {
	
	int depth;

	Operation operation;
	int number;

	std::string ident; 
	std::vector<Constr> idents; //meno a defaultna hodnota, ak bola nejaka

	float f_number;

	std::vector<int> ranges;

	Node * node;
	std::vector<Node *> nodes; //kde su ulozene premenne

	std::vector< Array *> arrays;
	Array * array;

	Create_type* type;

	Instructions instructions;

	Parameter_entry entry;
	std::vector<Parameter_entry> entries;

	ObjectFeatures of;
	Options op;
	
	Position position;
	std::vector<Position> positions;

	Element output;

};

// lex interface
#define YY_DECL	    int yylex(Lval *lv, unsigned *l, Robots *c)
YY_DECL;

// parser interface
int yyparse();

#endif
