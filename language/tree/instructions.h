#ifndef __INSTR__
#define __INSTR__
#include "node.h" //su tam ulozene node  values
#include "typedefs.h"

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

class Instruction
{
	Values * values;	
public:
	virtual int execute() = 0;
	Instruction();
};
#endif
