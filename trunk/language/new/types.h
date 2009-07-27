#ifndef ___TYPES____
#define ___TYPES____
bool is_simple();

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

struct Create_type
{
	int range;
	Create_type * data_type;
	Type type;
	Create_type();
	Create_type(Type t, int rang = 0);
	Create_type(const Create_type& t);
	Create_type & composite (Create_type t);
};

#endif
