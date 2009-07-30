#ifndef ___TYPES____
#define ___TYPES____

#include <vector>
#include<string>

enum Type
{
	TypeUndefined = 0,
	TypeInteger,
	TypeReal,
	TypeObject,
	TypeLocation,
	TypeArray,
	TypeFunction,
	TypeProcedure,
	TypeVoid,
	NumberOfTypes
};

enum NestedType
{
	Const,
	Global,
	Local
};

bool is_simple(Type t);

struct Create_type;

struct Record
{
	std::string name;
	Create_type * type;
};

struct Create_type
{
	int range;
	Create_type * data_type;
	std::vector<Record> nested_vars;
	Type type;
	Create_type();
	Create_type(Type t, int rang = 0);
	Create_type(const Create_type& t);
	Create_type & composite (Create_type t);
};

#endif
