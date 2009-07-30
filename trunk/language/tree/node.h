#ifndef ___NODES___
#define ___NODES___

#include <string> 
#include <vector>
#include <list>
#include "../core.h"
#include "typedefs.h"

bool is_simple();

struct Create_type
{
	int range;
	Create_type * data_type;
	Type type;
	Create_type();
	Create_type(Type t, int rang = 0);
	Create_type(const Create_type& t);
	Create_type & composite (Create_type t);
};

std::string quicksort(std::string s);

struct Node
{
	NestedType nested;
	std::string name;
	Create_type type_of_variable;
	Variable * var;
	Node();
	Node(std::string name, Create_type t);
};

struct Array
{
	int range; //rozmer pola
	Type element_type;
	std::vector<Variable* > elements;
};

struct Location
{
	int x, y;
	Location(int x = 0, int y = 0);
};

struct Variable // struktura premennych
{
	std::string name;
	Type type;

	int active; //bola deklarovana v danom bloku
	unsigned int last_access; //z  tohoto sa vypocita penalizacia
	std::vector<int> IntegerValue;
	std::vector<float> RealValue;
	std::vector<Array *> array;
	std::vector<Location> LocationValue;
	std::vector<Object *> ObjectValue;

	Variable();
	Variable(std::string s,Type t);
	void set_node(Create_type t, Memory *m);
	int size();
};

#endif
