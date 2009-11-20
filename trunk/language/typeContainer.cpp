#include "typeContainer.h"

Create_type * TypeContainer::find_type(Type t)
{
	for (size_t i= 0; i< defined_types.size(); i++)
		if (defined_types[i]->type == t)
		{
			return defined_types[i];
		}
	return NULL;//ZAVAZNA CHYBA! Ale zo strany programatora;), mozno by to stalo za excepsnu
}

Create_type * TypeContainer::find_array_type(size_t range, Create_type * descend)
{
	for (size_t i= 0; i< defined_types.size(); i++)
		if ((defined_types[i]->type == TypeArray)
			&&(defined_types[i]->data_type == descend)
			&&(defined_types[i]->range == range))
		{
			return defined_types[i];
		}
	Create_type * t = new Create_type(TypeArray, range);
	t->composite(descend);
	defined_types.push_back(t);
	return t;
}
void TypeContainer::add(Create_type * t)
{
	defined_types.push_back(t);
}
TypeContainer::~TypeContainer()
{
	//TODO kopirovat, neviem, ci su to pointre a ci sa medzitym niekde edealkokuju, skor pop()
	for ( size_t i =0; i< defined_types.size(); i++)
	{
		delete defined_types[i];
	}
}
