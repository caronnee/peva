#ifndef ___STACK___
#define ___STACK___
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include "./instructions.h"
#include "./tree.h"
#include "functions.h"

#define DELIMINER_CHAR '#'
typedef std::vector<Instruction *> Instructions;
typedef std::vector<Value> Values;

struct Constr
{
	std::string id;
	Instructions ins;
	bool default_set;
	Constr();
	Constr(std::string a);
	Constr(std::string a, int def);
	Constr(std::string a, Instructions i);
};

struct MyXmlData
{
	xmlDocPtr doc;
	xmlNodePtr root_ptr;
	xmlNodePtr node;
};

struct Program
{
	bool error;
	std::string nested;
	Function * nested_function;
	int last_loop_number;
	std::stack<int> loop_labels;
	Tree defined;//root burst stromu
	Instructions instructions; //kopa predefinovanych instrukcii
	Values values;//stack ukazatelov do stromu
	MyXmlData data;
	void save_to_xml();
	Program();
	Core * core;
	void add_global(Instructions ins);
	void output(Tree * t);
	void enter_loop();
	void end_loop();
	Node * find_var(std::string);
	/* Vracia, ci sa podarilo pridat alebo nie*/
	Node * add(std::string name, Create_type t);
	Function * find_f(std::string s);
	void add(Instructions ins);
	Node * create_type(Type t);
	void enter(std::string s, Create_type t);
	void add_function(std::vector<Parameter_entry> c, Instructions ins);
	void leave();
	void execute();
};
#endif
