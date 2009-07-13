#include "node.h"

Create_type::Create_type()
{
	type = TypeUndefined;
	data_type = NULL;
}
Create_type::Create_type(Type t, int rang)
{
	range = rang;
	type = t;
	data_type = NULL;
}
Create_type::Create_type(const Create_type & t)
{
	range = t.range;
	data_type = NULL;
	type = t.type;
}
Create_type::~Create_type() throw()
{
	if (data_type!=NULL)
	{
		delete data_type;
	}
	data_type = NULL;
}
Location::Location(int x_, int y_)
{
	x = x_; y = y_;
}
Node::Node() //toto sa normalne nebude pouzivat
{
	last_access = 0;
	type = TypeUndefined;
	int active = 0;//ked ju bison vytvori, este niej aktivana
	//location, object, real numbers a pod, nahodne cisla
}
Node::Node(Create_type t)
{
	type = t.type;
	if (t.type == TypeArray)
	{
		if (t.data_type == NULL)		
		{
			type = TypeUndefined;
			return; //TODO exception
		}
		for (int i =0; i<t.range; i++)
		{
			array = new Array();
			array->elements.push_back(Node(*t.data_type));
		}
	}
}
Node::Node(std::string s,Type t)
{
	//space_ocupied;
	last_access = 0;
	int active = 0;//ked ju bison vytvori, este niej aktivana
	name = s;
	type = t;
}

