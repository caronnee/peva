#ifndef ___STACK___
#define ___STACK___
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include "../instructions.h"
#include "./tree.h"
#include "./typedefs.h"
#include "./node.h"

struct Constr
{
	std::string id;
	Instructions ins;
	bool default_set;
	Constr()
	{
		default_set = false;
		id ="";
	}
	Constr(std::string a)
	{
		id = a;
		default_set = false;
	}
	Constr(std::string a, int def)
	{
		id  = a;
		default_set = true;
		ins.push_back(new InstructionLoad(def));
	}
	Constr(std::string a, Instructions i)
	{
		id = a;
		ins = i;
		default_set = true;
	}
};

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
	Parameter_entry(std::string name, Parameter_type pt, Create_type type);
	Parameter_entry();
};

struct Function
{
	std::string name;
	std::vector<Parameter_entry> parameters;
	int begin; //kde to zacina v stacku
	int end;
	Node * return_type;
	Function(std::string name, std::vector<Parameter_entry>, Create_type t);
};

struct Value
{
	Type t;
	int integer_value;
	float real_value;
	std::string string_value;
	Object * object_value;
};
struct MyXmlData
{
	xmlDocPtr doc;
	xmlNodePtr root_ptr;
	xmlNodePtr node;
};
struct Stack
{
//	Robot R;
	int PC;
	Instructions instructions;
	Values values;
};
struct Program
{
	int PC;
	bool error;
	int nested;
	int last_loop_number;
	std::stack<int> loop_labels;
	std::string alphabet;
	Tree defined;//root burst stromu
	Instructions instructions; //kopa predefinovanych instrukcii
	Values values;//stack ukazatelov do stromu
	MyXmlData data;
	void save_to_xml();
	Program();
	void add_global(Instructions ins);
	void output(Tree * t);
	void enter_loop();
	void end_loop();
	int find_index(char a);
	std::vector<Function> functions;
	Tree * find_string(std::string);
	Node * find_var(std::string);
	std::vector<Create_type*> types; //TODO spravit tak, aby boli unikatne
	/* Vracia, ci sa podarilo pridat alebo nie*/
	Node * add(std::string name, Create_type t);
	void add(Instructions ins);
	Node * create_type(Type t);
	void enter();
	void add_function(Create_type t, std::string name, std::vector<Parameter_entry> c, Instructions ins);
	void leave();
};
#endif
