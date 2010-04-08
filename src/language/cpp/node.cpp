#include <iostream>
#include "../h/node.h"

Node::Node()
{
	ID = 0;
}
Node::Node(std::string name_, Create_type * t, size_t ID_)
{
	ID =ID_;
	nested = Local;
	name = name_;
	var.clear();
	type_of_variable = t; //Root nasho kvazi stromu
	active = false;
//	TEST("pridavam create_type:" << t.data_type->type)
}
Node::~Node()
{
	/* nothing to clean it up */
}
