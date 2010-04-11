#include <cstdio>
#include "../h/core.h"
#include "../../add-ons/h/macros.h"

Core::Core(TypeContainer * t)
{
	typeContainer = t;
	PC =0;
	values.clear();	
	error = false;
	depth = 0;
	body = new Body();
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
	nested_function = nested_functions.back();
	nested_functions.pop_back();
	PC = PCs.back();
	PCs.pop_back();
	TEST("Context restored" << PC)
}
Variable * Core::getVariableFromStack()
{
	if (values.empty())
	{
		TEST("Error value not loaded!")
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
void Core::reset()
{

}
void Core::loadElement(int range)
{
	if (values.empty())
	{
		TEST("Error - array not loaded!")
		values.push_back(memory.random());
		return;
	}
	Variable * v = values.back();
	values.pop_back();
	if (v->array.elements.size() - range <= 0)
	{
		TEST("Error - array out of range, which is:" << v->array.elements.size() )
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
void Core::copyVariable()
{
	Variable * right = getVariableFromStack();
	Variable * left = getVariableFromStack();
	left->copyValue(right);
}
Core::~Core()
{
	delete body;
	while (!functions.empty())
	{
		Function * f = functions.back();
		delete f;
		functions.pop_back();
	}
}
