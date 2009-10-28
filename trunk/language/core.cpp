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
	std::cout << "Context restored" << PC << std::endl;
}
Variable * Core::getVariableFromStack()
{
	if (values.empty())
	{
		return memory.random();
	}
	Variable * v = values.back();
	values.pop_back();
	return v;
}
int Core::getIntFromStack()
{
	return getVariableFromStack()->integerValue;
}
float Core::getFloatFromStack()
{
	return getVariableFromStack()->realValue;
}
void Core::loadElement(int range)
{
	if (values.empty())
	{
		values.push_back(memory.random());
		return;
	}
	Variable * v = values.back();
	values.pop_back();
	if (v->array.elements.size() - range <= 0)
	{
		std::cout << "Loading WRONG element due to out of range"; getc(stdin);
		values.push_back(memory.random());
		return;
	}
	return values.push_back(v->array.elements[range]);
}
Object * Core::getObjectFromStack()
{
	return getVariableFromStack()->objectValue;
}
void Core::saveInteger()
{
	int right = getIntFromStack();
	getVariableFromStack()->integerValue = right;	
}
void Core::saveFloat()
{
	float right = getFloatFromStack();
	getVariableFromStack()->realValue = right;
}
void Core::saveObject()
{
	Object * right = getObjectFromStack();
	getVariableFromStack()->objectValue = right;
}
void Core::switchVariable()
{
	Variable * right = getVariableFromStack();
	Variable * left = getVariableFromStack();
	right->swapValue(left);
}
