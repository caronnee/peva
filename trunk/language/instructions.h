#ifndef __INSTR__
#define __INSTR__
#include "./tree/node.h" //su tam ulozene node  values
#include "./tree/typedefs.h"

/*enum InstructionType
{
	InstructionLoad = 0,//loaduje premennu
	InstructionStore,
	InstructionCall,
	InstructionTjump,
	InstructionJump,
	InstructionLabel, //kam ma skocit po nejakom jumpe
	InstructionReturn,
	InstructionLeaveBlock,//zneplatni vsetky premenne deklarovane v tomto bloku, deklarovanie spravene bisonom
	InstructionStartBlok,

	InstructionLess,
	InstructionMore,
	InstructionLessEqual,
	InstructionMoreEqual,
	InstructionNotEqual,
	InstructionEqual,

	InstructionPlusPlus,
	InstructionMinusMinus,
	InstructionPlus,
	InstructionMinus,
	InstructionDivide,
	InstructionMultiply,
	NumberOfInstructions //TODO pridat instrukcie na varovanie
};*/

class Instruction
{
	Values * values;	
public:
	virtual std::string name();
	virtual int execute();
	Instruction();
};
class InstructionCreate : public Instruction{
	public:
		InstructionCreate(std::string s);
		InstructionCreate();
};
class InstructionLoad : public Instruction{
	public:
		InstructionLoad(std::string s);
		InstructionLoad(int i);
		InstructionLoad(float f);
		InstructionLoad();
};

class InstructionStore : public Instruction{
	public:
		InstructionStore();
};
class Call : public Instruction
{
	Call();
};
#endif
