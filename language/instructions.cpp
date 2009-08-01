#include "instructions.h"

Instruction::Instruction()
{
	name_ = "UndefinedInstruction";
}
std::string Instruction::name()
{
	return name_;
}
int Instruction::breaks()
{
	return -1;
}
xmlNodePtr Instruction::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	return n;	
}
int Instruction::execute(Core * s)
{
	s->error = true;
	return 1;
}
InstructionCreate::InstructionCreate(Node * n)
{
	node = n;
	name_ = "InstructionCreate";
}
int InstructionCreate::execute(Core * c)
{
	Variable * v = c->memory.assign(node->type_of_variable,node->ID, c->depth);
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
	function = NULL;
	name_ = "Call";
}
Call::Call(Function * f_)
{
	function = f_;
	name_ = "Call";
}

int Call::execute(Core * c)
{
	//zoberie [pocet premennych aktualne na stacku], ulozi do svojich, v pripade varu ulozi svoje premenne(copy, pozor na pole a na recordy)
	for(size_t i = 0; i< function->parameters.size(); i++)
	{
		if (function->parameters[i].val_type == PARAMETER_BY_REFERENCE)
		{
			Var v;
			v.var = c->values.back().loaded;
			function->parameters[i].node->var.push_back(v);
			c->values.pop_back();
		}
		else
		{
			Var v;
			v.var = c->memory.assign(function->parameters[i].node->type_of_variable,function->parameters[i].node->ID,c->depth);
			function->parameters[i].node->var.push_back(v);
		}
	}
	c->save(function->begin);	
	return 0;
}
xmlNodePtr Call::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr n2 = xmlNewText(BAD_CAST function->name.c_str());
	xmlNewProp(n, BAD_CAST "begins", BAD_CAST deconvert(function->begin).c_str());
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
	shift = steps;
//	std::cout << "Must step: " << shift << std::endl;
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
	xmlNodePtr n3 = xmlNewText(BAD_CAST deconvert<int>(shift).c_str());
	xmlAddChild(n2,n3);
	xmlAddChild(n,n2);
	return n;
}
InstructionJump::InstructionJump(int yes_, int no_)
{
	yes = yes_;
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
	loop_label = 1;
	jump = 123;
	name_ = "InstructionReturn";
}
InstructionRestore::InstructionRestore()
{
	name_ = "InstructionRestore";
}
int InstructionRestore::execute(Core *c)
{
	c->restore();
	return 0;
}

InstructionBreak::InstructionBreak(int label)
{
//	std::cout << label << "-----" << std::endl;
	loop_label = label;
	name_ = "InstructionBreak";
}
int InstructionBreak::execute(Core * c)
{
	c->PC+=jump;
	c->memory.free(loop_label); //vycisti do vratane hlbky s
	return 0;
}
xmlNodePtr InstructionBreak::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNewChild(n,NULL, BAD_CAST "Jump", BAD_CAST deconvert<int>(jump).c_str());
	return n;
}
int InstructionBreak::breaks()
{
//	std::cout << loop_label << ": loop_label in break" << std::endl;
//	getc(stdin);
	return loop_label;
}
InstructionPlusPlus::InstructionPlusPlus()
{
	name_ = "InstructionPlusPlus";
}
int InstructionPlusPlus::execute(Core * c)
{
	c->values.back().hlp.IntegerValue = c->values.back().loaded->IntegerValue++;
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionMinusMinus::InstructionMinusMinus()
{
	name_ = "InstructionMinusMinus";
}
int InstructionMinusMinus::execute(Core * c)
{
	c->values.back().hlp.IntegerValue = c->values.back().loaded->IntegerValue--;
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionPlus::InstructionPlus()
{
	name_ = "InstructionPlus";
}
int InstructionPlus::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	c->values.back().hlp.IntegerValue = c->values.back().loaded->IntegerValue + right.loaded->IntegerValue;
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionMinus::InstructionMinus()
{
	name_ = "InstructionMinus";
}
int InstructionMinus::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	c->values.back().hlp.IntegerValue = c->values.back().loaded->IntegerValue - right.loaded->IntegerValue;
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionMultiply::InstructionMultiply()
{
	name_ = "InstructionMultiply";
}
int InstructionMultiply::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	c->values.back().hlp.IntegerValue = c->values.back().loaded->IntegerValue * right.loaded->IntegerValue;
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionDivide::InstructionDivide()
{
	name_ = "InstructionDivide";
}
int InstructionDivide::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	if ((right.loaded->type != TypeInteger) && (right.loaded->type!=TypeReal))
		return -1; //TODO do bisona	
	if ((c->values.back().loaded->type != TypeInteger) && (c->values.back().loaded->type!=TypeReal))
		return -1; //TODO do bisona	
	if (right.loaded->type == TypeInteger) //zatial nepredpokladame konverziu
	{
		c->values.back().hlp.IntegerValue = c->values.back().loaded->IntegerValue / right.loaded->IntegerValue;
		c->values.back().hlp.type = TypeInteger;
	}
	else
	{
		c->values.back().hlp.RealValue = c->values.back().loaded->RealValue / right.loaded->RealValue;
		c->values.back().hlp.type = TypeReal;
	}
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}

InstructionModulo::InstructionModulo()
{
	name_ = "InstructionModulo";
}
int InstructionModulo::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	c->values.back().hlp.IntegerValue = c->values.back().loaded->IntegerValue % right.loaded->IntegerValue;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionBinaryAnd::InstructionBinaryAnd()
{
	name_ = "InstructionBinaryAnd";
}
int InstructionBinaryAnd::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	c->values.back().hlp.IntegerValue = 
		c->values.back().loaded->IntegerValue & right.loaded->IntegerValue;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionAnd::InstructionAnd()
{
	name_ = "InstructionAnd";
}
int InstructionAnd::execute(Core *c)
{
	Value right = c->values.back();
	c->values.pop_back();
	Value left = c->values.back();
	if ((right.loaded->IntegerValue == 0)
		|| (left.loaded->IntegerValue ==0)) 
		c->values.back().hlp.IntegerValue = 0;
	else
		c->values.back().hlp.IntegerValue = 1;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionBinaryOr::InstructionBinaryOr()
{
	name_ = "InstructionBinaryOr";
}
int InstructionBinaryOr::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	c->values.back().hlp.IntegerValue = 
		c->values.back().loaded->IntegerValue | right.loaded->IntegerValue;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionOr::InstructionOr()
{
	name_ = "InstructionOr";
}
int InstructionOr::execute(Core *c)
{
	Value right = c->values.back();
	c->values.pop_back();
	Value left = c->values.back();
	if ((right.loaded->IntegerValue != 0)
		|| (left.loaded->IntegerValue !=0)) 
		c->values.back().hlp.IntegerValue = 1;
	else
		c->values.back().hlp.IntegerValue = 0;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionBinaryNot::InstructionBinaryNot()
{
	name_ = "InstructionBinaryNot";
}
int InstructionBinaryNot::execute(Core *c)
{
	c->values.back().hlp.IntegerValue = ~c->values.back().loaded->IntegerValue;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionNot::InstructionNot()
{
	name_ = "InstructionNot";
}
int InstructionNot::execute(Core *c)
{
	if (c->values.back().loaded->IntegerValue == 0)
		c->values.back().hlp.IntegerValue = 1;
	else 
		c->values.back().hlp.IntegerValue = 1;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
//----------------------------------------------------------------------------------------------------
InstructionGt::InstructionGt()
{
	name_ = "InstructionGt";
}
int InstructionGt::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	Value left = c->values.back();
	switch (left.loaded->type)
	{
		case TypeInteger:
			c->values.back().hlp.IntegerValue = (left.loaded->IntegerValue > right.loaded->IntegerValue)? 0:1; 
			break;
		case TypeReal:
			c->values.back().hlp.IntegerValue = (left.loaded->RealValue > right.loaded->RealValue)? 0:1; 
			break;
		default:
			return -1; //zvysok nepozna
	}
	c->values.back().loaded = &c->values.back().hlp;
	c->values.push_back(right);
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionGe::InstructionGe()
{
	name_ = "InstructionGe";
}
int InstructionGe::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	Value left = c->values.back();
	switch (left.loaded->type)
	{
		case TypeInteger:
			c->values.back().hlp.IntegerValue = (left.loaded->IntegerValue >= right.loaded->IntegerValue)? 0:1; 
			break;
		case TypeReal:
			c->values.back().hlp.IntegerValue = (left.loaded->RealValue >= right.loaded->RealValue)? 0:1; 
			break;
		default:
			return -1; //zvysok nepozna
	}
	c->values.back().loaded = &c->values.back().hlp;
	c->values.push_back(right);
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionEqual::InstructionEqual()
{
	name_ = "InstructionEqual";
}
int InstructionEqual::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	Value left = c->values.back();
	switch (left.loaded->type)
	{
		case TypeInteger:
			c->values.back().hlp.IntegerValue = (left.loaded->IntegerValue == right.loaded->IntegerValue)? 1:0; 
			break;
		case TypeReal:
			c->values.back().hlp.IntegerValue = (left.loaded->RealValue == right.loaded->RealValue)? 1:0; 
			break;
		case TypeLocation:
			if ((left.loaded->array->elements[0]->IntegerValue == right.loaded->array->elements[0]->IntegerValue) 
				&&(left.loaded->array->elements[1]->IntegerValue == right.loaded->array->elements[1]->IntegerValue))
				c->values.back().hlp.IntegerValue = 1;
			else 
				c->values.back().hlp.IntegerValue = 0;
			break;
		case TypeObject:
			c->values.back().hlp.IntegerValue = (left.loaded->ObjectValue == right.loaded->ObjectValue)? 1:0;
			break;
		case TypeArray:
			c->values.back().hlp.IntegerValue = (left.loaded == right.loaded)? 1:0;
			break;

/*		case TypeArray:
			bool equal = true;
			std::stack<Variable *> lefts, rights;
			rights.push(right.loaded);
			lefts.push(left.loaded);
			while (!lefts.empty())
			{
				Variable * left_v = lefts.top();
				lefts.pop();
				Variable * right_v = rights.top();
				rights.pop();
				if((left_v->type!=right_v->type)
				 ||(left_v->array->elements.size()!= right_v->array->elements.size()))
				{
					equal = false;
					break;
				}
				for(size_t i = 0; i< left_v->array->elements.size(); i++)
				{
					lefts.push(left_v->array->elements[i]);
					rights.push(right_v->array->elements[i])
				}

			}
			break;*///array sa porovnavat nebude,moc miesta a ets aj penalizacia by bola divna
		default:
			return -1; //zvysok nepozna
	}
	c->values.back().loaded = &c->values.back().hlp;
	c->values.push_back(right);
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionLt::InstructionLt()
{
	name_ = "InstructionLt";
}
int InstructionLt::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	Value left = c->values.back();
	switch (left.loaded->type)
	{
		case TypeInteger:
			c->values.back().hlp.IntegerValue = (left.loaded->IntegerValue < right.loaded->IntegerValue)? 0:1; 
			break;
		case TypeReal:
			c->values.back().hlp.IntegerValue = (left.loaded->RealValue < right.loaded->RealValue)? 0:1; 
			break;
		default:
			return -1; //zvysok nepozna
	}
	c->values.back().loaded = &c->values.back().hlp;
	c->values.push_back(right);
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionLe::InstructionLe()
{
	name_ = "InstructionLe";
}
int InstructionLe::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	Value left = c->values.back();
	switch (left.loaded->type)
	{
		case TypeInteger:
			c->values.back().hlp.IntegerValue = (left.loaded->IntegerValue <= right.loaded->IntegerValue)? 0:1; 
			break;
		case TypeReal:
			c->values.back().hlp.IntegerValue = (left.loaded->RealValue <= right.loaded->RealValue)? 0:1; 
		default:
			return -1; //zvysok nepozna
	}
	c->values.back().loaded = &c->values.back().hlp;
	c->values.push_back(right);
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionNotEqual::InstructionNotEqual()
{
	name_ = "InstructionNotEqual";
}
int InstructionNotEqual::execute(Core * c)
{
	Value right = c->values.back();
	c->values.pop_back();
	Value left = c->values.back();
	switch (left.loaded->type)
	{
		case TypeInteger:
			c->values.back().hlp.IntegerValue = (left.loaded->IntegerValue != right.loaded->IntegerValue)? 1:0; 
			break;
		case TypeReal:
			c->values.back().hlp.IntegerValue = (left.loaded->RealValue != right.loaded->RealValue)? 1:0; 
			break;
		case TypeLocation:
			if ((left.loaded->array->elements[0]->IntegerValue != right.loaded->array->elements[0]->IntegerValue) 
				&&(left.loaded->array->elements[1]->IntegerValue != right.loaded->array->elements[1]->IntegerValue))
				c->values.back().hlp.IntegerValue = 1;
			else 
				c->values.back().hlp.IntegerValue = 0;
			break;
		case TypeObject:
			c->values.back().hlp.IntegerValue = (left.loaded->ObjectValue != right.loaded->ObjectValue)? 1:0;
			break;
		case TypeArray:
			c->values.back().hlp.IntegerValue = (left.loaded != right.loaded)? 1:0;
			break;
		default:
			return -1;
	}
	c->values.back().loaded = &c->values.back().hlp;
	c->values.push_back(right);
	c->values.back().hlp.type = TypeInteger;

	return 0;
}
InstructionBegin::InstructionBegin()
{
	name_ = "InstructionBegin";
}
int InstructionBegin::execute(Core * c)
{
	c->depth++;
	return 0;
}
InstructionEndBlock::InstructionEndBlock()
{
	name_ = "InstructionEndBlock";
}
int InstructionEndBlock::execute(Core * c)
{
	c->memory.free(c->depth);
	c->depth--;
	return 0;
}
//--------------------------------------------------
InstructionSee::InstructionSee()
{
	name_ = "InstructionSee";
}
int InstructionSee::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->See();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionStep::InstructionStep()
{
	name_ = "InstructionStep";
}
int InstructionStep::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->Step();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionWait::InstructionWait()
{
	name_ = "InstructionWait";
}
int InstructionWait::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->Wait();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionShoot::InstructionShoot()
{
	name_ = "InstructionShoot";
}
int InstructionShoot::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->Shoot();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionTurn::InstructionTurn()
{
	name_ = "InstructionTurn";
}
int InstructionTurn::execute(Core *s)
{
	Value par = s->values.back();
	s->values.pop_back();
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->Turn(par.loaded->IntegerValue);
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionTurnR::InstructionTurnR()
{
	name_ = "InstructionTurnR";
}
int InstructionTurnR::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->TurnR();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionTurnL::InstructionTurnL()
{
	name_ = "InstructionTurnL";
}
int InstructionTurnL::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->TurnL();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionHit::InstructionHit()
{
	name_ = "InstructionHit";
}
int InstructionHit::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->Hit();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionIsPlayer::InstructionIsPlayer()
{
	name_ = "InstructionIsPlayer";
}
int InstructionIsPlayer::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->IsPlayer();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionIsWall::InstructionIsWall()
{
	name_ = "InstructionIsWall";
}
int InstructionIsWall::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->IsWall();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionIsMissille::InstructionIsMissille()
{
	name_ = "InstructionIsMissille";
}
int InstructionIsMissille::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->IsMissille();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionLocate::InstructionLocate()
{
	name_ = "InstructionLocate";
}
int InstructionLocate::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->Locate();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionIsMoving::InstructionIsMoving()
{
	name_ = "InstructionIsMoving";
}
int InstructionIsMoving::execute(Core *s)
{
	Value v;
	v.loaded = &v.hlp;
	v.loaded->IntegerValue = s->robot->IsMoving();
	v.loaded->type = TypeInteger;
	return 0;
}