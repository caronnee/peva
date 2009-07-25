#include "instructions.h"

InstructionCreate::InstructionCreate()
{
	name_ = "InstructionCreate";
};
InstructionCreate::InstructionCreate(Node * n)
{
	name_ = "InstructionCreate";
};
InstructionLoad::InstructionLoad()
{
	name_ = "InstructionLoad";
};
InstructionLoadGlobal::InstructionLoadGlobal()
{
	name_ = "InstructionLoadGlobal";
};
InstructionLoadGlobal::InstructionLoadGlobal(Node * n)
{
	name_ = "InstructionLoadGlobal";
};
InstructionLoadLocal::InstructionLoadLocal()
{
	name_ = "InstructionLoadLocal";
};
InstructionLoadLocal::InstructionLoadLocal(Node * n)
{
	name_ = "InstructionLoadLocal";
};
InstructionLoad::InstructionLoad(int i)
{
	name_ = "InstructionLoad";
};
InstructionLoad::InstructionLoad(float f)
{
	name_ = "InstructionLoad";
};
InstructionStore::InstructionStore()
{
	name_ = "InstructionStore";
};
Call::Call()
{
	name_ = "Call";
};
Call::Call(std::string s)
{
	name_ = "Call";
};
CallMethod::CallMethod()
{
	name_ = "CallMethod";
};
CallMethod::CallMethod(std::string s) //tu vazne potrebujem vediet meno tej premennej
{
	name_ = "CallMethod";
};
InstructionPop::InstructionPop()
{
	name_ = "InstructionPop";
};
InstructionMustJump::InstructionMustJump(int steps)
{
	name_ = "InstructionMustJump";
};
InstructionJump::InstructionJump(int yes, int no)
{
	name_ = "InstructionJump";
};
InstructionReturn::InstructionReturn()
{
	name_ = "InstructionReturn";
};
InstructionBreak::InstructionBreak()
{
	name_ = "InstructionBreak";
};
InstructionPlusPlus::InstructionPlusPlus()
{
	name_ = "InstructionPlusPlus";
};
InstructionMinusMinus::InstructionMinusMinus()
{
	name_ = "InstructionMinusMinus";
};
InstructionPlus::InstructionPlus()
{
	name_ = "InstructionPlus";
};
InstructionMinus::InstructionMinus()
{
	name_ = "InstructionMinus";
};
InstructionMultiply::InstructionMultiply()
{
	name_ = "InstructionMultiply";
};
InstructionDivide::InstructionDivide()
{
	name_ = "InstructionDivide";
};
InstructionModulo::InstructionModulo()
{
	name_ = "InstructionModulo";
};
InstructionBinaryAnd::InstructionBinaryAnd()
{
	name_ = "InstructionBinaryAnd";
};
InstructionAnd::InstructionAnd()
{
	name_ = "InstructionAnd";
};
InstructionBinaryOr::InstructionBinaryOr()
{
	name_ = "InstructionBinaryOr";
};
InstructionOr::InstructionOr()
{
	name_ = "InstructionOr";
};
InstructionBinaryNot::InstructionBinaryNot()
{
	name_ = "InstructionBinaryNot";
};
InstructionNot::InstructionNot()
{
	name_ = "InstructionNot";
};
//----------------------------------------------------------------------------------------------------
InstructionGt::InstructionGt()
{
	name_ = "InstructionGt";
};
InstructionGe::InstructionGe()
{
	name_ = "InstructionGe";
};
InstructionEqual::InstructionEqual()
{
	name_ = "InstructionEqual";
};
InstructionLt::InstructionLt()
{
	name_ = "InstructionLt";
};
InstructionLe::InstructionLe()
{
	name_ = "InstructionLe";
};
InstructionBegin::InstructionBegin()
{
	name_ = "InstructionBegin";
};
InstructionEndBlock::InstructionEndBlock()
{
	name_ = "InstructionEndBlock";
};

std::string Instruction::name()
{
	return name_;
};
Instruction::Instruction()
{
	values = NULL;
};
