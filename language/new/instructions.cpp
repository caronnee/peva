#include "instructions.h"

Instruction::Instruction()
{
	name_ = "UndefinedInstruction";
}
std::string Instruction::name()
{
	return name_;
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
InstructionCreate::InstructionCreate(Node * n)
{
	node = n;
	name_ = "InstructionCreate";
}
int InstructionCreate::execute(Core * c)
{
	Variable * v = c->memory.assign(node->type_of_variable);
	Var var;
	var.var = v;
	var.depth = c->depth;
	node->var.push_back(var); //pridali sme pre akutialne zanorenie premenu
	return 0;
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
	node = NULL;
	name_ = "InstructionLoadLocal";
}
InstructionLoadLocal::InstructionLoadLocal(Node * n)
{
	node = n;
	name_ = "InstructionLoadLocal";
}
int InstructionLoadLocal::execute(Core * c)
{
	Value v;
	v.loaded = node->var.back().var;
	c->values.push_back(v); //pridali sme value na stack
	return 0;
}
xmlNodePtr InstructionLoadLocal::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr child = xmlNewText( BAD_CAST node->name.c_str());
	xmlAddChild(n, child);
	return n;
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
int InstructionLoadGlobal::execute(Core * c)
{
	Value v;
	v.loaded = node->var[0].var;
	c->values.push_back(v);
	return 0;
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
	constant = true;
	var = new Variable("const",TypeInteger);
	var->IntegerValue = i;
	name_ = "InstructionLoad";
}
InstructionLoad::InstructionLoad(float f)
{
	constant = true;
	var = new Variable("const",TypeReal);
	var->RealValue = f;
	name_ = "InstructionLoad";
}
int InstructionLoad::execute(Core *c)
{
	if(constant)
	{
		Value v;
		v.loaded = var;
		c->values.push_back(v);
		return 0;
	}//else from stack
	Value range = c->values.back();
	c->values.pop_back();
	Value comp = c->values.back();
	c->values.pop_back();
	comp.loaded = comp.loaded->array->elements[range.loaded->IntegerValue];
	c->values.push_back(comp);
	return 0;
}
xmlNodePtr InstructionLoad::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr child;
        if (!constant)
		child= xmlNewText( BAD_CAST node->name.c_str());
	else
	{
		switch (var->type)
		{
			case TypeInteger:
				{
					child = xmlNewNode( NULL, BAD_CAST "TypeInteger");
					std::string s = deconvert<int>(var->IntegerValue);
					xmlNodePtr grand_child = xmlNewText(BAD_CAST s.c_str()); 
					xmlAddChild(child,grand_child);
					break;
				}
			case TypeReal:
				{
					child = xmlNewNode( NULL, BAD_CAST "TypeReal");
					std::string s = deconvert<double>(var->RealValue);
					xmlNodePtr grand_child = xmlNewText(BAD_CAST s.c_str()); 
					xmlAddChild(child,grand_child);
					break;
				}
			default:
				child = xmlNewText( BAD_CAST "TypeUndefined");
		}
	}
	xmlAddChild(n, child);
	return n;
}
InstructionStore::InstructionStore()
{
	name_ = "InstructionStore";
}
int InstructionStore::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	Value left = c->values.back();
	c->values.pop_back();
	//ak sa rovnaju, potom uloz
	switch(right.loaded->type)
	{
		case TypeInteger:
			{
				right.loaded->IntegerValue = left.loaded->IntegerValue;
				break;
			}
		case TypeReal:
			{
				right.loaded->RealValue = left.loaded->RealValue;
				break;
			}
		case TypeObject:
				right.loaded->ObjectValue = left.loaded->ObjectValue;
				break;
		default:
				return -1;
	}
	return 0;
}
Call::Call()
{
	name_ = "Call";
}
Call::Call(Function * f_)
{
	function = f_;
	name_ = "Call";
}
int Call::execute(Core * c)
{
	
	return 0;
}
xmlNodePtr Call::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr n2 = xmlNewNode(NULL, BAD_CAST function->name.c_str());
	xmlNewProp(n2, BAD_CAST "begins", BAD_CAST deconvert(function->begin).c_str());
	xmlAddChild(n,n2);
	return n;
}

InstructionPop::InstructionPop()
{
	name_ = "InstructionPop";
}
int InstructionPop::execute(Core *s)
{
	s->values.pop_back();
	return 0;
}
InstructionMustJump::InstructionMustJump(int steps)
{
	shift = steps -1;
	name_ = "InstructionMustJump";
}
int InstructionMustJump::execute(Core * c)
{
	c->PC+=shift;
	return 0;
}
xmlNodePtr InstructionMustJump::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr n2 = xmlNewNode(NULL, BAD_CAST "JumpCount");
	xmlNodePtr n3 = xmlNewText(BAD_CAST deconvert<size_t>(shift).c_str());
	xmlAddChild(n2,n3);
	xmlAddChild(n,n2);
	return n;
}
InstructionJump::InstructionJump(int yes_, int no_)
{
	no = no_;
	name_ = "InstructionJump";
}
int InstructionJump::execute(Core * c)
{
	Value v = c->values.back();
	c->values.pop_back();
	if (!v.loaded->IntegerValue)
		c->PC+=yes;
	else c->PC+=no;
	return 0;
}
xmlNodePtr InstructionJump::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNewChild(n,NULL,BAD_CAST "yes",BAD_CAST deconvert<int>(yes).c_str());
	xmlNewChild(n,NULL,BAD_CAST "no",BAD_CAST deconvert<int>(no).c_str());
	return n;
}
InstructionReturn::InstructionReturn()
{
	name_ = "InstructionReturn";
}
/*int InstructionReturn::execute(Core *c)
{
	
}*/
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
//--------------------------------------------------
InstructionSee::InstructionSee()
{
	name_ = "InstructionSee";
}
InstructionStep::InstructionStep()
{
	name_ = "InstructionStep";
}
InstructionWait::InstructionWait()
{
	name_ = "InstructionWait";
}
InstructionShoot::InstructionShoot()
{
	name_ = "InstructionShoot";
}
InstructionTurn::InstructionTurn()
{
	name_ = "InstructionTurn";
}
InstructionTurnR::InstructionTurnR()
{
	name_ = "InstructionTurnR";
}
InstructionTurnL::InstructionTurnL()
{
	name_ = "InstructionTurnL";
}
InstructionHit::InstructionHit()
{
	name_ = "InstructionHit";
}
InstructionIsPlayer::InstructionIsPlayer()
{
	name_ = "InstructionIsPlayer";
}
InstructionIsWall::InstructionIsWall()
{
	name_ = "InstructionIsWall";
}
InstructionIsMissille::InstructionIsMissille()
{
	name_ = "InstructionIsMissille";
}
InstructionLocate::InstructionLocate()
{
	name_ = "InstructionLocate";
}
InstructionIsMoving::InstructionIsMoving()
{
	name_ = "InstructionIsMoving";
}
