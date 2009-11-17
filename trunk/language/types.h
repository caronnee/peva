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

struct Record;

struct Create_type
{
	size_t range;
	Create_type * data_type;
	std::vector<Record> nested_vars; //pre strukty
	Type type;
	Create_type();
	Create_type(Type t, int rang = 0);
	Create_type(const Create_type& t);
	void composite (Create_type * t);
	void add(std::string name, Create_type * t);
	bool operator==(const Create_type& t);
	bool operator!=(const Create_type& t);
	Create_type element();
	size_t iterator; //kolkaty prvok sme uz pozreli
public:
	Create_type next(bool &ok);
	bool is_simple();
};

struct Record
{
	std::string name;
	Create_type type;
	Create_type typ();
};
#endif
