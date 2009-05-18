#include <list>
#include <vector>
#include <string>

#define MaxItems 5

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
struct Node //policko stromu
{
	std::string name;
	unsigned int last_access; //z  tohoto sa vypocita penalizacia
	Type type;
	int ProgramPointer;//na jake miesto v stacku sa zara
	int active; //bola deklarovana v danom bloku
	int IntegerValue;
	float RealNumber;
	//array
//	Position LocationValue;
//	Object objectValue;
	Node();
	Node(std::string s,Type t);
};
struct Tree
{
	bool inner_node;
	int depth;
	Tree * next[256];//TODO dyamicke linkovanie
	std::list<Node> items;//potom budeme posielat & ako adresu -> ok
	Tree();
	Tree(int d);
};
struct BotProgram
{
	std::string alphabet;
	Tree defined;//root burst stromu
	std::vector<Instruction> instructions;//obrovsky switch na to co ma s cim robit
	std::vector<Node * > valueStack;//stack ukazatelov do stromu

	BotProgram();
	void output(Tree * t);
	int find_index(char a);
	Tree * find_string(std::string);
	void add_string(std::string name,Type type);
};
