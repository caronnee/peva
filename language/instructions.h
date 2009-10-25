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
	bool constant;
public:
	std::string name_;
	virtual std::string name();
	virtual xmlNodePtr xml_format();
	virtual int execute(Core * s) = 0;
	Instruction();
};
class InstructionCreate : public Instruction
{
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		InstructionCreate(Node * n);
};
class InstructionLoadLocal : public Instruction
{
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		InstructionLoadLocal(Node * n);
		InstructionLoadLocal(); //loadne z toho, co ma na value stacku
};
class InstructionLoadGlobal : public Instruction
{
	public:
		virtual xmlNodePtr xml_format();
		virtual int execute(Core *s);
		InstructionLoadGlobal(Node * n);
		InstructionLoadGlobal(); //loadne z toho, co ma na value stacku
};
class InstructionLoad : public Instruction
{
	bool constant;
	Type type;
	Variable* var;
	public:
		virtual xmlNodePtr xml_format();
		virtual int execute(Core *s);
		InstructionLoad(int i);
		InstructionLoad(float f);
		InstructionLoad(); //loadne z toho, co ma na value stacku
};
class InstructionConversionToInt : public Instruction
{
	public:
		InstructionConversionToInt();
		virtual int execute(Core *s);
};
class InstructionConversionToReal: public Instruction
{
	public:
		InstructionConversionToReal();
		virtual int execute(Core *c);
};
class InstructionDuplicate: public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionDuplicate();
};
class InstructionStoreInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionStoreInteger();
};
class InstructionStoreReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionStoreReal();
};
/*Location, struct, array sa robi v InstructionStore, panlizacia potom vyppocitana*/

class InstructionStoreObject : public Instruction
{ 
	public:
		virtual int execute(Core *s);
		InstructionStoreObject();
};
class InstructionStore : public Instruction
{
	public:
	virtual int execute(Core *c);
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

class InstructionPop : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionPop();
};

class InstructionMustJump : public Instruction
{
	int shift;
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		InstructionMustJump(int steps);
};
class InstructionJump : public Instruction
{
	int yes, no;
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		InstructionJump(int stepsYes, int stepsNo);
};

class InstructionBreak : public Instruction
{
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		int jump, depth;
		InstructionBreak(int depth_ = 0);
		virtual void set(size_t jump, size_t depth);
};
class InstructionContinue : public InstructionBreak //stejne ako break, ale skace inam
{
	public:
		InstructionContinue(int depth_ = 0);
};
class InstructionReturn : public Instruction
{
	int depth,jump;
	public:
		InstructionReturn(int dep);
		virtual int execute(Core * c);
};
class InstructionRestore: public Instruction
{
	public:
		virtual int execute(Core * c);
		InstructionRestore();
};

class InstructionRemoveTemp: public Instruction
{
	public:
		virtual int execute(Core * c);
		InstructionRemoveTemp();
};

class InstructionPlusPlusInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionPlusPlusInteger();
};
class InstructionPlusPlusReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionPlusPlusReal();
};
class InstructionMinusMinusInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionMinusMinusInteger();
};
class InstructionMinusMinusReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionMinusMinusReal();
};
/*class InstructionPlus : public Instruction //pre pointre?Location
{
	public:
		virtual int execute(Core *s);
		InstructionPlus();
};*/
class InstructionPlusInteger : public Instruction //pre pointre
{
	public:
		virtual int execute(Core *s);
		InstructionPlusInteger();
};
class InstructionPlusReal : public Instruction //pre pointre
{
	public:
		virtual int execute(Core *s);
		InstructionPlusReal();
};
class InstructionMinusInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionMinusInteger();
};

class InstructionMinusReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionMinusReal();
};
class InstructionMultiplyInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionMultiplyInteger();
};
class InstructionMultiplyReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionMultiplyReal();
};
class InstructionDivideInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionDivideInteger();
};
class InstructionDivideReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionDivideReal();
};
class InstructionModulo : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionModulo();
};
class InstructionBinaryAnd : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionBinaryAnd();
};
class InstructionAnd : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionAnd();
};
class InstructionBinaryOr : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionBinaryOr();
};
class InstructionOr : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionOr();
};
class InstructionBinaryNot : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionBinaryNot();
};
class InstructionNot : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionNot();
};
//-------------------------------------------------------------------------------------------------------Relation------------------------------
class InstructionGtInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionGtInteger();
};
class InstructionGtReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionGtReal();
};
class InstructionGeInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionGeInteger();
};
class InstructionGeReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionGeReal();
};
class InstructionEqualInteger : public Instruction //na pointre
{
	public:
		virtual int execute(Core *s);
		InstructionEqualInteger();
};

class InstructionEqualReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionEqualReal();
};
class InstructionEqualObject : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionEqualObject();
};
class InstructionNotEqual : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionNotEqual();
};
class InstructionNotEqualInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionNotEqualInteger();
};
class InstructionNotEqualReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionNotEqualReal();
};
class InstructionNotEqualObject : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionNotEqualObject();
};

class InstructionLtInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionLtInteger();
};
class InstructionLtReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionLtReal();
};
class InstructionLeInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionLeInteger();
};

class InstructionLeReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionLeReal();
};

class InstructionBegin : public Instruction
{
	public:
		size_t depth;
		virtual int execute(Core *s);
		InstructionBegin(size_t d = 0); //label for 
};
class InstructionEndBlock : public Instruction
{
	public:
		size_t end_loop;
		virtual int execute(Core *s);
		InstructionEndBlock(size_t end_l = 0);
};
//--------------------------------------------------Interaction--------------------------------------------------
class InstructionSee : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionSee(Node *s);
};
class InstructionStep : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionStep();
};
class InstructionStepDefault : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionStepDefault();
};
class InstructionWait : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionWait();
};
class InstructionShootLocation : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionShootLocation();
};
class InstructionShootAngle : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionShootAngle();
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
