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
//	Robot_body * robot; //periferie, stav robota, interakcia s mapou
//	Map * map;
	Memory memory;
	std::vector<Value> values;	
	Core()
	{
		error = false;
//		robot = new Robot_body();
	}
	void save(int j);
	void restore(); //+ pushnut vsetky parametre zadanej funkcie o jedno
};
#endif
