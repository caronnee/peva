#include "types.h"

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
	type = t.type;
}

Create_type& Create_type::composite ( Create_type t)
{
	Create_type comp(*this);
	comp.data_type = &t; //TODO seriozny BUG! priradzujem typ, co za chvilinku zanikne
	return *this;
}
