#ifndef ___NODES___
#define ___NODES___

#include <string> 
#include <vector>
#include <list>

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
	NumberOfTypes
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
//AK type_function albo Type Procedure, hodnota ulozena v integer_value
{
	std::string name;
	unsigned int last_access; //z  tohoto sa vypocita penalizacia
	Type type;
	int active; //bola deklarovana v danom bloku
	int IntegerValue;
	float RealNumber;
	Array * array;
	Location LocationValue;
	Object * ObjectValue;
	Node();
	Node(std::string s,Type t);
	Node (std::string s,Create_type t);
	Node * clone(); //TODO
	int size();
};
#endif
