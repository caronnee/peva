#include "instructions.h"

Instruction::Instruction()
{
}
xmlNodePtr Instruction::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	return n;	
}
int Instruction::breaks()
{
	return -1;
}
InstructionCreate::InstructionCreate()
{
	name_ = "InstructionCreate";
}
InstructionCreate::InstructionCreate(Node * n)
{
	node = n;
	name_ = "InstructionCreate";
}
xmlNodePtr InstructionCreate::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr child = xmlNewText( BAD_CAST node->name.c_str());
	xmlAddChild(n, child);
	return n;
}
InstructionLoadLocal::InstructionLoadLocal()
{
	name_ = "InstructionLoadLocal";
}
InstructionLoadLocal::InstructionLoadLocal(Node * n)
{
	name_ = "InstructionLoadLocal";
}
xmlNodePtr InstructionLoadLocal::xml_format()
{
	return NULL;
}
InstructionLoadGlobal::InstructionLoadGlobal()
{
	node = NULL;
	name_ = "InstructionLoadGlobal";
}
InstructionLoadGlobal::InstructionLoadGlobal(Node * n)
{
	node = n;
	name_ = "InstructionLoadGlobal";
}
xmlNodePtr InstructionLoadGlobal::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr child = xmlNewText( BAD_CAST node->name.c_str());
	xmlAddChild(n, child);
	return n;
}
InstructionLoad::InstructionLoad()
{
	node = NULL;
	name_ = "InstructionLoad";
}
InstructionLoad::InstructionLoad(int i)
{
	destroy_node = true;
	node = new Node("const",Create_type(TypeInteger));
	node->IntegerValue.push_back(i);
	name_ = "InstructionLoad";
}
InstructionLoad::InstructionLoad(float f)
{
	destroy_node = true;
	node = new Node("const",Create_type(TypeReal));
	node->RealValue.push_back(f);
	name_ = "InstructionLoad";
}
xmlNodePtr InstructionLoad::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr child;
        if (node ==NULL)
		child= xmlNewText( BAD_CAST node->name.c_str());
	else
	{
		switch (node->type)
		{
			case TypeInteger:
				{
					child = xmlNewNode( NULL, BAD_CAST "integer");
					std::string s = deconvert<int>(node->IntegerValue[0]);
					xmlNodePtr grand_child = xmlNewText(BAD_CAST s.c_str()); 
				}
		}
	}
	xmlAddChild(n, child);
	return n;
}
InstructionStore::InstructionStore()
{
	name_ = "InstructionStore";
}
xmlNodePtr InstructionStore::xml_format()
{
	return NULL;

}
Call::Call()
{
	name_ = "Call";
}
Call::Call(std::string s)
{
	name_ = "Call";
}
xmlNodePtr Call::xml_format()
{
	return NULL;

}
CallMethod::CallMethod()
{
	name_ = "CallMethod";
}
CallMethod::CallMethod(std::string s) //tu vazne potrebujem vediet meno tej premennej
{
	name_ = "CallMethod";
}
xmlNodePtr CallMethod::xml_format()
{

	return NULL;
}
InstructionPop::InstructionPop()
{
	name_ = "InstructionPop";
}
InstructionMustJump::InstructionMustJump(int steps)
{
	name_ = "InstructionMustJump";
}
xmlNodePtr InstructionMustJump::xml_format()
{

	return NULL;
}
InstructionJump::InstructionJump(int yes, int no)
{
	name_ = "InstructionJump";
}
xmlNodePtr InstructionJump::xml_format()
{

	return NULL;
}
InstructionReturn::InstructionReturn()
{
	name_ = "InstructionReturn";
}
xmlNodePtr InstructionReturn::xml_format()
{
	return NULL;

}
InstructionBreak::InstructionBreak(int label)
{
	name_ = "InstructionBreak";
}
xmlNodePtr InstructionBreak::xml_format()
{
	return NULL;
}
int InstructionBreak::breaks()
{
	return loop_label;
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
InstructionAnd::InstructionAnd()
{
	name_ = "InstructionAnd";
}
InstructionBinaryOr::InstructionBinaryOr()
{
	name_ = "InstructionBinaryOr";
}
InstructionOr::InstructionOr()
{
	name_ = "InstructionOr";
}
InstructionBinaryNot::InstructionBinaryNot()
{
	name_ = "InstructionBinaryNot";
}
InstructionNot::InstructionNot()
{
	name_ = "InstructionNot";
}
//----------------------------------------------------------------------------------------------------
InstructionGt::InstructionGt()
{
	name_ = "InstructionGt";
}
InstructionGe::InstructionGe()
{
	name_ = "InstructionGe";
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
InstructionBegin::InstructionBegin()
{
	name_ = "InstructionBegin";
}
InstructionEndBlock::InstructionEndBlock()
{
	name_ = "InstructionEndBlock";
}

std::string Instruction::name()
{
	return name_;
}

