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

std::string quicksort(std::string s);

class Object;
struct Node;

struct Array
{
	int range; //rozmer pola
	Type type;
	Node* value;
};

struct Location
{
	int x, y;
	Location(int x = 0, int y = 0);
};
struct Node // struktura premennych
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
};
#endif
