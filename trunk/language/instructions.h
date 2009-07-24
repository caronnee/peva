#ifndef __INSTR__
#define __INSTR__
#include "./tree/node.h" //su tam ulozene node  values
#include "./tree/typedefs.h"

class Instruction
{
	protected:
	Values * values;	
	std::string name_;
public:
	virtual std::string name();
//	virtual int execute();
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
		InstructionLoad(); //loadne z toho, co ma na value stacku
};

class InstructionStore : public Instruction{
	public:
		InstructionStore();
};
class Call : public Instruction
{
	public:
		Call(std::string s);
		Call();
};

class CallMethod : public Instruction
{
	public:
		CallMethod(std::string s);
		CallMethod();
};
class InstructionPop : public Instruction{
	public:
		InstructionPop();
};
class InstructionMustJump : public Instruction{
	public:
		InstructionMustJump(int steps);
};
class InstructionJump : public Instruction{
	public:
		InstructionJump(int stepsYes, int stepsNo);
};
class InstructionReturn : public Instruction{
	public:
		InstructionReturn();
};
class InstructionBreak : public Instruction{
	public:
		InstructionBreak();
};
class InstructionPlusPlus : public Instruction{
	public:
		InstructionPlusPlus();
};
class InstructionMinusMinus : public Instruction{
	public:
		InstructionMinusMinus();
};
class InstructionPlus : public Instruction{
	public:
		InstructionPlus();
};
class InstructionMinus : public Instruction{
	public:
		InstructionMinus();
};
class InstructionMultiply : public Instruction{
	public:
		InstructionMultiply();
};
class InstructionDivide : public Instruction{
	public:
		InstructionDivide();
};
class InstructionModulo : public Instruction{
	public:
		InstructionModulo();
};
class InstructionBinaryAnd : public Instruction{
	public:
		InstructionBinaryAnd();
};
class InstructionAnd : public Instruction{
	public:
		InstructionAnd();
};
class InstructionBinaryOr : public Instruction{
	public:
		InstructionBinaryOr();
};
class InstructionOr : public Instruction{
	public:
		InstructionOr();
};
class InstructionBinaryNot : public Instruction{
	public:
		InstructionBinaryNot();
};

class InstructionNot : public Instruction{
	public:
		InstructionNot();
};

//-------------------------------------------------------------------------------------------------------Relation------------------------------
class InstructionGt : public Instruction{
	public:
		InstructionGt();
};

class InstructionGe : public Instruction{
	public:
		InstructionGe();
};
class InstructionEqual : public Instruction{
	public:
		InstructionEqual();
};
class InstructionLt : public Instruction{
	public:
		InstructionLt();
};
class InstructionLe : public Instruction{
	public:
		InstructionLe();
};
#endif
