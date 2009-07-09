#ifndef ___STACK___
#define ___STACK___
#include <list>
#include <vector>
#include <string>
#include "./tree.h"
#include "./instructions.h"
#include "./typedefs.h"
#include "./node.h"

#define MaxItems 2

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

struct Program
{
	bool error;
	std::string alphabet;
	Tree defined;//root burst stromu
	Instructions instructions; //kope prdefinovanych instrukcii
	Values values;//stack ukazatelov do stromu

	Program();
	void output(Tree * t);
	int find_index(char a);
	Tree * find_string(std::string);
	Node * add_string(std::string name,Type type);
	std::list<Node * > const_numbers; //aby sme pokazde nemuseli pridavat 
};
#endif
