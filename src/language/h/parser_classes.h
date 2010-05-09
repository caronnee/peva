#ifndef ___PARSER_CLASSES____
#define ___PARSER_CLASSES____
#include <vector>
#include <deque>
#include "instructions.h"
#include "parser_classes.h"

typedef std::deque<Instruction *> Instructions;
typedef std::vector<Variable *> Values;
typedef std::vector<Create_type> Expressions;

struct Element
{
	Instructions ins;
	Expressions output;
	std::vector<bool> temp;
	void clear();
};

//TODO zmenit na nieco lepsie
struct Constr
{
	std::string id;
	Instructions ins;
	std::vector<Create_type> output;
	bool default_set;
	Constr();
	Constr(std::string a);
	Constr(std::string a, Instructions i, Expressions e);
};

#endif
