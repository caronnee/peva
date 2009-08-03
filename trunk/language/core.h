#ifndef ___CORE____
#define ___CORE____

#include "memory.h"
#include "variable.h"
#include "functions.h"

struct Value
{
	Variable hlp;
	Variable * loaded;
};

struct Core
{
	size_t PC;
	std::vector<size_t> PCs;
	Function * nested_function;
	std::vector<Function *> functions;
	std::vector<Function *> nested_functions;
	int depth;
	bool error;
	Robot_body * robot; //periferie, stav robota, interakcia s mapou
//	Map * map;
	Memory memory;
	std::vector<Value> values;	
	Core()
	{
		error = false;
		robot = new Robot_body();
	}
	void save(int j)
	{
		PCs.push_back(PC);
		PC = j-1;
	}
	void restore() //+ pushnut vsetky parametre zadanej funkcie o jedno
	{
		if (nested_functions.size() == 0)
		{
			nested_function =NULL;
			return;
		}
		for(size_t i =0; i< nested_function->parameters.size(); i++)
		{
			nested_function->parameters[i].node->var.pop_back();
		}
		nested_function = nested_functions.back();
		nested_functions.pop_back();
		PC = PCs.back();
		PCs.pop_back();
		std::cout << "Restored" << PC << std::endl;
	}
};
#endif
