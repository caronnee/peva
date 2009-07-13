#ifndef ___STACK___
#define ___STACK___
#include <list>
#include <vector>
#include <string>
#include "./tree.h"
#include "./instructions.h"
#include "./typedefs.h"
#include "./node.h"

struct Program
{
	bool error;
	std::string alphabet;
	Tree defined;//root burst stromu
	Instructions instructions; //kope prdefinovanych instrukcii
	Values values;//stack ukazatelov do stromu

	Program();
	void output(Tree * t);
	int find_index(char a);
	Tree * find_string(std::string);
	std::vector<Create_type*> types; //TODO spravit tak, aby boli unikatne
	/* Vracia, ci sa podarilo rpidat alebo nie*/
	bool  add(std::string name, Node * n);
	Node * create_type(Type t);
};
#endif
