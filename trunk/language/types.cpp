#include "types.h"
#include <iostream>
static Type simple[] = { TypeInteger, TypeReal, TypeObject };

bool is_simple(Type t)
{
	for (size_t i =0; i< sizeof(simple)/sizeof(Type); i++)
	{
		if (simple[i] == t)
			return true;
	}
	return false;
}

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
	for(size_t i = 0; i<t.nested_vars.size(); i++)
	{
		Record r;
		r.name = nested_vars[i].name;
		r.type = new Create_type(*nested_vars[i].type);
		std::cout <<"bolo akolovane:" << r.type <<"v:" << this<< std::endl;
		nested_vars.push_back(r);
	}
	if (t.data_type!=NULL)
	{
		data_type = new Create_type(*t.data_type);
		std::cout <<"bolo akolovane:" <<  data_type <<"v:" << this<< std::endl;
	}
	type = t.type;
}

void Create_type::composite ( Create_type* t) //vrati sa novy typ, Location = type.add(TYPE_INTEGER, INT)
{//TODO id podruhe, nejaky vykrik
	this->data_type = t; 
}
void Create_type::add(std::string name, Create_type * t)
{
	Record r;
	r.name = name;
	r.type = t;
	nested_vars.push_back(r);
}
bool Create_type::operator!=(const Create_type & t)
{
	return !((*this)==t);
}
bool Create_type::operator==(const Create_type & t)
{
	if (t.type!=type)
		return false;
	if (nested_vars.size()!=t.nested_vars.size())
		return false;
	for(size_t i =0; i<nested_vars.size(); i++)
	{
		if (nested_vars[i].name!=t.nested_vars[i].name)
			return false;
		if ((*nested_vars[i].type) !=(*t.nested_vars[i].type))
			return false;
	}
	if (range!=t.range)
		return false;
	if (data_type == t.data_type) // ak sa rovnaju poitre, tak je zvysok zarucene stejny
		return true;
	return ((*data_type)==(*t.data_type));
}
