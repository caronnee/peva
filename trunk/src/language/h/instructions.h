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
	IGroup_create,
	IGroup_load,
	IGroup_conversion,
	IGroup_duplicate,
	IGroup_store,
	IGroup_pop,
	IGroup_jump,
	IGroup_break,
	IGroup_continue,
	IGroup_return,
	IGroup_restore,
	IGroup_removetemp,
	IGroup_plusplus,
	IGroup_minusminus,
	IGroup_plus,
	IGroup_minus,
	IGroup_multiply,
	IGroup_divide,
	IGroup_modulo,
	IGroup_binaryand,
	IGroup_and,
	IGroup_binaryor,
	IGroup_or,
	IGroup_binarynot,
	IGroup_not,
	IGroup_gt,
	IGroup_ge,
	IGroup_equal,
	IGroup_notequal ,
	IGroup_lt,
	IGroup_le,
	IGroup_begin,
	IGroup_endblock,
	IGroup_see,
	IGroup_eye,
	IGroup_fetchstate,
	IGroup_step,
	IGroup_wait,
	IGroup_shoot,
	IGroup_turn,
	IGroup_hit,
	IGroup_check,
	IGroup_locate,
	IGroup_direction,
	IGroup_random,
	IGroups
};

class Instruction
{
protected:
	/* node that can be used */
	Node * node;
	//bool constant;

	/*name of intruction */
	std::string name_;

	unsigned line;
public:
	size_t group; //inukatne pre azdu instrukciu, TODO spravit z toho funkciu
	/* Contructor */
	Instruction(unsigned line);

	/* returns name of intruction */
	std::string name();
	
	/* return xml node */
	virtual xmlNodePtr xml_format();

	/* executes an instruction */
	virtual int execute(Core * s) = 0;

	/* virtual destructor */
	virtual ~Instruction();
};

class InstructionCreate : public Instruction
{
	public:
		virtual int execute(Core * c);
		virtual xmlNodePtr xml_format();
	InstructionCreate(unsigned line, Node * n);
		virtual ~InstructionCreate();
};
class InstructionLoadLocal : public Instruction
{
	public:
		virtual int execute(Core * c);
		virtual xmlNodePtr xml_format();
		InstructionLoadLocal(unsigned line,Node * n);
		InstructionLoadLocal(unsigned line); //loadne z toho, co ma na value stacku
		virtual ~InstructionLoadLocal();
};
class InstructionLoadGlobal : public Instruction
{
	public:
		virtual xmlNodePtr xml_format();
		virtual int execute(Core * c);
	InstructionLoadGlobal(unsigned line, Node * n);
	InstructionLoadGlobal(unsigned line); //loadne z toho, co ma na value stacku
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
	InstructionLoad(unsigned line, int i);
	InstructionLoad(unsigned line, float f);
	InstructionLoad(unsigned line); 
		virtual ~InstructionLoad();
};
class InstructionConversionToInt : public Instruction
{
	public:
	InstructionConversionToInt(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionConversionToInt();
};
class InstructionConversionToReal: public Instruction
{
	public:
	InstructionConversionToReal(unsigned line);
		virtual int execute(Core *c);
		virtual ~InstructionConversionToReal();
};
class InstructionDuplicate: public Instruction
{
	public:
		virtual int execute(Core * c);
	InstructionDuplicate(unsigned line);
		virtual ~InstructionDuplicate();
};
class InstructionStoreRef : public Instruction
{
	public:
	InstructionStoreRef(unsigned line, Node * n);
		virtual int execute(Core * c);
		virtual ~InstructionStoreRef();
};
class InstructionStoreInteger : public Instruction
{
	public:
		virtual int execute(Core * c);
	InstructionStoreInteger(unsigned line);
		virtual ~InstructionStoreInteger();
};
class InstructionStoreReal : public Instruction
{
	public:
		virtual int execute(Core * c);
	InstructionStoreReal(unsigned line);
		virtual ~InstructionStoreReal();
};
/*Location, struct, array sa robi v InstructionStore, panlizacia potom vyppocitana*/

class InstructionStoreObject : public Instruction
{ 
	public:
		virtual int execute(Core * c);
	InstructionStoreObject(unsigned line);
		virtual ~InstructionStoreObject();
};
class InstructionCall : public Instruction
{
	Function* function;
	public:
	InstructionCall(unsigned line, Function * f);
		virtual xmlNodePtr xml_format();
		virtual int execute(Core * c);
		virtual ~InstructionCall();
};

class InstructionPop : public Instruction
{
	public:
		virtual int execute(Core * c);
	InstructionPop(unsigned line);
		virtual ~InstructionPop();
};

class InstructionMustJump : public Instruction
{
	int shift;
	public:
	InstructionMustJump(unsigned line, int steps);
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
	InstructionJump(unsigned line, int stepsYes, int stepsNo);
		virtual ~InstructionJump();
};

class InstructionBreak : public Instruction
{
	public:
		InstructionBreak(unsigned line, int depth_ = 0);
		int jump, depth;
		virtual int execute(Core * c);
		virtual xmlNodePtr xml_format();
		virtual void set(size_t jump, size_t depth);
		virtual ~InstructionBreak();
};
class InstructionContinue : public InstructionBreak //stejne ako break, ale skace inam
{
	public:
	InstructionContinue(unsigned line, int depth_ = 0);
		virtual int execute(Core * c);
		virtual ~InstructionContinue();
};
class InstructionReturn : public Instruction
{
	int depth,jump;
	public:
	InstructionReturn(unsigned line, int dep);
		virtual int execute(Core * c);
		virtual ~InstructionReturn();
};
class InstructionRestore: public Instruction
{
	public:
		virtual int execute(Core * c);
	InstructionRestore(unsigned line);
		virtual ~InstructionRestore();
};

class InstructionRemoveTemp: public Instruction
{
	public:
	InstructionRemoveTemp(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionRemoveTemp();
};

//-----------------------------------COUNTING-----------------------------------------

class InstructionPlusPlusInteger : public Instruction
{
	public:
	InstructionPlusPlusInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionPlusPlusInteger();
};
class InstructionPlusPlusReal : public Instruction
{
	public:
	InstructionPlusPlusReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionPlusPlusReal();
};
class InstructionMinusMinusInteger : public Instruction
{
	public:
	InstructionMinusMinusInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionMinusMinusInteger();
};
class InstructionMinusMinusReal : public Instruction
{
	public:
	InstructionMinusMinusReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionMinusMinusReal();
};
/*class InstructionPlus : public Instruction //pre pointre?Location
{
	public:
		virtual int execute(Core * c);
	InstructionPlus(unsigned line);
};*/
class InstructionPlusInteger : public Instruction //pre pointre
{
	public:
	InstructionPlusInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionPlusInteger();
};
class InstructionPlusReal : public Instruction //pre pointre
{
	public:
	InstructionPlusReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionPlusReal();
};
class InstructionMinusInteger : public Instruction
{
	public:
	InstructionMinusInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionMinusInteger();
};

class InstructionMinusReal : public Instruction
{
	public:
	InstructionMinusReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionMinusReal();
};
class InstructionMultiplyInteger : public Instruction
{
	public:
	InstructionMultiplyInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionMultiplyInteger();
};
class InstructionMultiplyReal : public Instruction
{
	public:
	InstructionMultiplyReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionMultiplyReal();
};
class InstructionDivideInteger : public Instruction
{
	public:
	InstructionDivideInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionDivideInteger();
};
class InstructionDivideReal : public Instruction
{
	public:
	InstructionDivideReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionDivideReal();
};
class InstructionModulo : public Instruction
{
	public:
	InstructionModulo(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionModulo();
};
class InstructionBinaryAnd : public Instruction
{
	public:
	InstructionBinaryAnd(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionBinaryAnd();
};
class InstructionAnd : public Instruction
{
	public:
	InstructionAnd(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionAnd();
};
class InstructionBinaryOr : public Instruction
{
	public:
	InstructionBinaryOr(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionBinaryOr();
};
class InstructionOr : public Instruction
{
	public:
	InstructionOr(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionOr();
};
class InstructionBinaryNot : public Instruction
{
	public:
	InstructionBinaryNot(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionBinaryNot();
};
class InstructionNot : public Instruction
{
	public:
	InstructionNot(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionNot();
};
//-------------------------------------------------------------------------------------------------------Relation------------------------------
class InstructionGtInteger : public Instruction
{
	public:
	InstructionGtInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionGtInteger();
};
class InstructionGtReal : public Instruction
{
	public:
	InstructionGtReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionGtReal();
};
class InstructionGeInteger : public Instruction
{
	public:
	InstructionGeInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionGeInteger();
};
class InstructionGeReal : public Instruction
{
	public:
	InstructionGeReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionGeReal();
};
class InstructionEqualInteger : public Instruction //na pointre
{
	public:
	InstructionEqualInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionEqualInteger();
};

class InstructionEqualReal : public Instruction
{
	public:
	InstructionEqualReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionEqualReal();
};
class InstructionEqualObject : public Instruction
{
	public:
	InstructionEqualObject(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionEqualObject();
};
class InstructionNotEqual : public Instruction
{
	public:
	InstructionNotEqual(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionNotEqual();
};
class InstructionNotEqualInteger : public Instruction
{
	public:
	InstructionNotEqualInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionNotEqualInteger();
};
class InstructionNotEqualReal : public Instruction
{
	public:
	InstructionNotEqualReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionNotEqualReal();
};
class InstructionNotEqualObject : public Instruction
{
	public:
	InstructionNotEqualObject(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionNotEqualObject();
};

class InstructionLtInteger : public Instruction
{
	public:
	InstructionLtInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionLtInteger();
};
class InstructionLtReal : public Instruction
{
	public:
	InstructionLtReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionLtReal();
};
class InstructionLeInteger : public Instruction
{
	public:
	InstructionLeInteger(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionLeInteger();
};

class InstructionLeReal : public Instruction
{
	public:
	InstructionLeReal(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionLeReal();
};

class InstructionBegin : public Instruction
{
	public:
	InstructionBegin(unsigned line, size_t d = 0); //label for 
		size_t depth;
		virtual int execute(Core * c);
		virtual ~InstructionBegin(); //label for 
};
class InstructionEndBlock : public Instruction
{
	public:
	InstructionEndBlock(unsigned line, size_t end_l = 0);
		size_t end_loop;
		virtual int execute(Core * c);
		virtual ~InstructionEndBlock();
};
//--------------------------------------------------Interaction--------------------------------------------------
class InstructionSee : public Instruction
{
	public:
	InstructionSee(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionSee();
};
class InstructionEye : public Instruction
{
	public:
	InstructionEye(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionEye();
};
class InstructionFetchState : public Instruction
{
	public:
	InstructionFetchState(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionFetchState();
};
class InstructionStep : public Instruction
{
	public:
	InstructionStep(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionStep();
};
class InstructionStepDefault : public Instruction
{
	public:
	InstructionStepDefault(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionStepDefault();
};
class InstructionWait : public Instruction
{
	public:
	InstructionWait(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionWait();
};
class InstructionShootAngle : public Instruction
{
	public:
	InstructionShootAngle(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionShootAngle();
};

class InstructionTurn : public Instruction
{
	public:
	InstructionTurn(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionTurn();
};
class InstructionTurnR : public Instruction
{
	public:
	InstructionTurnR(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionTurnR();
};
class InstructionTurnL: public Instruction
{
	public:
	InstructionTurnL(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionTurnL();
};
class InstructionHit: public Instruction
{
	public:
	InstructionHit(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionHit();
};
//--------------------------------------------
class InstructionIsPlayer: public Instruction
{
	public:
	InstructionIsPlayer(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionIsPlayer();
};
class InstructionIsWall: public Instruction
{
	public:
	InstructionIsWall(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionIsWall();
};
class InstructionIsMissille: public Instruction
{
	public:
	InstructionIsMissille(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionIsMissille();
};
class InstructionLocate: public Instruction
{
	Create_type type;
	public:
	InstructionLocate(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionLocate();
};
class InstructionIsMoving: public Instruction
{
	public:
	InstructionIsMoving(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionIsMoving();
};
class InstructionTarget: public Instruction
{
	public:
	InstructionTarget(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionTarget();
};

class InstructionIsEnemy: public Instruction
{
	public:
	InstructionIsEnemy(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionIsEnemy();
};
class InstructionSeeEnemy: public Instruction
{
	public:
	InstructionSeeEnemy(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionSeeEnemy();
};

class InstructionSaveVariable : public Instruction
{
	public:
	InstructionSaveVariable(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionSaveVariable();
};

class InstructionLoadVariable : public Instruction
{
	public:
	InstructionLoadVariable(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionLoadVariable();
};

class InstructionDirection : public Instruction
{
	public:
	InstructionDirection(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionDirection();
};
class InstructionRandom : public Instruction
{
	public:
	InstructionRandom(unsigned line);
		virtual int execute(Core * c);
		virtual ~InstructionRandom();
};
#endif
