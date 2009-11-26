#include <iostream>
#include <cstdio>
#include "../h/types.h"

static Type simple[] = { TypeInteger, TypeReal, TypeObject };

Create_type * Create_type::next()
{
	if (iterator < range)
	{
		iterator++;
		return data_type;
	}
	if (iterator < nested_vars.size())
	{
		iterator++;
		return nested_vars[iterator-1].type;
	}
	std::cout <<"Next nepresiel!Je to asi jednoduchy typ"<<iterator;getc(stdin);
	return NULL;
}
//reset sa d apouzit jedine v pripade, ze sa neopakuju typy a to je nemozne -> cyklus
void Create_type::reset()
{
	iterator = 0;
}
bool Create_type::is_simple()
{
	for (size_t i =0; i< sizeof(simple)/sizeof(Type); i++)
	{
		if (simple[i] == type)
		{
			return true;
		}
	}
	return false;
}

Create_type::Create_type()
{
	iterator = 0;
	range = 0;
	type = TypeUndefined;
	data_type = NULL;
}
Create_type::Create_type(Type t, int rang)
{
	iterator = 0;
	range = rang;
	type = t;
	data_type = NULL;
}
Create_type::Create_type(const Create_type & t)
{
	iterator = 0;
	range = t.range;
	data_type = NULL;
	
//	std::cout << "Tu sa este dostanem -CREATE_T"<<t.nested_vars.size(); getc(stdin);
	for(size_t i = 0; i<t.nested_vars.size(); i++)
	{
		Record r;
		r.name = t.nested_vars[i].name;
		r.type = t.nested_vars[i].type;
		nested_vars.push_back(r);
	}
//	std::cout << "ENDTu sa este dostanem -CREATE_T"; getc(stdin);
	data_type = t.data_type;
	type = t.type;
}

void Create_type::composite ( Create_type* t) 
{//FIXME id podruhe, nejaky vykrik
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
	{
		std::cout << "1";
		return false;
	}
	if (nested_vars.size()!=t.nested_vars.size())
	{
		std::cout << "2";
		return false;
	}
	for(size_t i =0; i<nested_vars.size(); i++)
	{
		if (nested_vars[i].name!=t.nested_vars[i].name)
		{
			std::cout << "3";
			return false;
		}
		if ((nested_vars[i].type) !=(t.nested_vars[i].type))
			{
				std::cout << "4";
				return false;
			}
	}
	if (range!=t.range)
	{
		std::cout << "ranges:" << range << " " << t.range;
		return false;
	}
	
	if (data_type != t.data_type) // ak sa rovnaju poitre, tak je zvysok zarucene stejny
		return false;
	return true;
}
