#ifndef ___STACK___
#define ___STACK___
#include <list>
#include <vector>
#include <string>
#include "./tree.h"
#include "../instructions.h"
#include "./typedefs.h"
#include "./node.h"

template <class Key, class Val>class pair
{
	Key key;
	Val val;
};

enum Parameter_type
{
	PARAMETER_BY_REFERENCE,
	PARAMETER_BY_VALUE
};

struct Parameter_entry
{
	std::string name;
	Parameter_type val_type;
	Create_type type;
};

struct Functions
{
	std::string name;
	std::vector<Parameter_entry> parameters;
	int begin; //kde to zacina v stacku
};

struct Value
{
	Type t;
	int integer_value;
	float real_value;
	std::string string_value;
	Object * object_value;
};

struct Program
{
	bool error;
	std::string alphabet;
	Tree defined;//root burst stromu
	Instructions instructions; //kopa predefinovanych instrukcii
	Values values;//stack ukazatelov do stromu

	Program();
	void output(Tree * t);
	int find_index(char a);
	std::vector<Functions> functions;
	Tree * find_string(std::string);
	std::vector<Create_type*> types; //TODO spravit tak, aby boli unikatne
	/* Vracia, ci sa podarilo pridat alebo nie*/
	bool add(std::string name, Create_type t);
	Node * create_type(Type t);
	void enter();
	void leave();
};
#endif
