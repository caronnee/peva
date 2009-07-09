#ifndef __INSTR__
#define __INSTR__
#include "node.h" //su tam ulozene node  values
#include "typedefs.h"

class Instruction
{
	Values * values;	
public:
	virtual int execute() = 0;
	Instruction();
};
#endif
