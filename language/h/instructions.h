#ifndef __INSTR__
#define __INSTR__
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "../../add-ons/h/help_functions.h"
#include "node.h"
#include "core.h"
#include "functions.h"

enum Instr
{		
	IGroup_undefined = 0,
	IGroup_call,
	IGroup_create ,
	IGroup_loadlocal ,
	IGroup_loadglobal ,
	IGroup_load ,
	IGroup_conversiontoint ,
	IGroup_conversiontoreal,
	IGroup_duplicate,
	IGroup_storeinteger ,
	IGroup_storereal ,
	IGroup_storeobject ,
	IGroup_store ,
	IGroup_pop ,
	IGroup_mustjump ,
	IGroup_jump ,
	IGroup_break ,
	IGroup_continue ,
	IGroup_return ,
	IGroup_restore,
	IGroup_removetemp,
	IGroup_plusplusinteger ,
	IGroup_plusplusreal ,
	IGroup_minusminusinteger ,
	IGroup_minusminusreal ,
	IGroup_plusinteger ,
	IGroup_plusreal ,
	IGroup_minusinteger ,
	IGroup_minusreal ,
	IGroup_multiplyinteger ,
	IGroup_multiplyreal ,
	IGroup_divideinteger ,
	IGroup_dividereal ,
	IGroup_modulo ,
	IGroup_binaryand ,
	IGroup_and ,
	IGroup_binaryor ,
	IGroup_or ,
	IGroup_binarynot ,
	IGroup_not ,
	IGroup_gtinteger ,
	IGroup_gtreal ,
	IGroup_geinteger ,
	IGroup_gereal ,
	IGroup_equalinteger ,
	IGroup_equalreal ,
	IGroup_equalobject ,
	IGroup_notequal ,
	IGroup_notequalinteger ,
	IGroup_notequalreal ,
	IGroup_notequalobject ,
	IGroup_ltinteger ,
	IGroup_ltreal ,
	IGroup_leinteger ,
	IGroup_lereal ,
	IGroup_begin ,
	IGroup_endblock ,
	IGroup_see ,
	IGroup_eye ,
	IGroup_fetchstate ,
	IGroup_step ,
	IGroup_stepdefault ,
	IGroup_wait ,
	IGroup_shootlocation ,
	IGroup_shootangle ,
	IGroup_turn ,
	IGroup_turnr ,
	IGroup_turnl,
	IGroup_hit,
	IGroup_isplayer,
	IGroup_iswall,
	IGroup_ismissille,
	IGroup_locate,
	IGroup_ismoving,
	IGroups
};
class Instruction
{
protected:
	Node * node;
	bool constant;
public:
	size_t group; //inukatne pre azdu instrukciu
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
		virtual int execute(Core * c);
		virtual xmlNodePtr xml_format();
		InstructionCreate(Node * n);
		virtual ~InstructionCreate();
};
class InstructionLoadLocal : public Instruction
{
	public:
		virtual int execute(Core * c);
		virtual xmlNodePtr xml_format();
		InstructionLoadLocal(Node * n);
		InstructionLoadLocal(); //loadne z toho, co ma na value stacku
		virtual ~InstructionLoadLocal();
};
class InstructionLoadGlobal : public Instruction
{
	public:
		virtual xmlNodePtr xml_format();
		virtual int execute(Core * c);
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
		virtual int execute(Core * c);
		InstructionLoad(int i);
		InstructionLoad(float f);
		InstructionLoad(); 
		virtual ~InstructionLoad();
};
class InstructionConversionToInt : public Instruction
{
	public:
		InstructionConversionToInt();
		virtual int execute(Core * c);
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
		virtual int execute(Core * c);
		InstructionDuplicate();
		virtual ~InstructionDuplicate();
};
class InstructionStoreInteger : public Instruction
{
	public:
		virtual int execute(Core * c);
		InstructionStoreInteger();
		virtual ~InstructionStoreInteger();
};
class InstructionStoreReal : public Instruction
{
	public:
		virtual int execute(Core * c);
		InstructionStoreReal();
		virtual ~InstructionStoreReal();
};
/*Location, struct, array sa robi v InstructionStore, panlizacia potom vyppocitana*/

class InstructionStoreObject : public Instruction
{ 
	public:
		virtual int execute(Core * c);
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
		virtual int execute(Core * c);
		virtual ~Call();
};

class InstructionPop : public Instruction
{
	public:
		virtual int execute(Core * c);
		InstructionPop();
		virtual ~InstructionPop();
};

class InstructionMustJump : public Instruction
{
	int shift;
	public:
		InstructionMustJump(int steps);
		virtual int execute(Core * c);
		virtual xmlNodePtr xml_format();
		virtual ~InstructionMustJump();
};
class InstructionJump : public Instruction
{
	int yes, no;
	public:
		virtual int execute(Core * c);
		virtual xmlNodePtr xml_format();
		InstructionJump(int stepsYes, int stepsNo);
		virtual ~InstructionJump();
};

class InstructionBreak : public Instruction
{
	public:
		InstructionBreak(int depth_ = 0);
		int jump, depth;
		virtual int execute(Core * c);
		virtual xmlNodePtr xml_format();
		virtual void set(size_t jump, size_t depth);
		virtual ~InstructionBreak();
};
class InstructionContinue : public InstructionBreak //stejne ako break, ale skace inam
{
	public:
		InstructionContinue(int depth_ = 0);
		virtual int execute(Core * c);
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
		virtual int execute(Core * c);
		virtual ~InstructionPlusPlusInteger();
};
class InstructionPlusPlusReal : public Instruction
{
	public:
		InstructionPlusPlusReal();
		virtual int execute(Core * c);
		virtual ~InstructionPlusPlusReal();
};
class InstructionMinusMinusInteger : public Instruction
{
	public:
		InstructionMinusMinusInteger();
		virtual int execute(Core * c);
		virtual ~InstructionMinusMinusInteger();
};
class InstructionMinusMinusReal : public Instruction
{
	public:
		InstructionMinusMinusReal();
		virtual int execute(Core * c);
		virtual ~InstructionMinusMinusReal();
};
/*class InstructionPlus : public Instruction //pre pointre?Location
{
	public:
		virtual int execute(Core * c);
		InstructionPlus();
};*/
class InstructionPlusInteger : public Instruction //pre pointre
{
	public:
		InstructionPlusInteger();
		virtual int execute(Core * c);
		virtual ~InstructionPlusInteger();
};
class InstructionPlusReal : public Instruction //pre pointre
{
	public:
		InstructionPlusReal();
		virtual int execute(Core * c);
		virtual ~InstructionPlusReal();
};
class InstructionMinusInteger : public Instruction
{
	public:
		InstructionMinusInteger();
		virtual int execute(Core * c);
		virtual ~InstructionMinusInteger();
};

class InstructionMinusReal : public Instruction
{
	public:
		InstructionMinusReal();
		virtual int execute(Core * c);
		virtual ~InstructionMinusReal();
};
class InstructionMultiplyInteger : public Instruction
{
	public:
		InstructionMultiplyInteger();
		virtual int execute(Core * c);
		virtual ~InstructionMultiplyInteger();
};
class InstructionMultiplyReal : public Instruction
{
	public:
		InstructionMultiplyReal();
		virtual int execute(Core * c);
		virtual ~InstructionMultiplyReal();
};
class InstructionDivideInteger : public Instruction
{
	public:
		InstructionDivideInteger();
		virtual int execute(Core * c);
		virtual ~InstructionDivideInteger();
};
class InstructionDivideReal : public Instruction
{
	public:
		InstructionDivideReal();
		virtual int execute(Core * c);
		virtual ~InstructionDivideReal();
};
class InstructionModulo : public Instruction
{
	public:
		InstructionModulo();
		virtual int execute(Core * c);
		virtual ~InstructionModulo();
};
class InstructionBinaryAnd : public Instruction
{
	public:
		InstructionBinaryAnd();
		virtual int execute(Core * c);
		virtual ~InstructionBinaryAnd();
};
class InstructionAnd : public Instruction
{
	public:
		InstructionAnd();
		virtual int execute(Core * c);
		virtual ~InstructionAnd();
};
class InstructionBinaryOr : public Instruction
{
	public:
		InstructionBinaryOr();
		virtual int execute(Core * c);
		virtual ~InstructionBinaryOr();
};
class InstructionOr : public Instruction
{
	public:
		InstructionOr();
		virtual int execute(Core * c);
		virtual ~InstructionOr();
};
class InstructionBinaryNot : public Instruction
{
	public:
		InstructionBinaryNot();
		virtual int execute(Core * c);
		virtual ~InstructionBinaryNot();
};
class InstructionNot : public Instruction
{
	public:
		InstructionNot();
		virtual int execute(Core * c);
		virtual ~InstructionNot();
};
//-------------------------------------------------------------------------------------------------------Relation------------------------------
class InstructionGtInteger : public Instruction
{
	public:
		InstructionGtInteger();
		virtual int execute(Core * c);
		virtual ~InstructionGtInteger();
};
class InstructionGtReal : public Instruction
{
	public:
		InstructionGtReal();
		virtual int execute(Core * c);
		virtual ~InstructionGtReal();
};
class InstructionGeInteger : public Instruction
{
	public:
		InstructionGeInteger();
		virtual int execute(Core * c);
		virtual ~InstructionGeInteger();
};
class InstructionGeReal : public Instruction
{
	public:
		InstructionGeReal();
		virtual int execute(Core * c);
		virtual ~InstructionGeReal();
};
class InstructionEqualInteger : public Instruction //na pointre
{
	public:
		InstructionEqualInteger();
		virtual int execute(Core * c);
		virtual ~InstructionEqualInteger();
};

class InstructionEqualReal : public Instruction
{
	public:
		InstructionEqualReal();
		virtual int execute(Core * c);
		virtual ~InstructionEqualReal();
};
class InstructionEqualObject : public Instruction
{
	public:
		InstructionEqualObject();
		virtual int execute(Core * c);
		virtual ~InstructionEqualObject();
};
class InstructionNotEqual : public Instruction
{
	public:
		InstructionNotEqual();
		virtual int execute(Core * c);
		virtual ~InstructionNotEqual();
};
class InstructionNotEqualInteger : public Instruction
{
	public:
		InstructionNotEqualInteger();
		virtual int execute(Core * c);
		virtual ~InstructionNotEqualInteger();
};
class InstructionNotEqualReal : public Instruction
{
	public:
		InstructionNotEqualReal();
		virtual int execute(Core * c);
		virtual ~InstructionNotEqualReal();
};
class InstructionNotEqualObject : public Instruction
{
	public:
		InstructionNotEqualObject();
		virtual int execute(Core * c);
		virtual ~InstructionNotEqualObject();
};

class InstructionLtInteger : public Instruction
{
	public:
		InstructionLtInteger();
		virtual int execute(Core * c);
		virtual ~InstructionLtInteger();
};
class InstructionLtReal : public Instruction
{
	public:
		InstructionLtReal();
		virtual int execute(Core * c);
		virtual ~InstructionLtReal();
};
class InstructionLeInteger : public Instruction
{
	public:
		InstructionLeInteger();
		virtual int execute(Core * c);
		virtual ~InstructionLeInteger();
};

class InstructionLeReal : public Instruction
{
	public:
		InstructionLeReal();
		virtual int execute(Core * c);
		virtual ~InstructionLeReal();
};

class InstructionBegin : public Instruction
{
	public:
		InstructionBegin(size_t d = 0); //label for 
		size_t depth;
		virtual int execute(Core * c);
		virtual ~InstructionBegin(); //label for 
};
class InstructionEndBlock : public Instruction
{
	public:
		InstructionEndBlock(size_t end_l = 0);
		size_t end_loop;
		virtual int execute(Core * c);
		virtual ~InstructionEndBlock();
};
//--------------------------------------------------Interaction--------------------------------------------------
class InstructionSee : public Instruction
{
	public:
		InstructionSee();
		virtual int execute(Core * c);
		virtual ~InstructionSee();
};
class InstructionEye : public Instruction
{
	public:
		InstructionEye();
		virtual int execute(Core * c);
		virtual ~InstructionEye();
};
class InstructionFetchState : public Instruction
{
	public:
		InstructionFetchState();
		virtual int execute(Core * c);
		virtual ~InstructionFetchState();
};
class InstructionStep : public Instruction
{
	public:
		InstructionStep();
		virtual int execute(Core * c);
		virtual ~InstructionStep();
};
class InstructionStepDefault : public Instruction
{
	public:
		InstructionStepDefault();
		virtual int execute(Core * c);
		virtual ~InstructionStepDefault();
};
class InstructionWait : public Instruction
{
	public:
		InstructionWait();
		virtual int execute(Core * c);
		virtual ~InstructionWait();
};
class InstructionShootLocation : public Instruction
{
	public:
		InstructionShootLocation();
		virtual int execute(Core * c);
		virtual ~InstructionShootLocation();
};
class InstructionShootAngle : public Instruction
{
	public:
		InstructionShootAngle();
		virtual int execute(Core * c);
		virtual ~InstructionShootAngle();
};

class InstructionTurn : public Instruction
{
	public:
		InstructionTurn();
		virtual int execute(Core * c);
		virtual ~InstructionTurn();
};
class InstructionTurnR : public Instruction
{
	public:
		InstructionTurnR();
		virtual int execute(Core * c);
		virtual ~InstructionTurnR();
};
class InstructionTurnL: public Instruction
{
	public:
		InstructionTurnL();
		virtual int execute(Core * c);
		virtual ~InstructionTurnL();
};
class InstructionHit: public Instruction
{
	public:
		InstructionHit();
		virtual int execute(Core * c);
		virtual ~InstructionHit();
};
//--------------------------------------------
class InstructionIsPlayer: public Instruction
{
	public:
		InstructionIsPlayer();
		virtual int execute(Core * c);
		virtual ~InstructionIsPlayer();
};
class InstructionIsWall: public Instruction
{
	public:
		InstructionIsWall();
		virtual int execute(Core * c);
		virtual ~InstructionIsWall();
};
class InstructionIsMissille: public Instruction
{
	public:
		InstructionIsMissille();
		virtual int execute(Core * c);
		virtual ~InstructionIsMissille();
};
class InstructionLocate: public Instruction
{
	Create_type type;
	public:
		InstructionLocate(Create_type t);
		virtual int execute(Core * c);
		virtual ~InstructionLocate();
};
class InstructionIsMoving: public Instruction
{
	public:
		InstructionIsMoving();
		virtual int execute(Core * c);
		virtual ~InstructionIsMoving();
};
#endif
