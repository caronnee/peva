#include "instructions.h"
#include <iostream>

//TODO premenovat floatfrom an real, aby to olo konzistentne
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
Node * Instruction::get_node()
{
	return node;
}
InstructionCreate::InstructionCreate(Node * n)
{
	node = n;
	name_ = "InstructionCreate";
}
int InstructionCreate::execute(Core * c)
{	
	std::cout << "Vytvaram premennu " << node->name << "...";
	Variable * v = c->memory.assign(*node->type_of_variable,node->ID, c->depth);
	node->var.push_back(v); //pridali sme pre akutialne zanorenie premenu
	std::cout << "OK" << std::endl;
	return 0;
}
xmlNodePtr InstructionCreate::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	std::cout << node->name << "--3t4---"<< std::endl;
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
	std::cout << "Loading local variable " << node->name << "...";
	Value v;
	v.loaded = node->var.back();
	c->values.push_back(v); //pridali sme value na stack
	std::cout << "OK" << std::endl;
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
	std::cout << " Loading global variable: " << node->name << "...";
	if (node->var.size() == 0) 
	{
		Variable * v;
		v = c->memory.assign(*node->type_of_variable, node->ID, 0);
		node->var.push_back(v);
	}	
	Value v;
	v.loaded = node->var[0];
	c->values.push_back(v);
	std::cout << "OK" << std::endl;
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
	constant = false;
	node = NULL;
	name_ = "InstructionLoad";
	var = NULL;
}
InstructionLoad::InstructionLoad(int i)
{
	constant = true;
	var = new Variable("const",TypeInteger);
	var->integerValue = i;
	name_ = "InstructionLoad";
}
InstructionLoad::InstructionLoad(float f)
{
	name_ = "InstructionLoad";
	constant = true;
	var = new Variable("const",TypeReal);
	var->realValue = f;
}
int InstructionLoad::execute(Core *c)
{
	if(constant)
	{
		std::cout << "Loading constant ...";
		Value v;
		v.loaded = var;
		c->values.push_back(v);
		std::cout << "OK" << std::endl;
		return 0;
	}//else from stack
	std::cout << "Loading array, element number:" << c->values.back().loaded->integerValue <<"..."; 
	Value range = c->values.back();
	c->values.pop_back();
	Value comp = c->values.back();
	c->values.pop_back();
	comp.loaded = comp.loaded->array.elements[range.loaded->integerValue];
	c->values.push_back(comp);
	std::cout << "OK" << std::endl;
	return 0;
}
xmlNodePtr InstructionLoad::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr child;
	if (var == NULL)
		return n;
	switch (var->type)
	{
		case TypeInteger:
			{
				child = xmlNewNode( NULL, BAD_CAST "TypeInteger");
				std::string s = deconvert<int>(var->integerValue);
				xmlNodePtr grand_child = xmlNewText(BAD_CAST s.c_str()); 
				xmlAddChild(child,grand_child);
				break;
			}
		case TypeReal:
			{
				child = xmlNewNode( NULL, BAD_CAST "TypeReal");
				std::string s = deconvert<double>(var->realValue);
				xmlNodePtr grand_child = xmlNewText(BAD_CAST s.c_str()); 
				xmlAddChild(child,grand_child);
				break;
			}
		default:
			child = xmlNewText( BAD_CAST "TypeUndefined");
	}

	xmlAddChild(n, child);
	return n;
}
InstructionConversionToInt::InstructionConversionToInt()
{
	name_ = "InstructionConversionToInt";
}
int InstructionConversionToInt::execute(Core * c)
{
	std::cout << "Converting" <<c->values.back().loaded->realValue;
	c->values.back().loaded->integerValue = (int)c->values.back().loaded->realValue;
	std::cout << "to integer" << c->values.back().loaded->integerValue << "...";
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionConversionToReal::InstructionConversionToReal()
{
	name_ = "InstructionConversionToReal";
}
int InstructionConversionToReal::execute(Core * c)
{
	std::cout << "Converting" <<c->values.back().loaded->integerValue;
	c->values.back().loaded->realValue = (float)c->values.back().loaded->integerValue;
	std::cout << "to real" << c->values.back().loaded->realValue << "...";
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionDuplicate::InstructionDuplicate()
{
	name_ = "InstructionDuplicate";
}
int InstructionDuplicate::execute(Core * c)
{
	std::cout << "Duplicating variable" << std::endl;
	c->values.push_back(c->values.back()); //TODO ocheckovat, ci ma z coho brat
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionStoreInteger::InstructionStoreInteger()
{
	name_ = "InstructionStoreInteger";
}
int InstructionStoreInteger::execute(Core * c)
{
	std::cout<<"Storing integer, value: " << c->values.back().loaded->integerValue;
	int right = c->getIntFromStack();
	c->values.back().loaded->integerValue = right;
	c->values.pop_back();
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionStoreReal::InstructionStoreReal()
{
	name_ = "InstructionStoreReal";
}
int InstructionStoreReal::execute(Core * c)
{
	std::cout<<"Storing real, value" <<c->values.back().loaded->realValue<< "..." ;
	float right = c->getFloatFromStack();
	c->values.back().loaded->realValue = right;
	c->values.pop_back();
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionStoreObject::InstructionStoreObject()
{
	name_ = "InstructionStoreObject";
}
int InstructionStoreObject::execute(Core * c)
{
	std::cout << "Storing object, address:" << c->values.back().loaded->objectValue <<"...";
	Object * right = c->getObjectFromStack();
	c->values.back().loaded->objectValue = right;
	std::cout << "OK" << std::endl;
	return 0;
}
Call::Call()
{
	node = NULL;
	function = NULL;
	name_ = "Call";
}
Call::Call(Function * f_)
{
	node = NULL;
	std::cout << "Creatinf instruction for calling function :" << f_ << std::endl;
	function = f_;
	name_ = "Call";
}
int Call::execute(Core * c)
{
	std::cout << "Calling function: " << function->name << std::endl;
	c->nested_functions.push_back(c->nested_function);
	c->nested_function = function;
	Variable *v;
	Node * ret = function->return_var;
	v = c->memory.assign(*ret->type_of_variable,ret->ID, c->depth ); //aby zmizlo po ukonceni
	ret->var.push_back(v);//skopiruje si zo stacku hodnoty svojich parametrov
	for( size_t i = 0; i< function->parameters.size(); i++)
	{
		Variable * v;
		//ak pridane ako refeencia, skopiruj pointre
		if (function->parameters[i].val_type == PARAMETER_BY_REFERENCE)
		{
			std::cout << "Storing parameter by reference" << std::endl;
			v = c->values.back().loaded; //mozem to tam spravit, lebo v gramatike sa to da pouzit len pramo s premennou
			//Musi byt premenna
			function->parameters[i].node->var.push_back(v);
		}
		else
		{
			std::cout << "Storing parameter by value" << std::endl;
			v = c->memory.assign(*function->parameters[i].node->type_of_variable,function->parameters[i].node->ID,c->depth + 1);
			function->parameters[i].node->var.push_back(v);
			Variable * vvv = c->values.back().loaded;
			v->copyValue(vvv);	
			c->values.pop_back();
		}
	}
	c->save(function->begin);	
	std::cout << "OK" << std::endl;
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
	std::cout << "Popping out variable from stack ...";
	s->values.pop_back();
	std::cout << "OK" << std::endl;
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
	std::cout << "Jumping " << shift << "steps...";
	c->PC+=shift;
	std::cout << "OK" << std::endl;
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
	std::cout << "Conditional Jump, ";
	Value v = c->values.back();
	c->values.pop_back();
	if (v.loaded->integerValue)
	{
		std::cout <<" condition fulfilled ...";
		c->PC+=yes;
	}
	else 
	{
		std::cout <<" condition not fulfilled ...";
		c->PC+=no;
	}
	std::cout << "OK" << std::endl;
	return 0;
}
xmlNodePtr InstructionJump::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNewChild(n,NULL,BAD_CAST "yes",BAD_CAST deconvert<int>(yes).c_str());
	xmlNewChild(n,NULL,BAD_CAST "no",BAD_CAST deconvert<int>(no).c_str());
	return n;
}
InstructionBreak::InstructionBreak(int label, int depth_)
{
	depth = depth_;
	loop_label = label;
	name_ = "InstructionBreak";
}
int InstructionBreak::execute(Core * c)
{
	std::cout << "Breaking loop, from depth" <<c->depth;
	c->PC+=jump;
	c->depth -= depth;
	std::cout << "to depth " << c->depth <<"...";
	c->memory.free(c->depth+1); //vycisti do vratane az do hlbky povodneho, loop_label je povodny, tam by to chcelo nechat
	std::cout << "OK" << std::endl;
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
	return loop_label;
}
void InstructionBreak::set(int a, int b, int c)
{
	jump = b-a-1;
	depth = c;
}
InstructionContinue::InstructionContinue(int label, int depth_)
{
	depth = depth_;
	loop_label = label;
	name_ = "InstructionContinue";
}
void InstructionContinue::set(int jump, int size, int dep)
{
	jump = -jump;
	depth = dep;
}
InstructionReturn::InstructionReturn(int depth_)
{
	std::cout << "hlbka: " << depth_ << std::endl;
	depth = depth_;
	name_ = "InstructionReturn";
}
int InstructionReturn::execute(Core * c)
{
	std::cout << "Return from depth" << c->depth;
	c->depth -= depth-1;
	std::cout << "to depth" << c->depth <<"..."<< std::endl;
	c->PC = c->nested_function->end -3; //za restore, end_block a ++ u PC
	Value v;
	v.loaded = c->nested_function->return_var->var.back();
	c->nested_function->return_var->var.pop_back();//zmazanie returnu po naloadovani do stacku
	c->values.push_back(v);
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionRestore::InstructionRestore()
{
	name_ = "InstructionRestore";
}
int InstructionRestore::execute(Core *c)
{
	std::cout << "Restorin' "; //zmaz prebentivne navratove hodnoty a para,etre
	c->restore();
	std::cout << "OK" << std::endl;
	return 0;
}

//--------------------------POCITANIE--------------------------------------------------

InstructionPlusPlusInteger::InstructionPlusPlusInteger()
{
	name_ = "InstructionPlusPlusInteger";
}
int InstructionPlusPlusInteger::execute(Core * c)
{
	std::cout << "Integer plusplus ...";
	c->values.back().loaded->integerValue++;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionPlusPlusReal::InstructionPlusPlusReal()
{
	name_ = "InstructionPlusPlusReal";
}
int InstructionPlusPlusReal::execute(Core * c)
{
	std::cout << "Real plusplus ...";
	c->values.back().loaded->realValue++;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionMinusMinusInteger::InstructionMinusMinusInteger()
{
	name_ = "InstructionMinusMinusInteger";
}
int InstructionMinusMinusInteger::execute(Core * c)
{
	std::cout << "Integer minusminus ...";
	c->values.back().loaded->integerValue--;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionMinusMinusReal::InstructionMinusMinusReal()
{
	name_ = "InstructionMinusMinusReal";
}
int InstructionMinusMinusReal::execute(Core * c)
{
	std::cout << "Real minusminus ...";
	c->values.back().loaded->realValue--;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionPlusInteger::InstructionPlusInteger()
{
	name_ = "InstructionPlusInteger";
	std::cout << name_ << std::endl;
}
int InstructionPlusInteger::execute(Core * c)
{
	std::cout << "Adding two integer numbers...";
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue + right;
	c->values.back().loaded = &c->values.back().hlp;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionPlusReal::InstructionPlusReal()
{
	name_ = "InstructionPlusReal";
	std::cout << name_ << std::endl;
}
int InstructionPlusReal::execute(Core * c)
{
	std::cout << "Adding two real numbers...";
	float right = c->getFloatFromStack();
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue + right;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().loaded->type = TypeReal;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionMinusInteger::InstructionMinusInteger()
{
	name_ = "InstructionMinusInteger";
}
int InstructionMinusInteger::execute(Core * c)
{
	std::cout << "Substraction two integer numbers ...";
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue - right;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().loaded->type = TypeInteger;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionMinusReal::InstructionMinusReal()
{
	name_ = "InstructionMinusReal";
}
int InstructionMinusReal::execute(Core * c)
{
	std::cout << "Substracting two real numbers ...";
	float right = c->getFloatFromStack();
	c->values.back().hlp.realValue = c->values.back().loaded->realValue - right;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().loaded->type = TypeReal;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionMultiplyInteger::InstructionMultiplyInteger()
{
	name_ = "InstructionMultiplyInteger";
}
int InstructionMultiplyInteger::execute(Core * c)
{
	std::cout << "Multiplying two integer numbers ...";
	float right = c->getFloatFromStack();
	c->values.back().hlp.realValue = c->values.back().loaded->realValue * right;
	c->values.back().loaded = &c->values.back().hlp;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionMultiplyReal::InstructionMultiplyReal()
{
	name_ = "InstructionMultiplyReal";
}
int InstructionMultiplyReal::execute(Core * c)
{
	std::cout << "Multiplying two real numbers ...";
	float right = c->getFloatFromStack();
	c->values.back().hlp.realValue = c->values.back().loaded->realValue * right;
	c->values.back().loaded = &c->values.back().hlp;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionDivideInteger::InstructionDivideInteger()
{
	name_ = "InstructionDivideInteger";
}
int InstructionDivideInteger::execute(Core * c)
{
	std::cout << "Dividing two integer numbers ..."; 
	int right = c->getIntFromStack();
	c->values.back().hlp.realValue = c->values.back().loaded->integerValue / right;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionDivideReal::InstructionDivideReal()
{
	name_ = "InstructionDivideReal";
}
int InstructionDivideReal::execute(Core * c)
{
	std::cout << "Dividing two real numbers ..."; 
	int right = c->getFloatFromStack();
	c->values.back().hlp.realValue = c->values.back().loaded->realValue / right;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionModulo::InstructionModulo()
{
	name_ = "InstructionModulo";
}
int InstructionModulo::execute(Core * c)
{
	std::cout << "Module ...";
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue % right;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionBinaryAnd::InstructionBinaryAnd()
{
	name_ = "InstructionBinaryAnd";
}
int InstructionBinaryAnd::execute(Core * c)
{
	std::cout << " & ...";
	std::cout << name_ << std::endl;
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue & right;
	c->values.back().loaded = & c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionAnd::InstructionAnd()
{
	name_ = "InstructionAnd";
}
int InstructionAnd::execute(Core *c)
{
	std::cout << " && ..."; 
	int right = c->getIntFromStack();
	Value left = c->values.back();
	if ((right == 0)
			|| (left.loaded->integerValue ==0)) 
		c->values.back().hlp.integerValue = 0;
	else
		c->values.back().hlp.integerValue = 1;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionBinaryOr::InstructionBinaryOr()
{
	name_ = "InstructionBinaryOr";
}
int InstructionBinaryOr::execute(Core * c)
{
	std::cout << " | ...";
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue | right;
	c->values.back().hlp.type = TypeInteger;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionOr::InstructionOr()
{
	name_ = "InstructionOr";
}
int InstructionOr::execute(Core *c) //TODO skratene vyhodnocovanie??
{
	std::cout << " || ";
	int right = c->getIntFromStack();
	Value left = c->values.back();
	if ((right != 0)
			|| (left.loaded->integerValue !=0)) 
		c->values.back().hlp.integerValue = 1;
	else
		c->values.back().hlp.integerValue = 0;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionBinaryNot::InstructionBinaryNot()
{
	name_ = "InstructionBinaryNot";
}
int InstructionBinaryNot::execute(Core *c)
{
	std::cout << " ~ ...";
	c->values.back().hlp.integerValue = ~c->values.back().loaded->integerValue;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionNot::InstructionNot()
{
	name_ = "InstructionNot";
}
int InstructionNot::execute(Core *c) //POZOR, pri unarnych operaciach sa neda pouzivat int!
{
	std::cout << " Not ...";
	if (c->values.back().loaded->integerValue == 0)
		c->values.back().hlp.integerValue = 1;
	else
		c->values.back().hlp.integerValue = 1;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	std::cout << "OK" << std::endl;
	return 0;
}
//----------------------------------------------------------------------------------------------------
InstructionGtInteger::InstructionGtInteger()
{
	name_ = "InstructionGtInteger";
}
int InstructionGtInteger::execute(Core * c)
{
	std::cout << "Integer > ...";
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue > right)? 0:1; 
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionGtReal::InstructionGtReal()
{
	name_ = "InstructionGtReal";
}
int InstructionGtReal::execute(Core * c)
{
	std::cout << "Real > ...";
	float right = c->getFloatFromStack();
	Value left = c->values.back();
	c->values.back().hlp.integerValue = (c->values.back().loaded->realValue > right)? 0:1; 
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionGeInteger::InstructionGeInteger()
{
	name_ = "InstructionGeInteger";
}
int InstructionGeInteger::execute(Core *c)
{
	std::cout<<"Integer >= ...";
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue >= right)? 0:1; 
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionGeReal::InstructionGeReal()
{
	name_ = "InstructionGeReal";
}
int InstructionGeReal::execute(Core * c)
{
	std::cout<<"Real >= ...";
	float right = c->getFloatFromStack();
	Value left = c->values.back();
	c->values.back().hlp.integerValue = (c->values.back().loaded->realValue >= right)? 0:1; 
	c->values.back().loaded = &c->values.back().hlp;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionEqualInteger::InstructionEqualInteger()
{
	name_ = "InstructionEqualInteger";
}
int InstructionEqualInteger::execute(Core * c) //pre location nech si napisu funkciu bujde o nastejno:)
{
	std::cout << " Integer == ...";
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue == right)? 1:0; 
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionEqualReal::InstructionEqualReal()
{
	name_ = "InstructionEqualReal";
}
int InstructionEqualReal::execute(Core *c)
{
	std::cout << "Real == ...";
	float right = c->getFloatFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->realValue == right)? 1:0; 
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionEqualObject::InstructionEqualObject()
{
	name_ = "InstructionEqualObject";
}
int InstructionEqualObject::execute(Core * c)
{
	std::cout << "Object == ...";
	Object * right = c->getObjectFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->objectValue == right)? 1:0;
	c->values.back().loaded = &c->values.back().hlp;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionNotEqualInteger::InstructionNotEqualInteger()
{
	name_ = "InstructionNotEqualInteger";
}
int InstructionNotEqualInteger::execute(Core * c)
{
	std::cout << "object != ...";
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue != right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionNotEqualReal::InstructionNotEqualReal()
{
	name_ = "InstructionNotEqualReal";
}
int InstructionNotEqualReal::execute(Core * c)
{
	std::cout << "Real != ...";
	int right = c->getFloatFromStack();
	c->values.back().hlp.realValue = (c->values.back().loaded->realValue != right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionNotEqualObject::InstructionNotEqualObject()
{
	name_ = "InstructionNotEqualObject";
}
int InstructionNotEqualObject::execute(Core * c)
{
	std::cout << "Object != ...";
	Object * right = c->getObjectFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->objectValue != right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionLtInteger::InstructionLtInteger()
{
	name_ = "InstructionLtInteger";
}
int InstructionLtInteger::execute(Core * c)
{
	std::cout << "Integer < ...";
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue < right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionLtReal::InstructionLtReal()
{
	name_ = "InstructionLtReal";
}
int InstructionLtReal::execute(Core * c)
{
	std::cout << "Real < ...";
	float right = c->getFloatFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->realValue < right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionLeInteger::InstructionLeInteger()
{
	name_ = "InstructionLeInteger";
}
int InstructionLeInteger::execute(Core * c)
{
	std::cout << "Integer <= ...";
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue <= right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionLeReal::InstructionLeReal()
{
	name_ = "InstructionLeReal";
}
int InstructionLeReal::execute(Core * c)
{
	std::cout << "Real <=";
	float right = c->getFloatFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->realValue <= right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionBegin::InstructionBegin()
{
	name_ = "InstructionBegin";
}
int InstructionBegin::execute(Core * c)
{
	std::cout << name_ << "Increasing depth to:" << c->depth +1<< "...";
	c->depth++;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionEndBlock::InstructionEndBlock()
{
	name_ = "InstructionEndBlock";
}
int InstructionEndBlock::execute(Core * c)
{
	std::cout <<"Ending depth"<< c->depth <<"...";
	c->memory.free(c->depth);
	c->depth--;
	std::cout << "OK" << std::endl;
	return 0;
}
//--------------------------------------------------
InstructionSee::InstructionSee(Node * n) //uzol ktory sa ma naplnit viditelnymi objektami
{
	node = n;
	name_ = "InstructionSee";
}
int InstructionSee::execute(Core *c) //	ziadne dlasie parametre
{
	std::cout << "Filling objects in robot's see angle ...";
	Value v;
	c->values.push_back(v);
	c->values.back().loaded = &c->values.back().hlp;
//TODO napln variable	
	c->values.back().loaded->integerValue = c->robot->See(); //TODO, kam to naplni
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionStep::InstructionStep()
{
	name_ = "InstructionStep";
}
int InstructionStep::execute(Core *c)
{
	std::cout << "Stepping ...";
	Value v;
	c->values.push_back(v);
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().loaded->integerValue = c->robot->Step(c->getIntFromStack());
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionWait::InstructionWait()
{
	name_ = "InstructionWait";
}
int InstructionWait::execute(Core *c)
{
	std::cout << "Waiting ...";
	Value v;
	c->values.push_back(v);
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().loaded->integerValue = c->robot->Wait(c->getIntFromStack());
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionShootLocation::InstructionShootLocation()
{
	name_ = "InstructionShootLocation";
}
int InstructionShootLocation::execute(Core *c)
{
	std::cout << "Shooting at location...";
	Value v;
	int x = c->getIntFromStack();
	int y = c->getIntFromStack();
	c->values.push_back(v);
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().loaded->integerValue = c->robot->Shoot(x,y); //TODO vypocitat angle, smer x a smer y
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionShootAngle::InstructionShootAngle()
{
	name_ = "InstructionShootAngle";
}
int InstructionShootAngle::execute(Core *c)
{
	std::cout << "Shooting at angle...";
	int an = c->getIntFromStack();
	Value v;
	c->values.push_back(v);
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().loaded->integerValue = c->robot->Shoot(an,an); //TODO angle
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionTurn::InstructionTurn()
{
	name_ = "InstructionTurn";
}
int InstructionTurn::execute(Core *s)
{
	std::cout << "Turning ...";
	int par = s->getIntFromStack();
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->Turn(par);
	s->values.push_back(v);
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionTurnR::InstructionTurnR()
{
	name_ = "InstructionTurnR";
}
int InstructionTurnR::execute(Core *s)
{
	std::cout << "Tirning right ...";
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->TurnR();
	v.loaded->type = TypeInteger;
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionTurnL::InstructionTurnL()
{
	name_ = "InstructionTurnL";
}
int InstructionTurnL::execute(Core *s)
{
	std::cout << "Turning left ...";
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->TurnL();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionHit::InstructionHit()
{
	name_ = "InstructionHit";
}
int InstructionHit::execute(Core *s)
{
	std::cout << "Checking hit state of object ...";
	Object * o = s->values.back().loaded->objectValue;
	s->values.back().loaded = &s->values.back().hlp;
	s->values.back().loaded->integerValue = o->Hit();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionIsPlayer::InstructionIsPlayer()
{
	name_ = "InstructionIsPlayer";
}
int InstructionIsPlayer::execute(Core *s)
{
	std::cout << "Checking playerism ...";
	Object * o = s->values.back().loaded->objectValue;
	s->values.back().loaded = &s->values.back().hlp;
	s->values.back().loaded->integerValue = o->IsPlayer();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionIsWall::InstructionIsWall()
{
	name_ = "InstructionIsWall";
}
int InstructionIsWall::execute(Core *s)
{
	std::cout << "Checking wallism ...";
	Object * o = s->values.back().loaded->objectValue;
	s->values.back().loaded = &s->values.back().hlp;
	s->values.back().loaded->integerValue = o->IsWall();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionIsMissille::InstructionIsMissille()
{
	name_ = "InstructionIsMissille";
}
int InstructionIsMissille::execute(Core *s)
{
	std::cout <<"Checking missilism ..."; //s jednym parametrom
	Object * o = s->values.back().loaded->objectValue;
	s->values.back().loaded = &s->values.back().hlp;
	s->values.back().loaded->integerValue = o->IsMissille();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionLocate::InstructionLocate()
{
	name_ = "InstructionLocate";
}
int InstructionLocate::execute(Core *s) //TODO location
{
	std::cout << "Getting location of object ...";
	Value v;
	v.loaded = &v.hlp;
//	v.loaded->Array = s->robot->Locate();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionIsMoving::InstructionIsMoving()
{
	name_ = "InstructionIsMoving";
}
int InstructionIsMoving::execute(Core *s)
{
	std::cout << "Checking movement ...";
	Object * o = s->values.back().loaded->objectValue;
	s->values.back().loaded = &s->values.back().hlp;
	s->values.back().loaded->integerValue = o->IsMoving();
	std::cout << "OK" <<std::endl;
	return 0;
}
