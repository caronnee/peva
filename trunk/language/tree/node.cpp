#include "node.h"

static Type simple[] = { TypeInteger, TypeReal, TypeObject };

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

Create_type& Create_type::composite ( Create_type t)
{
	Create_type comp(*this);
	comp.data_type = &t;
	return *this;
}

bool is_simple(Type t)
{
	for (int i =0; i< sizeof(simple)/sizeof(Type); i++)
	{
		if (simple[i] == t)
			return true;
	}
	return false;
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
Node::Node(std::string s, Create_type t)
{
	type = t.type;
	if (t.type == TypeArray)
	{
		if (t.data_type == NULL)		
		{
			type = TypeUndefined;
			return; //TODO exception
		}
		for (int i =0; i < t.range; i++)
		{
			array = new Array();
			array->elements.push_back(Node(s,*t.data_type));
		}
	}
}
int Node::size() //kolko v zasoniku ma preskocit, aby sa dostal na zaciatok
{
	if (is_simple(this->type))
	{
		return 1;
	}
	int size = 0;
	for (int i =0; i< array->elements.size(); i++)
	{
		size +=array->elements[i].size();
	}
	return size;
}
Node::Node(std::string s,Type t)
{
	//space_ocupied;
	last_access = 0;
	int active = 0;//ked ju bison vytvori, este niej aktivana
	name = s;
	type = t;
}

