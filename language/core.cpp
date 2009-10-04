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
int Core::getIntFromStack()
{
	int i;
	if (!values.empty()) //TODO throw exception
	{
		i = values.back()->integerValue;
		values.pop_back();
		return i;
	}
	return rand();
}
float Core::getFloatFromStack()
{
	float i;
	if (!values.empty()) //TODO throw exception
	{
		i = values.back()->realValue;
		values.pop_back();
		return i;
	}
	return rand();
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
	if (v->array.elements.size() - range < 0)
	{
		values.push_back(memory.random());
		return;
	}
	return values.push_back(v->array.elements[range]);
}
Object * Core::getObjectFromStack()
{
	Object * o = NULL;
	if (!values.empty())
	{
		o = values.back()->objectValue;
		values.pop_back();
	}
	return o;
}
void Core::saveInteger()
{
	int right = getIntFromStack();
	if (values.empty())
		return;
	values.back()->integerValue = right;
	values.pop_back();
}
void Core::saveFloat()
{
	float right = getFloatFromStack();
	if (values.empty())
		return;
	values.back()->realValue = right;
	values.pop_back();
}
void Core::saveObject()
{
	Object * right = getObjectFromStack();
	if (values.empty())
		return;
	values.back()->objectValue = right;
	values.pop_back();
}
