#include "instructions.h"

InstructionCreate::InstructionCreate()
{
	name_ = "InstructionCreate";
}
InstructionLoad::InstructionLoad()
{
	name_ = "InstructionLoad";
}
InstructionLoad::InstructionLoad(std::string s)
{
	name_ = "InstructionLoad";
}
InstructionLoad::InstructionLoad(int i)
{
	name_ = "InstructionLoad";
}
InstructionLoad::InstructionLoad(float f)
{
	name_ = "InstructionLoad";
}
InstructionStore::InstructionStore()
{
	name_ = "InstructionStore";
}
Call::Call()
{
	name_ = "Call";
}
CallMethod::CallMethod()
{
	name_ = "CallMethod";
}
CallMethod::CallMethod(std::string s)
{
	name_ = "CallMethod";
}
InstructionPop::InstructionPop()
{
	name_ = "InstructionPop";
}
InstructionMustJump::InstructionMustJump(int steps)
{
	name_ = "InstructionMustJump";
}
InstructionJump::InstructionJump(int yes, int no)
{
	name_ = "InstructionJump";
}
InstructionReturn::InstructionReturn()
{
	name_ = "InstructionReturn";
}
InstructionBreak::InstructionBreak()
{
	name_ = "InstructionBreak";
}
InstructionPlusPlus::InstructionPlusPlus()
{
	name_ = "InstructionPlusPlus";
}
InstructionMinusMinus::InstructionMinusMinus()
{
	name_ = "InstructionMinusMinus";
}
InstructionPlus::InstructionPlus()
{
	name_ = "InstructionPlus";
}
InstructionMinus::InstructionMinus()
{
	name_ = "InstructionMinus";
}
InstructionMultiply::InstructionMultiply()
{
	name_ = "InstructionMultiply";
}
InstructionDivide::InstructionDivide()
{
	name_ = "InstructionDivide";
}
InstructionModulo::InstructionModulo()
{
	name_ = "InstructionModulo";
}
InstructionBinaryAnd::InstructionBinaryAnd()
{
	name_ = "InstructionBinaryAnd";
}
InstructionBinaryOr::InstructionBinaryOr()
{
	name_ = "InstructionBinaryOr";
}
//----------------------------------------------------------------------------------------------------
InstructionGe::InstructionGe()
{
	name_ = "InstructionGe";
}
InstructionGt::InstructionGt()
{
	name_ = "InstructionGt";
}
InstructionEqual::InstructionEqual()
{
	name_ = "InstructionEqual";
}
InstructionLt::InstructionLt()
{
	name_ = "InstructionLt";
}
InstructionLe::InstructionLe()
{
	name_ = "InstructionLe";
}
InstructionBegin::InstructionBegin
{
	name_ = "InstructionBegin";
}
InstructionEndBlock::InstructionEndBlock
{
	name_ = "InstructionEndBlock";
}

std::string Instruction::name()
{
	return name_;
}
Instruction::Instruction()
{
	values = NULL;
}
