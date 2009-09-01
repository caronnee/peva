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
	Type element_type;
	std::vector<Variable* > elements;
};
struct Variable // struktura premennych
{
	size_t owner;
	Type type;
	int active; //bola deklarovana v danom bloku, TODO zistit, ci sa este pouziva
	unsigned int last_access; //z  tohoto sa vypocita penalizacia
	int integerValue;
	float realValue;
	Array array;
	Object * objectValue;
	Variable();
	Variable(std::string s,Type t);
	void set_variable(Type t);
};



#endif
