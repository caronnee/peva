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
	virtual ~Instruction();
};
class InstructionCreate : public Instruction
{
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		InstructionCreate(Node * n);
		virtual ~InstructionCreate();
};
class InstructionLoadLocal : public Instruction
{
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		InstructionLoadLocal(Node * n);
		InstructionLoadLocal(); //loadne z toho, co ma na value stacku
		virtual ~InstructionLoadLocal();
};
class InstructionLoadGlobal : public Instruction
{
	public:
		virtual xmlNodePtr xml_format();
		virtual int execute(Core *s);
		InstructionLoadGlobal(Node * n);
		InstructionLoadGlobal(); //loadne z toho, co ma na value stacku
		virtual ~InstructionLoadGlobal();
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
		InstructionLoad(); 
		virtual ~InstructionLoad();
};
class InstructionConversionToInt : public Instruction
{
	public:
		InstructionConversionToInt();
		virtual int execute(Core *s);
		virtual ~InstructionConversionToInt();
};
class InstructionConversionToReal: public Instruction
{
	public:
		InstructionConversionToReal();
		virtual int execute(Core *c);
		virtual ~InstructionConversionToReal();
};
class InstructionDuplicate: public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionDuplicate();
		virtual ~InstructionDuplicate();
};
class InstructionStoreInteger : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionStoreInteger();
		virtual ~InstructionStoreInteger();
};
class InstructionStoreReal : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionStoreReal();
		virtual ~InstructionStoreReal();
};
/*Location, struct, array sa robi v InstructionStore, panlizacia potom vyppocitana*/

class InstructionStoreObject : public Instruction
{ 
	public:
		virtual int execute(Core *s);
		InstructionStoreObject();
		virtual ~InstructionStoreObject();
};
class InstructionStore : public Instruction
{
	public:
		InstructionStore();
		virtual int execute(Core *c);
		virtual ~InstructionStore();
};
class Call : public Instruction
{
	Function* function;
	public:
		Call();
		Call(Function * f);
		virtual xmlNodePtr xml_format();
		virtual int execute(Core *s);
		virtual ~Call();
};

class InstructionPop : public Instruction
{
	public:
		virtual int execute(Core *s);
		InstructionPop();
		virtual ~InstructionPop();
};

class InstructionMustJump : public Instruction
{
	int shift;
	public:
		InstructionMustJump(int steps);
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		virtual ~InstructionMustJump();
};
class InstructionJump : public Instruction
{
	int yes, no;
	public:
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		InstructionJump(int stepsYes, int stepsNo);
		virtual ~InstructionJump();
};

class InstructionBreak : public Instruction
{
	public:
		InstructionBreak(int depth_ = 0);
		int jump, depth;
		virtual int execute(Core *s);
		virtual xmlNodePtr xml_format();
		virtual void set(size_t jump, size_t depth);
		virtual ~InstructionBreak();
};
class InstructionContinue : public InstructionBreak //stejne ako break, ale skace inam
{
	public:
		InstructionContinue(int depth_ = 0);
		virtual ~InstructionContinue();
};
class InstructionReturn : public Instruction
{
	int depth,jump;
	public:
		InstructionReturn(int dep);
		virtual int execute(Core * c);
		virtual ~InstructionReturn();
};
class InstructionRestore: public Instruction
{
	public:
		virtual int execute(Core * c);
		InstructionRestore();
		virtual ~InstructionRestore();
};

class InstructionRemoveTemp: public Instruction
{
	public:
		InstructionRemoveTemp();
		virtual int execute(Core * c);
		virtual ~InstructionRemoveTemp();
};

//-----------------------------------COUNTING-----------------------------------------

class InstructionPlusPlusInteger : public Instruction
{
	public:
		InstructionPlusPlusInteger();
		virtual int execute(Core *s);
		virtual ~InstructionPlusPlusInteger();
};
class InstructionPlusPlusReal : public Instruction
{
	public:
		InstructionPlusPlusReal();
		virtual int execute(Core *s);
		virtual ~InstructionPlusPlusReal();
};
class InstructionMinusMinusInteger : public Instruction
{
	public:
		InstructionMinusMinusInteger();
		virtual int execute(Core *s);
		virtual ~InstructionMinusMinusInteger();
};
class InstructionMinusMinusReal : public Instruction
{
	public:
		InstructionMinusMinusReal();
		virtual int execute(Core *s);
		virtual ~InstructionMinusMinusReal();
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
		InstructionPlusInteger();
		virtual int execute(Core *s);
		virtual ~InstructionPlusInteger();
};
class InstructionPlusReal : public Instruction //pre pointre
{
	public:
		InstructionPlusReal();
		virtual int execute(Core *s);
		virtual ~InstructionPlusReal();
};
class InstructionMinusInteger : public Instruction
{
	public:
		InstructionMinusInteger();
		virtual int execute(Core *s);
		virtual ~InstructionMinusInteger();
};

class InstructionMinusReal : public Instruction
{
	public:
		InstructionMinusReal();
		virtual int execute(Core *s);
		virtual ~InstructionMinusReal();
};
class InstructionMultiplyInteger : public Instruction
{
	public:
		InstructionMultiplyInteger();
		virtual int execute(Core *s);
		virtual ~InstructionMultiplyInteger();
};
class InstructionMultiplyReal : public Instruction
{
	public:
		InstructionMultiplyReal();
		virtual int execute(Core *s);
		virtual ~InstructionMultiplyReal();
};
class InstructionDivideInteger : public Instruction
{
	public:
		InstructionDivideInteger();
		virtual int execute(Core *s);
		virtual ~InstructionDivideInteger();
};
class InstructionDivideReal : public Instruction
{
	public:
		InstructionDivideReal();
		virtual int execute(Core *s);
		virtual ~InstructionDivideReal();
};
class InstructionModulo : public Instruction
{
	public:
		InstructionModulo();
		virtual int execute(Core *s);
		virtual ~InstructionModulo();
};
class InstructionBinaryAnd : public Instruction
{
	public:
		InstructionBinaryAnd();
		virtual int execute(Core *s);
		virtual ~InstructionBinaryAnd();
};
class InstructionAnd : public Instruction
{
	public:
		InstructionAnd();
		virtual int execute(Core *s);
		virtual ~InstructionAnd();
};
class InstructionBinaryOr : public Instruction
{
	public:
		InstructionBinaryOr();
		virtual int execute(Core *s);
		virtual ~InstructionBinaryOr();
};
class InstructionOr : public Instruction
{
	public:
		InstructionOr();
		virtual int execute(Core *s);
		virtual ~InstructionOr();
};
class InstructionBinaryNot : public Instruction
{
	public:
		InstructionBinaryNot();
		virtual int execute(Core *s);
		virtual ~InstructionBinaryNot();
};
class InstructionNot : public Instruction
{
	public:
		InstructionNot();
		virtual int execute(Core *s);
		virtual ~InstructionNot();
};
//-------------------------------------------------------------------------------------------------------Relation------------------------------
class InstructionGtInteger : public Instruction
{
	public:
		InstructionGtInteger();
		virtual int execute(Core *s);
		virtual ~InstructionGtInteger();
};
class InstructionGtReal : public Instruction
{
	public:
		InstructionGtReal();
		virtual int execute(Core *s);
		virtual ~InstructionGtReal();
};
class InstructionGeInteger : public Instruction
{
	public:
		InstructionGeInteger();
		virtual int execute(Core *s);
		virtual ~InstructionGeInteger();
};
class InstructionGeReal : public Instruction
{
	public:
		InstructionGeReal();
		virtual int execute(Core *s);
		virtual ~InstructionGeReal();
};
class InstructionEqualInteger : public Instruction //na pointre
{
	public:
		InstructionEqualInteger();
		virtual int execute(Core *s);
		virtual ~InstructionEqualInteger();
};

class InstructionEqualReal : public Instruction
{
	public:
		InstructionEqualReal();
		virtual int execute(Core *s);
		virtual ~InstructionEqualReal();
};
class InstructionEqualObject : public Instruction
{
	public:
		InstructionEqualObject();
		virtual int execute(Core *s);
		virtual ~InstructionEqualObject();
};
class InstructionNotEqual : public Instruction
{
	public:
		InstructionNotEqual();
		virtual int execute(Core *s);
		virtual ~InstructionNotEqual();
};
class InstructionNotEqualInteger : public Instruction
{
	public:
		InstructionNotEqualInteger();
		virtual int execute(Core *s);
		virtual ~InstructionNotEqualInteger();
};
class InstructionNotEqualReal : public Instruction
{
	public:
		InstructionNotEqualReal();
		virtual int execute(Core *s);
		virtual ~InstructionNotEqualReal();
};
class InstructionNotEqualObject : public Instruction
{
	public:
		InstructionNotEqualObject();
		virtual int execute(Core *s);
		virtual ~InstructionNotEqualObject();
};

class InstructionLtInteger : public Instruction
{
	public:
		InstructionLtInteger();
		virtual int execute(Core *s);
		virtual ~InstructionLtInteger();
};
class InstructionLtReal : public Instruction
{
	public:
		InstructionLtReal();
		virtual int execute(Core *s);
		virtual ~InstructionLtReal();
};
class InstructionLeInteger : public Instruction
{
	public:
		InstructionLeInteger();
		virtual int execute(Core *s);
		virtual ~InstructionLeInteger();
};

class InstructionLeReal : public Instruction
{
	public:
		InstructionLeReal();
		virtual int execute(Core *s);
		virtual ~InstructionLeReal();
};

class InstructionBegin : public Instruction
{
	public:
		InstructionBegin(size_t d = 0); //label for 
		size_t depth;
		virtual int execute(Core *s);
		virtual ~InstructionBegin(); //label for 
};
class InstructionEndBlock : public Instruction
{
	public:
		InstructionEndBlock(size_t end_l = 0);
		size_t end_loop;
		virtual int execute(Core *s);
		virtual ~InstructionEndBlock();
};
//--------------------------------------------------Interaction--------------------------------------------------
class InstructionSee : public Instruction
{
	public:
		InstructionSee(Node *s);
		virtual int execute(Core *s);
		virtual ~InstructionSee();
};
class InstructionEye : public Instruction
{
	public:
		InstructionEye();
		virtual int execute(Core *s);
		virtual ~InstructionEye();
};
class InstructionStep : public Instruction
{
	public:
		InstructionStep();
		virtual int execute(Core *s);
		virtual ~InstructionStep();
};
class InstructionStepDefault : public Instruction
{
	public:
		InstructionStepDefault();
		virtual int execute(Core *s);
		virtual ~InstructionStepDefault();
};
class InstructionWait : public Instruction
{
	public:
		InstructionWait();
		virtual int execute(Core *s);
		virtual ~InstructionWait();
};
class InstructionShootLocation : public Instruction
{
	public:
		InstructionShootLocation();
		virtual int execute(Core *s);
		virtual ~InstructionShootLocation();
};
class InstructionShootAngle : public Instruction
{
	public:
		InstructionShootAngle();
		virtual int execute(Core *s);
		virtual ~InstructionShootAngle();
};

class InstructionTurn : public Instruction
{
	public:
		InstructionTurn();
		virtual int execute(Core *s);
		virtual ~InstructionTurn();
};
class InstructionTurnR : public Instruction
{
	public:
		InstructionTurnR();
		virtual int execute(Core *s);
		virtual ~InstructionTurnR();
};
class InstructionTurnL: public Instruction
{
	public:
		InstructionTurnL();
		virtual int execute(Core *s);
		virtual ~InstructionTurnL();
};
class InstructionHit: public Instruction
{
	public:
		InstructionHit();
		virtual int execute(Core *s);
		virtual ~InstructionHit();
};
//--------------------------------------------
class InstructionIsPlayer: public Instruction
{
	public:
		InstructionIsPlayer();
		virtual int execute(Core *s);
		virtual ~InstructionIsPlayer();
};
class InstructionIsWall: public Instruction
{
	public:
		InstructionIsWall();
		virtual int execute(Core *s);
		virtual ~InstructionIsWall();
};
class InstructionIsMissille: public Instruction
{
	public:
		InstructionIsMissille();
		virtual int execute(Core *s);
		virtual ~InstructionIsMissille();
};
class InstructionLocate: public Instruction
{
	Create_type type;
	public:
		InstructionLocate(Create_type t);
		virtual int execute(Core *s);
		virtual ~InstructionLocate();
};
class InstructionIsMoving: public Instruction
{
	public:
		InstructionIsMoving();
		virtual int execute(Core *s);
		virtual ~InstructionIsMoving();
};
#endif
