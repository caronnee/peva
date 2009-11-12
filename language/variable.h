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
	std::vector<Variable* > elements;
};

struct Variable // struktura premennych
{
	size_t ID;
	size_t owner;
	size_t last_access; //z  tohoto sa vypocita penalizacia
	int integerValue;
	float realValue;
	Array array;
	Object * objectValue;
	Variable(size_t t = 0);
	Variable(std::string s);
	void copyValue(Variable * v);
	void swapValue(Variable * v);
private:
	void reset();
public:
	~Variable();
};



#endif
