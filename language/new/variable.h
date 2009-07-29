#ifndef ___VAR___
#define ___VAR___

#include<string>
#include<vector>
#include "object.h"
#include "types.h"
#include "simple_types.h"

struct Array;

struct Variable // struktura premennych
{
	std::string name;
	Type type;
	int active; //bola deklarovana v danom bloku
	unsigned int last_access; //z  tohoto sa vypocita penalizacia
	int IntegerValue;
	float RealValue;
	Array * array;
	Object * ObjectValue;

	Variable();
	Variable(std::string s,Type t);
	void set_variable(Type t);
};

struct Array
{
	int range; //rozmer pola
	Type element_type;
	std::vector<Variable* > elements;
};

#endif
