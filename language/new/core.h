#ifndef ___CORE____
#define ___CORE____

#include "memory.h"
#include "variable.h"

struct Value
{
	Variable hlp;
	Variable * loaded;
};

struct Core
{
	size_t PC;
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
};
#endif
