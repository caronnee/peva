#ifndef ___CORE____
#define ___CORE____

#include "memory.h"
#include "variable.h"
#include "functions.h"

typedef std::vector<Variable *> Values;

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
	Memory memory;
	Values values;	
	Core();
	void save(int j);
	void restore(); //+ pushnut vsetky parametre zadanej funkcie o jedno
	int getIntFromStack();
	float getFloatFromStack(); //dalej su iba object a location
	Object * getObjectFromStack();
};
#endif
