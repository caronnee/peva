#include "core.h"

Core::Core()
{
	PC =0;
	values.clear();	
	error = false;
	robot = new Robot_body();
	depth = 0;
}

void Core::save(int j)
{
	PCs.push_back(PC);
	PC = j-1;
}

void Core::restore() //+ pushnut vsetky parametre zadanej funkcie o jedno
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

