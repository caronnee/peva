#ifndef __INSTR__
#define __INSTR__
#include "./tree/node.h" //su tam ulozene node  values
#include "./tree/typedefs.h"

enum InstructionType
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
};

class Instruction
{
	Values * values;	
public:
	virtual int execute() = 0;
	Instruction();
};
#endif
