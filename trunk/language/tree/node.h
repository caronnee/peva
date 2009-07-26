#ifndef ___NODES___
#define ___NODES___

#include <string> 
#include <vector>
#include <list>
#include "typedefs.h"

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
	Global,
	Local
};

bool is_simple();

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

std::string quicksort(std::string s);

class Object;
struct Node;

struct Array
{
	int range; //rozmer pola
	Type element_type;
	std::vector<Node> elements;
};

struct Location
{
	int x, y;
	Location(int x = 0, int y = 0);
};

struct Node // struktura premennych
{
	std::string name;
	Type type;
	NestedType nested;

	int active; //bola deklarovana v danom bloku
	unsigned int last_access; //z  tohoto sa vypocita penalizacia
	std::vector<int> IntegerValue;
	std::vector<float> RealNumber;
	std::vector<Array *> array;
	std::vector<Location> LocationValue;
	std::vector<Object *> ObjectValue;

	Node();
	Node(std::string s,Type t);
	Node (std::string s,Create_type t);
	int size();
};

#endif
