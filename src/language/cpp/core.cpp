#include <cstdio>
#include "../h/core.h"
#include "../../add-ons/h/macros.h"

Core::Core(TypeContainer * t)
{
	typeContainer = t;
	PC =0;
	values.clear();	
	depth = 0;
	body = new Body();
	savedVar = memory.dev_null();
}

void Core::save(int j)
{	
	PCs.push_back(PC);
	PC = j-1;
}

void Core::restore() 
{
	if ( nested_functions.empty() ) //FIXME nikdy nemoze nastat
	{
		nested_functions.push_back(nested_function);
		return;
	}
	memory.freeParameters(nested_function);
	nested_function->return_var->var.pop_back(); //zmazanie navratovej hodnoty
	nested_functions.pop_back();
	nested_function = nested_functions.empty()? NULL:nested_functions.back();

	PC = PCs.back();
	PCs.pop_back();
	TEST("Context restored" << PC)
}
Variable * Core::getVariableFromStack()
{
	if (values.empty())
	{
		TEST("Error value not loaded!")
		return memory.dev_null();
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
		TEST("Error - array not loaded!")
		addValue(memory.dev_null());
		return;
	}
	Variable * v = values.back();
	values.pop_back();
	if (v->array.range <= range)
	{
		TEST("Error - array out of range, which is:" << v->array.elements.size() << " against " << range )
		addValue(memory.dev_null());
		return;
	}
	return addValue(v->array.elements[range]);
}
void Core::addValue(Variable *v)
{
	//restriction on number of variables in stack
	if (values.size() >=10000)
		return;
	values.push_back(v);
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
