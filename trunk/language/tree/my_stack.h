#ifndef ___STACK___
#define ___STACK___
#include <list>
#include <vector>
#include <string>

#define MaxItems 2

class Object;//TODO potom zmazat a pridat v inklude

enum InstructionType
{
	IntructionLoad = 0,//loaduje premennu
	IntructionStore,
	IntructionCall,
	IntructionTjump,
	IntructionJump,
	InstructionLabel, //kam ma skocit po nejakom jumpe
	IntructionReturn,
	IntructionLeaveBlock,//zneplatni vsetky premenne deklarovane v tomto bloku, deklarovanie spravene bisonom
	InstructionStartBlok,

	IntructionLess,
	IntructionMore,
	IntructionLessEqual,
	IntructionMoreEqual,
	IntructionNotEqual,
	IntructionEqual,

	IntructionPlusPlus,
	IntructionMinusMinus,
	IntructionPlus,
	IntructionMinus,
	IntructionDivide,
	IntructionMultiply,
	NumberOfInstructions //TODO pridat instrukcie na varovanie
};
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

struct Instruction
{
	InstructionType instruction;
	std::string parameter;
	Instruction(InstructionType t, std::string s);
};

struct Node;

struct Array
{
	int range; //rozmer pola
	Type t;
	std::vector<Node> values;
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

struct Tree
{
	bool inner_node;
	int depth;
	Tree * next[256];//TODO dynamicke linkovanie
	std::list<Node *> items;//ukazatel z jednoducheho dovodu -> inak je to prasarna, vyparsovavat z listu:)
	Tree();
	Tree(int d);
};
typedef std::vector<Instruction> Instructions;
typedef std::vector<Node *> Values;
struct Program
{
	bool error;
	std::string alphabet;
	Tree defined;//root burst stromu
	Instructions instructions;//obrovsky switch na to co ma s cim robit
	Values values;//stack ukazatelov do stromu

	Program();
	void output(Tree * t);
	int find_index(char a);
	Tree * find_string(std::string);
	Node * add_string(std::string name,Type type);
	std::list<Node * > const_numbers; //aby sme pokazde nemuseli pridavat 
};
#endif
