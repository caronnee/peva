#ifndef __INSTR__
#define __INSTR__
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "./tree/node.h" //su tam ulozene node  values
#include "./tree/typedefs.h"
#include "help_functions.h"

class Instruction
{
	protected:
	Node * node;
	std::string name_;
	bool constant;
public:
	virtual std::string name();
	virtual int breaks();
	virtual xmlNodePtr xml_format();
//	virtual int execute();
	Instruction();
};
class InstructionCreate : public Instruction{
	public:
		virtual xmlNodePtr xml_format();
		InstructionCreate(Node * n);
		InstructionCreate();
};
class InstructionLoadLocal : public Instruction{
	public:
		virtual xmlNodePtr xml_format();
		InstructionLoadLocal(Node * n);
		InstructionLoadLocal(); //loadne z toho, co ma na value stacku
};
class InstructionLoadGlobal : public Instruction{
	public:
		virtual xmlNodePtr xml_format();
		InstructionLoadGlobal(Node * n);
		InstructionLoadGlobal(); //loadne z toho, co ma na value stacku
};
class InstructionLoad : public Instruction{
	bool destroy_node;
	public:
		virtual xmlNodePtr xml_format();
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
	//	virtual xmlNodePtr xml_format();
		Call(std::string s);
		Call();
};

class CallMethod : public Instruction
{
	public:
	//	virtual xmlNodePtr xml_format();
		CallMethod(std::string s);
		CallMethod();
};
class InstructionPop : public Instruction{
	public:
		InstructionPop();
};
class InstructionMustJump : public Instruction{
	int shift;
	public:
		virtual xmlNodePtr xml_format();
		InstructionMustJump(int steps);
};
class InstructionJump : public Instruction{
	int yes, no;
	public:
		virtual xmlNodePtr xml_format();
		InstructionJump(int stepsYes, int stepsNo);
};
class InstructionReturn : public Instruction{
	public:
		virtual xmlNodePtr xml_format();
		InstructionReturn();
};
class InstructionBreak : public Instruction{
	int loop_label;
	public:
		virtual xmlNodePtr xml_format();
		int jump;
		InstructionBreak(int label);
		virtual int breaks();
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
class InstructionBegin : public Instruction{
	public:
		InstructionBegin(); //Aby sme vedeli, kedy sa vynorujeme
};
class InstructionEndBlock : public Instruction{
	public:
		InstructionEndBlock();
};
//--------------------------------------------------Interaction50--------------------------------------------------
class InstructionSee : public Instruction
{
	public:
		InstructionSee();
};
class InstructionStep : public Instruction
{
	public:
		InstructionStep();
};
class InstructionWait : public Instruction
{
	public:
		InstructionWait();
};
class InstructionShoot : public Instruction
{
	public:
		InstructionShoot();
};
class InstructionTurn : public Instruction
{
	public:
		InstructionTurn();
};
class InstructionTurnR : public Instruction
{
	public:
		InstructionTurnR();
};
class InstructionTurnL: public Instruction
{
	public:
		InstructionTurnL();
};
#endif
