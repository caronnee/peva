#ifndef ___VAR___
#define ___VAR___

#include<string>
#include<vector>
#include "object.h"
#include "types.h"
#include "simple_types.h"

struct Variable;

struct Array
{
	int range; //rozmer pola
//	Type element_type; //netreba, type je aj tak vo variabloch:)
	std::vector<Variable* > elements;
};

struct Variable // struktura premennych
{
	size_t owner;
	int active; 
	unsigned int last_access; //z  tohoto sa vypocita penalizacia
	int integerValue;
	float realValue;
	Array array;
	Object * objectValue;
	Variable();
	Variable(std::string s);
///	void set_variable(Type t);
	void copyValue(Variable * v);
};



#endif
