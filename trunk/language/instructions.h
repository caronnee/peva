#ifndef __INSTR__
#define __INSTR__
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "node.h"
#include "core.h"
#include "help_functions.h"
#include "functions.h"

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
	virtual int execute(Core * s);
	Instruction();
};
class InstructionCreate : public Instruction{
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		InstructionCreate(Node * n);
};
class InstructionLoadLocal : public Instruction{
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		InstructionLoadLocal(Node * n);
		InstructionLoadLocal(); //loadne z toho, co ma na value stacku
};
class InstructionLoadGlobal : public Instruction{
	public:
		virtual xmlNodePtr xml_format();
		virtual int execute(Core *s);
		InstructionLoadGlobal(Node * n);
		InstructionLoadGlobal(); //loadne z toho, co ma na value stacku
};
class InstructionLoad : public Instruction{
	bool constant;
	Variable* var;
	public:
		virtual xmlNodePtr xml_format();
		virtual int execute(Core *s);
		InstructionLoad(int i);
		InstructionLoad(float f);
		InstructionLoad(); //loadne z toho, co ma na value stacku
};
class InstructionStore : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionStore();
};
class Call : public Instruction
{
	Function* function;
	public:
		virtual xmlNodePtr xml_format();
		virtual int execute(Core *s);
		Call(Function * f);
		Call();
};

class InstructionPop : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionPop();
};

class InstructionMustJump : public Instruction{
	int shift;
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		InstructionMustJump(int steps);
};
class InstructionJump : public Instruction{
	int yes, no;
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		InstructionJump(int stepsYes, int stepsNo);
};
class InstructionReturn : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionReturn();
};
class InstructionBreak : public Instruction{
	int loop_label;
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		int jump;
		InstructionBreak(int label);
		virtual int breaks();
};
class InstructionPlusPlus : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionPlusPlus();
};
class InstructionMinusMinus : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionMinusMinus();
};
class InstructionPlus : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionPlus();
};
class InstructionMinus : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionMinus();
};
class InstructionMultiply : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionMultiply();
};
class InstructionDivide : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionDivide();
};
class InstructionModulo : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionModulo();
};
class InstructionBinaryAnd : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionBinaryAnd();
};
class InstructionAnd : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionAnd();
};
class InstructionBinaryOr : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionBinaryOr();
};
class InstructionOr : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionOr();
};
class InstructionBinaryNot : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionBinaryNot();
};
class InstructionNot : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionNot();
};
//-------------------------------------------------------------------------------------------------------Relation------------------------------
class InstructionGt : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionGt();
};
class InstructionGe : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionGe();
};
class InstructionEqual : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionEqual();
};
class InstructionLt : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionLt();
};
class InstructionLe : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionLe();
};
class InstructionBegin : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionBegin(); //Aby sme vedeli, kedy sa vynorujeme
};
class InstructionEndBlock : public Instruction{
	public:
		virtual int execute(Core *s);
		InstructionEndBlock();
};
//--------------------------------------------------Interaction--------------------------------------------------
class InstructionSee : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionSee();
};
class InstructionStep : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionStep();
};
class InstructionWait : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionWait();
};
class InstructionShoot : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionShoot();
};
class InstructionTurn : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionTurn();
};
class InstructionTurnR : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionTurnR();
};
class InstructionTurnL: public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionTurnL();
};
class InstructionHit: public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionHit();
};
//--------------------------------------------
class InstructionIsPlayer: public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionIsPlayer();
};
class InstructionIsWall: public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionIsWall();
};
class InstructionIsMissille: public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionIsMissille();
};
class InstructionLocate: public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionLocate();
};
class InstructionIsMoving: public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionIsMoving();
};
#endif
