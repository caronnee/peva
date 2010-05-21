//TODO namiesto removetemp = operacia +remove temp, aby to bolo atomicke
//TODO return value by sa mala vytvorit az v okamziku RETURN u
#include <iostream>
#include <cmath>
#include "../h/instructions.h"
#include "../../add-ons/h/macros.h"

#define CRITICAL_AMOUNT_OF_FUNCTIONS 100

//FIXME premenovat floatfrom an real, aby to olo konzistentne

Instruction::Instruction()
{
	node = NULL;
	name_ = "UndefinedInstruction";
	group = IGroup_undefined;
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
Instruction::~Instruction()
{
	if (node !=NULL)
	{
		delete node;
		node = NULL;
	}
}

InstructionCreate::InstructionCreate(Node * n)
{
	node = n;
	name_ = "Instruction Create";
	group = IGroup_create;
}

int InstructionCreate::execute(Core * c)
{	
	TEST("Creating variable '" << node->name << "'...")
	Create_type * t = node->type_of_variable;
	while (t->data_type!=NULL)
	{
		t = t->data_type;
	}	
	TEST(" in depth" << c->depth)
	c->memory.assign( node, c->depth);
	TEST("result:" << node->var.size()<< " " <<node<< " ")
	TEST("OK")
	return 0;
}
xmlNodePtr InstructionCreate::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr child = xmlNewText( BAD_CAST node->name.c_str());
	xmlAddChild(n, child);
	return n;
}

InstructionCreate::~InstructionCreate()
{
	node = NULL; //node from talbe, destructed at table
}

InstructionLoadLocal::InstructionLoadLocal()
{
	node = NULL;
	name_ = "Instruction LoadLocal";
	group = IGroup_load;
}
InstructionLoadLocal::InstructionLoadLocal(Node * n)
{
	node = n;
	name_ = "Instruction LoadLocal";
	group = IGroup_load;
}
int InstructionLoadLocal::execute(Core * c)
{
	TEST("Loading local variable " << node->name)
	if (node->var.size() == 0)
		throw "Trying to load mpty variable";
	c->values.push_back(node->var.back());
	TEST("OK")
	return 0;
}
xmlNodePtr InstructionLoadLocal::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr child = xmlNewText( BAD_CAST node->name.c_str());
	xmlAddChild(n, child);
	return n;
}

InstructionLoadLocal::~InstructionLoadLocal()
{
	node = NULL;
}

InstructionLoadGlobal::InstructionLoadGlobal()
{
	node = NULL;
	name_ = "Instruction LoadGlobal";
	group = IGroup_load;	
}
InstructionLoadGlobal::InstructionLoadGlobal(Node * n)
{
	node = n;
	name_ = "Instruction LoadGlobal";
	group = IGroup_load;
}
int InstructionLoadGlobal::execute(Core * c) //FIXME kedyto potrebujem? nikdy tam nedam viac ako jednu premennu, pretoze sa nezanorujem,osetrene  bisone
{
	TEST(" Loading global variable: " << node->name << "...")
	TEST(" id =  " << node->var.size() << "...")
	Variable * v;
	v = node->var.back();
	c->values.push_back(v);
	TEST("OK")
	return 0;
}
xmlNodePtr InstructionLoadGlobal::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr child = xmlNewText( BAD_CAST node->name.c_str());
	xmlAddChild(n, child);
	return n;
}

InstructionLoadGlobal::~InstructionLoadGlobal()
{
	node = NULL;
}

InstructionLoad::InstructionLoad()
{
	constant = false;
	name_ = "Instruction Load";
	var = NULL;
	group = IGroup_load;
}
InstructionLoad::InstructionLoad(int i)
{
	constant = true;
	var = new Variable("const");
	type = TypeInteger;
	var->integerValue = i;
	name_ = "Instruction Load";
	group = IGroup_load;
}
InstructionLoad::InstructionLoad(float f)
{
	name_ = "Instruction Load";
	group = IGroup_load;
	constant = true;
	type = TypeReal;
	var = new Variable("const");
	var->realValue = f;
}
int InstructionLoad::execute(Core *c)
{
	if(constant)
	{
		TEST("Loading constant ..." << var->integerValue)
		c->values.push_back(var);
		TEST("OK")
		return 0;
	}//else from stack
	TEST("Loading array, element number:" << c->values.back()->integerValue <<"...")
	int range = c->getIntFromStack();
	c->loadElement(range);
	TEST("OK")
	return 0;
}
xmlNodePtr InstructionLoad::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNodePtr child;
	if (var == NULL)
		return n;
	switch (type)
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

InstructionLoad::~InstructionLoad()
{
	if(var)
		delete var;
	var = NULL;
	node = NULL; //node tu vlastne ani nepotrebujem
}
InstructionConversionToInt::InstructionConversionToInt()
{
	name_ = "Instruction ConversionToInt";
	group = IGroup_conversion;
}
int InstructionConversionToInt::execute(Core * c)
{
	TEST("Converting " << c->values.back()->realValue)
	float f=c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (int)f;
	TEST(" to integer" << c->values.back()->integerValue << "...")
	TEST("OK")
	return 0;
}

InstructionConversionToInt::~InstructionConversionToInt()
{
	/* nothing to be done yet, node is already null*/
}

InstructionConversionToReal::InstructionConversionToReal()
{
	name_ = "Instruction ConversionToReal";
	group = IGroup_conversion;
}

int InstructionConversionToReal::execute(Core * c)
{
	TEST("Converting" <<c->values.back()->integerValue)
	float f = (float)c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->realValue = f;
	TEST("to real" << c->values.back()->realValue << "...")
	TEST("OK")
	return 0;
}

InstructionConversionToReal::~InstructionConversionToReal()
{
	/* nothing to be done yet */
}

InstructionDuplicate::InstructionDuplicate()
{
	name_ = "Instruction Duplicate";
	group = IGroup_duplicate;
}

int InstructionDuplicate::execute(Core * c)
{
	TEST("Duplicating variable")
	c->values.push_back(c->values.back());
	TEST("OK")
	return 0;
}

InstructionDuplicate::~InstructionDuplicate()
{
	/* Nothing to be done yet*/
}

InstructionStoreRef::InstructionStoreRef(Node * n)
{
	node = n;
	name_ = "Instruction StoreReference";
	group = IGroup_store;
}
int InstructionStoreRef::execute(Core * c)
{
	Variable * var = c->getVariableFromStack();
	node->var.push_back(var);
	return 0;
}
InstructionStoreRef::~InstructionStoreRef() { }

InstructionStoreInteger::InstructionStoreInteger()
{
	name_ = "Instruction StoreInteger";
	group = IGroup_store;
}

int InstructionStoreInteger::execute(Core * c)
{
	TEST("Storing integer, value: " << c->values.back()->integerValue)
	c->saveInteger();
	TEST("OK")
	return 0;
}
	
InstructionStoreInteger::~InstructionStoreInteger()
{
	/* Nothing to be done yet*/
}

InstructionStoreReal::InstructionStoreReal()
{
	name_ = "Instruction StoreReal";
	group = IGroup_store;
}
int InstructionStoreReal::execute(Core * c)
{
	TEST("Storing real, value" <<c->values.back()->realValue<< "...")
	c->saveFloat();
	TEST("OK")
	return 0;
}
InstructionStoreReal::~InstructionStoreReal()
{
	/* Nothing to be done yet*/
}

InstructionStoreObject::InstructionStoreObject()
{
	name_ = "Instruction StoreObject";
	group = IGroup_store;
}
int InstructionStoreObject::execute(Core * c)
{
	TEST("Storing object, address:" << c->values.back()->objectValue <<"...")
	c->saveObject();
	TEST("OK")
	return 0;
}
InstructionStoreObject::~InstructionStoreObject()
{
	/* Nothing to be done yet */
}

Call::Call()
{
	node = NULL;
	function = NULL;
	name_ = "Call";
	group = IGroup_call;
}
Call::Call(Function * f_)
{
	node = NULL;
	function = f_;
	name_ = "Call";
	group = IGroup_call;
}
int Call::execute(Core * c) //TODO zmenit kopirovanie parametrov
{
	TEST("Calling function: ") 
	Node * ret = function->return_var;
	Variable * v = c->memory.assign_temp(ret->type_of_variable); //aby zmizlo po ukonceni
	
	if (c->nested_functions.size() == CRITICAL_AMOUNT_OF_FUNCTIONS)
	{
		c->values.push_back(v);
		return -1;
	}
	c->nested_functions.push_back(c->nested_function);
	c->nested_function = function;

	ret->var.push_back(v);//skopiruje si zo stacku hodnoty svojich parametrov

	c->save(function->begin);	
	TEST("OK")
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
Call::~Call()
{
	/* Nothing to be done yet */
}
InstructionPop::InstructionPop()
{
	name_ = "Instruction Pop";
	group = IGroup_pop;
}
int InstructionPop::execute(Core *s)
{
	TEST("Popping out variable from stack ...")
	s->values.pop_back();
	TEST("OK")
	return 0;
}
InstructionPop::~InstructionPop()
{
	/* Nothing to be done yet */
}
InstructionMustJump::InstructionMustJump(int steps)
{
	shift = steps;
	name_ = "Instruction MustJump";
	group = IGroup_jump;
}
int InstructionMustJump::execute(Core * c)
{
	TEST("Jumping " << shift << "steps...")
	c->PC+=shift;
	TEST("OK")
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
InstructionMustJump :: ~InstructionMustJump()
{
	/* nothing to be done yet */
}
InstructionJump::InstructionJump(int yes_, int no_)
{
	yes = yes_;
	no = no_;
	name_ = "Instruction Jump";
	group = IGroup_jump;
}
int InstructionJump::execute(Core * c)
{
	TEST("Conditional Jump, ")
	Variable * v = c->values.back();
	c->values.pop_back();
	if (v->integerValue)
	{
		TEST(" condition fulfilled ...")
		c->PC+=yes;
	}
	else 
	{
		TEST(" condition not fulfilled ...")
		c->PC+=no;
	}
	TEST("OK")
	return 0;
}
xmlNodePtr InstructionJump::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNewChild(n,NULL,BAD_CAST "yes",BAD_CAST deconvert<int>(yes).c_str());
	xmlNewChild(n,NULL,BAD_CAST "no",BAD_CAST deconvert<int>(no).c_str());
	return n;
}
InstructionJump::~InstructionJump()
{
	/* nothing to be done yet */
}
InstructionBreak::InstructionBreak(int depth_)
{
	depth = depth_;
	name_ = "Instruction Break";
	group = IGroup_break;
}
int InstructionBreak::execute(Core * c)
{
	TEST("Breaking loop, from depth" <<c->depth)
	TEST("jumping to instruction number: " << jump)
	c->PC=jump;
	c->depth -= depth;
	TEST("to depth " << c->depth <<"...")
//	c->memory.free(c->depth+1); //vycisti do vratane az do hlbky povodneho, loop_label je povodny, tam by to chcelo nechat
	TEST("OK")
	return 0;
}
xmlNodePtr InstructionBreak::xml_format()
{
	xmlNodePtr n = xmlNewNode(NULL, BAD_CAST name_.c_str());
	xmlNewChild(n,NULL, BAD_CAST "Jump", BAD_CAST deconvert<int>(jump).c_str());
	return n;
}
void InstructionBreak::set(size_t jump_ , size_t depth_)
{
	jump = jump_;
	depth -= depth_;
}
InstructionBreak::~InstructionBreak()
{
	/* nothing to be done yet */
}
InstructionContinue::InstructionContinue(int depth_)
{
	depth = depth_-1; //TODO v bisone
	name_ = "Instruction Continue";
	group = IGroup_continue;
}
int InstructionContinue::execute(Core * c)
{
	TEST("Breaking loop, from depth" <<c->depth)
	TEST("jumping to instruction number: " << jump)
	c->PC=jump;
	c->depth -= depth;
	TEST("to depth " << c->depth <<"...")
	c->memory.free(c->depth); //vycisti do vratane az do hlbky povodneho, loop_label je povodny, tam by to chcelo nechat
	TEST("OK")
	return 0;
}
InstructionContinue::~InstructionContinue()
{
	/* nothing to be done yet */
}
InstructionReturn::InstructionReturn(int depth_)
{
	TEST("hlbka: " << depth_)
	depth = depth_;
	name_ = "Instruction Return";
	group = IGroup_return;
}
int InstructionReturn::execute(Core * c)
{
	TEST("Return from depth" << c->depth)
	c->depth -= depth-1;
	c->PC = c->nested_function->end - 3; //za restore, end_block a ++ u PC
//	Variable * v;
//	v = c->nested_function->return_var->var.back();
//	c->nested_function->return_var->var.pop_back();//zmazanie returnu po naloadovani do stacku
//	c->values.push_back(v);
	TEST("OK")
	return 0;
}
InstructionReturn::~InstructionReturn()
{
	/* nothing to be done */
}
InstructionRestore::InstructionRestore()
{
	name_ = "Instruction Restore";
	group = IGroup_restore;
}

int InstructionRestore::execute(Core *c)
{
	TEST("Restorin' ") //zmaz prebentivne navratove hodnoty a parametre
	c->restore();
	TEST("OK")
	return 0;
}
InstructionRestore::~InstructionRestore()
{
	/* nothing to be done */
}
InstructionRemoveTemp::InstructionRemoveTemp()
{
	name_ = "Instruction RemoveTemp";
	group = IGroup_removetemp;
}
int InstructionRemoveTemp::execute(Core * c)
{
	TEST("Freeing temporary ...")
	c->memory.free_tmp();
	TEST("OK")
	return 0;
}
InstructionRemoveTemp::~InstructionRemoveTemp()
{
	/* nothing to be done */
}
//-----------------------------------COUNTING-----------------------------------------

InstructionPlusPlusInteger::InstructionPlusPlusInteger()
{
	name_ = "Instruction PlusPlusInteger";
	group = IGroup_plusplus;
}
int InstructionPlusPlusInteger::execute(Core * c)
{
	TEST("Integer plusplus ...")
	c->values.back()->integerValue++;
	TEST(c->values.back()->integerValue)
	TEST("OK")
	return 0;
}
InstructionPlusPlusInteger::~InstructionPlusPlusInteger()
{
	/* Nothing to be done yet */
}
InstructionPlusPlusReal::InstructionPlusPlusReal()
{
	name_ = "Instruction PlusPlusReal";
	group = IGroup_plus;
}
int InstructionPlusPlusReal::execute(Core * c)
{
	TEST("Real plusplus ...")
	c->values.back()->realValue++;
	TEST("OK")
	return 0;
}
InstructionPlusPlusReal::~InstructionPlusPlusReal()
{
	/* Nothing to be done yet */
}
InstructionMinusMinusInteger::InstructionMinusMinusInteger()
{
	name_ = "Instruction MinusMinusInteger";
	group = IGroup_minusminus;
}
int InstructionMinusMinusInteger::execute(Core * c)
{
	TEST("Integer minusminus ...")
	c->values.back()->integerValue--;
	TEST("OK")
	return 0;
}
InstructionMinusMinusInteger::~InstructionMinusMinusInteger()
{
	/* Nothing to be done yet */
}
InstructionMinusMinusReal::InstructionMinusMinusReal()
{
	name_ = "Instruction MinusMinusReal";
	group = IGroup_minus;
}
int InstructionMinusMinusReal::execute(Core * c)
{
	TEST("Real minusminus ...")
	c->values.back()->realValue--;
	TEST("OK")
	return 0;
}
InstructionMinusMinusReal::~InstructionMinusMinusReal()
{
	/* Nothing to be done yet */
}
InstructionPlusInteger::InstructionPlusInteger()
{
	name_ = "Instruction PlusInteger";
	group = IGroup_plus;
	TEST(name_)
}
int InstructionPlusInteger::execute(Core * c)
{
	TEST("Adding two integer numbers...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = left + right;
	TEST("OK")
	return 0;
}
InstructionPlusInteger::~InstructionPlusInteger()
{}
InstructionPlusReal::InstructionPlusReal()
{
	name_ = "Instruction PlusReal";
	group = IGroup_plus;
	TEST(name_)
}
int InstructionPlusReal::execute(Core * c)
{
	TEST("Adding two real numbers...")
	float right = c->getFloatFromStack();
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeReal)));
	c->values.back()->realValue = left + right;
	TEST("OK")
	return 0;
}
InstructionPlusReal::~InstructionPlusReal()
{}
InstructionMinusInteger::InstructionMinusInteger()
{
	name_ = "Instruction MinusInteger";
	group = IGroup_minus;
}
int InstructionMinusInteger::execute(Core * c)
{
	TEST("Substraction two integer numbers ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = left - right;
	TEST("OK")
	return 0;
}
InstructionMinusInteger::~InstructionMinusInteger()
{}
InstructionMinusReal::InstructionMinusReal()
{
	name_ = "Instruction MinusReal";
	group = IGroup_minus;
}
int InstructionMinusReal::execute(Core * c)
{
	TEST("Substracting two real numbers ...")
	float right = c->getFloatFromStack();
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeReal)));
	c->values.back()->realValue = left - right;
	TEST("OK")
	return 0;
}
InstructionMinusReal::~InstructionMinusReal()
{}
InstructionMultiplyInteger::InstructionMultiplyInteger()
{
	name_ = "Instruction MultiplyInteger";
	group = IGroup_multiply;
}
int InstructionMultiplyInteger::execute(Core * c)
{
	TEST("Multiplying two integer numbers ...")
	TEST(" right value" << c->values.back()->ID)
	int right = c->getIntFromStack();
	TEST("value " << right)
	TEST(" left value" << c->values.back()->ID << " ")
	int left = c->getIntFromStack();
	TEST("value " << left)
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = left * right;
	TEST("OK")
	return 0;
}
InstructionMultiplyInteger::~InstructionMultiplyInteger()
{}
InstructionMultiplyReal::InstructionMultiplyReal()
{
	name_ = "Instruction MultiplyReal";
	group = IGroup_multiply;
}
int InstructionMultiplyReal::execute(Core * c)
{
	TEST("Multiplying two real numbers ...")
	float right = c->getFloatFromStack();
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeReal)));
	c->values.back()->realValue = left * right;
	TEST("OK")
	return 0;
}
InstructionMultiplyReal::~InstructionMultiplyReal()
{}
InstructionDivideInteger::InstructionDivideInteger()
{
	name_ = "Instruction DivideInteger";
	group = IGroup_divide;
}
int InstructionDivideInteger::execute(Core * c)
{
	TEST("Dividing two integer numbers ...") 
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = left / right;
	TEST("OK")
	return 0;
}
InstructionDivideInteger::~InstructionDivideInteger()
{}
InstructionDivideReal::InstructionDivideReal()
{
	name_ = "Instruction DivideReal";
	group = IGroup_divide;
}
int InstructionDivideReal::execute(Core * c)
{
	TEST("Dividing two real numbers ...") 
	int right = c->getFloatFromStack();
	int left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeReal)));
	c->values.back()->realValue = left / right;
	TEST("OK")
	return 0;
}
InstructionDivideReal::~InstructionDivideReal()
{}
InstructionModulo::InstructionModulo()
{
	name_ = "Instruction Modulo";
	group = IGroup_modulo;
}
int InstructionModulo::execute(Core * c)
{
	TEST("Module ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = left % right;
	TEST("OK")
	return 0;
}
InstructionModulo::~InstructionModulo()
{}
InstructionBinaryAnd::InstructionBinaryAnd()
{
	name_ = "Instruction BinaryAnd";
	group = IGroup_binaryand;
}
int InstructionBinaryAnd::execute(Core * c)
{
	TEST(" & ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = left & right;
	TEST("OK")
	return 0;
}
InstructionBinaryAnd::~InstructionBinaryAnd()
{}
InstructionAnd::InstructionAnd()
{
	name_ = "Instruction And";
	group = IGroup_and;
}
int InstructionAnd::execute(Core *c)
{
	TEST(" && ...") 
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));

	if ((right == 0)
         || (left ==0)) 
		c->values.back()->integerValue = 0;
	else
		c->values.back()->integerValue = 1;
	TEST("OK")
	return 0;
}
InstructionAnd::~InstructionAnd()
{}
InstructionBinaryOr::InstructionBinaryOr()
{
	name_ = "Instruction BinaryOr";
	group = IGroup_binaryor;
}
int InstructionBinaryOr::execute(Core * c)
{
	TEST(" | ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = left | right;
	TEST("OK")
	return 0;
}
InstructionBinaryOr::~InstructionBinaryOr()
{}
InstructionOr::InstructionOr()
{
	name_ = "Instruction Or";
	group = IGroup_or;
}
int InstructionOr::execute(Core *c) //TODO skratene vyhodnocovanie??
{
	TEST(" || ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	if ((right != 0)
	 || (left !=0)) 
		c->values.back()->integerValue = 1;
	else
		c->values.back()->integerValue = 0;
	TEST("OK")
	return 0;
}
InstructionOr::~InstructionOr()
{}
InstructionBinaryNot::InstructionBinaryNot()
{
	name_ = "Instruction BinaryNot";
	group = IGroup_binarynot;
}
int InstructionBinaryNot::execute(Core *c)
{
	TEST(" ~ ...")
	int var = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = ~var;
	TEST("OK")
	return 0;
}
InstructionBinaryNot::~InstructionBinaryNot()
{}
InstructionNot::InstructionNot()
{
	name_ = "Instruction Not";
	group = IGroup_not;
}
int InstructionNot::execute(Core *c) //POZOR, pri unarnych operaciach sa neda pouzivat int!
{
	TEST(" Not ...")
	int var = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	if (var == 0)
		c->values.back()->integerValue = 1;
	else
		c->values.back()->integerValue = 0;
	TEST("OK")
	return 0;
}
InstructionNot::~InstructionNot()
{}
//----------------RELATION------------------------------------------------------------------------------------
InstructionGtInteger::InstructionGtInteger()
{
	name_ = "Instruction GtInteger";
	group = IGroup_gt;
}
int InstructionGtInteger::execute(Core * c)
{
	TEST("Integer > ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left > right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionGtInteger::~InstructionGtInteger()
{}
InstructionGtReal::InstructionGtReal()
{
	name_ = "Instruction GtReal";
	group = IGroup_gt;
}
int InstructionGtReal::execute(Core * c)
{
	TEST("Real > ...")
	float right = c->getFloatFromStack();
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left > right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionGtReal::~InstructionGtReal()
{}
InstructionGeInteger::InstructionGeInteger()
{
	name_ = "Instruction GeInteger";
	group = IGroup_ge;
}
int InstructionGeInteger::execute(Core *c)
{
	TEST("Integer >= ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left >= right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionGeInteger::~InstructionGeInteger()
{}
InstructionGeReal::InstructionGeReal()
{
	name_ = "Instruction GeReal";
	group = IGroup_ge;
}
int InstructionGeReal::execute(Core * c)
{
	TEST("Real >= ...")
	float right = c->getFloatFromStack();
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left >= right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionGeReal::~InstructionGeReal()
{}
InstructionEqualInteger::InstructionEqualInteger()
{
	name_ = "Instruction EqualInteger";
	group = IGroup_equal;
}
int InstructionEqualInteger::execute(Core * c) //pre location nech si napisu funkciu bujde o nastejno:)
{
	TEST(" Integer == ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left == right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionEqualInteger::~InstructionEqualInteger()
{}
InstructionEqualReal::InstructionEqualReal()
{
	name_ = "Instruction EqualReal";
	group = IGroup_equal;
}
int InstructionEqualReal::execute(Core *c)
{
	TEST("Real == ...")
	float right = c->getFloatFromStack();
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left == right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionEqualReal::~InstructionEqualReal()
{}
InstructionEqualObject::InstructionEqualObject()
{
	name_ = "Instruction EqualObject";
	group = IGroup_equal;
}
int InstructionEqualObject::execute(Core * c)
{
	TEST("Object == ...")
	Object * right = c->getObjectFromStack();
	Object * left = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left == right)? 1:0;
	TEST("OK")
	return 0;
}
InstructionEqualObject::~InstructionEqualObject()
{}


InstructionNotEqualInteger::InstructionNotEqualInteger()
{
	name_ = "Instruction NotEqualInteger";
	group = IGroup_notequal;
}
int InstructionNotEqualInteger::execute(Core * c)
{
	TEST("object != ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left != right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionNotEqualInteger::~InstructionNotEqualInteger()
{}
InstructionNotEqualReal::InstructionNotEqualReal()
{
	name_ = "Instruction NotEqualReal";
	group = IGroup_notequal;
}
int InstructionNotEqualReal::execute(Core * c)
{
	TEST("Real != ...")
	int right = c->getFloatFromStack();
	int left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->realValue = (left != right)? 1:0; 
	return 0;
}
InstructionNotEqualReal::~InstructionNotEqualReal()
{}
InstructionNotEqualObject::InstructionNotEqualObject()
{
	name_ = "Instruction NotEqualObject";
	group = IGroup_notequal;
}
int InstructionNotEqualObject::execute(Core * c)
{
	TEST("Object != ...")
	Object * right = c->getObjectFromStack();
	Object * left = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left != right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionNotEqualObject::~InstructionNotEqualObject()
{}
InstructionLtInteger::InstructionLtInteger()
{
	name_ = "Instruction LtInteger";
	group = IGroup_lt;
}
int InstructionLtInteger::execute(Core * c)
{
	TEST("Integer < ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left < right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionLtInteger::~InstructionLtInteger()
{}
InstructionLtReal::InstructionLtReal()
{
	name_ = "Instruction LtReal";
	group = IGroup_lt;
}
int InstructionLtReal::execute(Core * c)
{
	TEST("Real < ...")
	float right = c->getFloatFromStack();
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left < right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionLtReal::~InstructionLtReal()
{}
InstructionLeInteger::InstructionLeInteger()
{
	name_ = "Instruction LeInteger";
	group = IGroup_le;
}
int InstructionLeInteger::execute(Core * c)
{
	TEST("Integer <= ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left <= right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionLeInteger::~InstructionLeInteger()
{}
InstructionLeReal::InstructionLeReal()
{
	name_ = "Instruction LeReal";
	group = IGroup_le;
}
int InstructionLeReal::execute(Core * c)
{
	TEST("Real <=")
	float right = c->getFloatFromStack();
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left <= right)? 1:0; 
	TEST("OK")
	return 0;
}
InstructionLeReal::~InstructionLeReal()
{}
InstructionBegin::InstructionBegin(size_t depth_)
{
	depth = depth_;
	name_ = "Instruction Begin";
	group = IGroup_begin;
}
int InstructionBegin::execute(Core * c)
{
	TEST(name_ << "Increasing depth to:" << c->depth +1<< "...")
	c->depth++;
	TEST("OK")
	return 0;
}
InstructionBegin::~InstructionBegin()
{}
InstructionEndBlock::InstructionEndBlock(size_t endl)
{
	end_loop = endl;
	name_ = "Instruction EndBlock";
	group = IGroup_endblock;
}
int InstructionEndBlock::execute(Core * c)
{
	TEST("Ending depth"<< c->depth <<"...")
	c->memory.free(c->depth);
	c->depth--;
	TEST("OK")
	return 0;
}
InstructionEndBlock::~InstructionEndBlock()
{}
//-------------------------ROBOT ACTIONS-------------------------
InstructionSee::InstructionSee() //uzol ktory sa ma naplnit viditelnymi objektami
{
	node = NULL;
	name_ = "Instruction See";
	group = IGroup_see;
}
int InstructionSee::execute(Core *c) //	ziadne dlasie parametre
{
	TEST("Filling objects in robot's see angle ...")
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = c->body->see(); 
	TEST("OK")
	return 0;
}
InstructionSee::~InstructionSee()
{
	node = NULL;
}
InstructionEye::InstructionEye() //uzol ktory sa ma naplnit viditelnymi objektami
{
	node = NULL;
	name_ = "Instruction Eye";
	group = IGroup_eye;
}
int InstructionEye::execute(Core *c) 
{
	TEST("Getting object from the eye ...")
	Object * o = c->body->eye(c->values.back()->integerValue);
	c->values.pop_back(); 
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeObject)));
	if (!o)
		o = c->memory.dummy();
	c->values.back()->objectValue = o; 
	TEST("OK")
	return 0;
}
InstructionEye::~InstructionEye()
{
	node = NULL;
}
InstructionFetchState::InstructionFetchState()
{
	name_ = "Instruction FetchState";
	group = IGroup_step;
}
int InstructionFetchState::execute(Core *c) //prave jeden parameter
{
	TEST("Fetching state ...")
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = c->body->state();
	TEST("OK")
	return 0;
}
InstructionFetchState::~InstructionFetchState()
{}

InstructionStep::InstructionStep()
{
	name_ = "Instruction Step";
	group = IGroup_step;
}
int InstructionStep::execute(Core *c) //prave jeden parameter
{
	TEST("Stepping ...")
	int steps = c->getIntFromStack();
	c->body->step(steps);
	TEST("OK")
	return 0;
}

InstructionStep::~InstructionStep()
{}
InstructionStepDefault::InstructionStepDefault()
{
	name_ = "Instruction StepDefault";
	group = IGroup_step;
}
int InstructionStepDefault::execute(Core *c) //prave jeden parameter
{
	TEST("Stepping default...")
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = c->body->step();
	TEST("OK")
	return 0;
}
InstructionStepDefault::~InstructionStepDefault()
{}
InstructionWait::InstructionWait()
{
	name_ = "Instruction Wait";
	group = IGroup_wait;
}
int InstructionWait::execute(Core *c) //prave jeden parameter
{
	TEST("Waiting ...")
	int waits = c->getIntFromStack();
//	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
//	c->values.back()->integerValue = 
	c->body->wait(waits);
	TEST("OK")
	return 0;
}
InstructionWait::~InstructionWait() {}

InstructionShootAngle::InstructionShootAngle()
{
	name_ = "Instruction ShootAngle";
	group = IGroup_shoot;
}
int InstructionShootAngle::execute(Core *c)
{
	TEST("Shooting at angle...TODO convert")
	int an = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = c->body->shoot(an); //TODO angle
	TEST("OK")
	return 0;
}
InstructionShootAngle::~InstructionShootAngle() {}

InstructionTurn::InstructionTurn()
{
	name_ = "Instruction Turn";
	group = IGroup_turn;
}
int InstructionTurn::execute(Core *c)
{
	TEST("Turning ...")
	int par = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = c->body->turn(par); //TODO angle
	TEST("OK")
	return 0;
}
InstructionTurn::~InstructionTurn() {}

InstructionTurnR::InstructionTurnR()
{
	name_ = "Instruction TurnR";
	group = IGroup_turn;
}
int InstructionTurnR::execute(Core *c)
{
	TEST("Turning right ...")
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = c->body->turnR();
	TEST("OK")
	return 0;
}
InstructionTurnR::~InstructionTurnR() {}

InstructionTurnL::InstructionTurnL()
{
	name_ = "Instruction TurnL";
	group = IGroup_turn;
}
int InstructionTurnL::execute(Core *c)
{
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = c->body->turnL();
	TEST("OK")
	return 0;
}
InstructionTurnL::~InstructionTurnL() {}

InstructionHit::InstructionHit()
{
	name_ = "Instruction Hit";
	group = IGroup_hit;
}
int InstructionHit::execute(Core *c)
{
	TEST("Checking hit state of object ...")
	Object * o = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = o->Hit();
	TEST("OK")
	return 0;
}
InstructionHit::~InstructionHit() {}

InstructionIsPlayer::InstructionIsPlayer()
{
	name_ = "Instruction IsPlayer";
	group = IGroup_check;
}
int InstructionIsPlayer::execute(Core *c)
{
	TEST("Checking playerism ...")
	Object * o = c->getObjectFromStack();	
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = o->typeObject() & Object::Player;
	TEST("OK")
	return 0;
}
InstructionIsPlayer::~InstructionIsPlayer() {}

InstructionIsWall::InstructionIsWall()
{
	name_ = "Instruction IsWall";
	group = IGroup_check;
}
int InstructionIsWall::execute(Core *c)
{
	TEST("Checking wallism ...")
	Object * o = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = o->typeObject() & Object::Wall_;
	TEST("OK")
	return 0;
}
InstructionIsWall::~InstructionIsWall()
{}
InstructionIsMissille::InstructionIsMissille()
{
	name_ = "Instruction IsMissille";
	group = IGroup_check;
}
int InstructionIsMissille::execute(Core *c)
{
	TEST("Checking missilism ...") //s jednym parametrom
	Object * o = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = o->typeObject() & Object::Missille_;
	TEST("OK")
	return 0;
}
InstructionIsMissille::~InstructionIsMissille() {}

InstructionLocate::InstructionLocate()
{
	name_ = "Instruction Locate";
	group = IGroup_locate;
}
int InstructionLocate::execute(Core *c) //TODO location
{
	TEST("Getting location of object ...")
	Object * o = c->getObjectFromStack();
	Position p; //FIXME neaka inteligetnejsia hodnota? Last seen nefunguje, lebo nemam ako povedat, ze to je neplatna hodnota
	if ((c->body == o)||(c->body->seer.find(o)))
		p = o->get_pos();
	else
		p = c->memory.dummy()->get_pos();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeLocation))); 
	c->values.back()->array.elements[0]->integerValue = p.x;
	c->values.back()->array.elements[1]->integerValue = p.y;
	TEST("OK")
	return 0;
}
InstructionLocate::~InstructionLocate() {}

InstructionIsMoving::InstructionIsMoving()
{
	name_ = "Instruction IsMoving";
	group = IGroup_check;
}
int InstructionIsMoving::execute(Core *c)
{
	TEST("Checking movement ...")
	Object * o = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	if (c->body->seer.find(o))
		c->values.back()->integerValue = o->isMoving();
	else
		c->values.back()->integerValue = rand()%2;
	TEST("OK")
	return 0;
}

InstructionIsMoving::~InstructionIsMoving() {}

InstructionTarget::InstructionTarget()
{
	name_ = "Instruction Target";
	group = IGroup_check;
}
int InstructionTarget::execute(Core *c)
{
	TEST("Returning first unvisited place ...")
	Position p(-1,-1); //TODO random? NEEE, nevedelo by sa, ze vseko skoncilo
	for (size_t i =0; i<c->body->targets.size(); i++)
		if (!c->body->targets[i]->getOk())
		{
			Rectangle t = c->body->targets[i]->tellPosition();
			p.x = t.x + t.width/2;
			p.y = t.y + t.height/2;
			break;
		}
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeLocation)));
	c->values.back()->array.elements[0]->integerValue = p.x;
	c->values.back()->array.elements[1]->integerValue = p.y;
	TEST("OK")
	return 0;
}
InstructionTarget::~InstructionTarget() {}
	
InstructionSaveVariable::InstructionSaveVariable()
{
	name_ = "Instruction Save variable";
	group = IGroup_store;
}
int InstructionSaveVariable::execute(Core * c)
{
	TEST("Saving variable to some place for later retrieve")
	if (c->values.empty())
	{
		TEST( "No variable to save")
		return -1;
	}
	c->savedVar = c->values.back();
	return 0;
}
InstructionSaveVariable::~InstructionSaveVariable() {}

InstructionLoadVariable::InstructionLoadVariable()
{
	name_ = "Instruction Load variable";
	group = IGroup_load;
}
int InstructionLoadVariable::execute(Core * c)
{
	TEST("loading variable from hiden place")
	c->values.push_back(c->savedVar);
	return 0;
}
InstructionLoadVariable::~InstructionLoadVariable() { }

InstructionDirection::InstructionDirection() 
{ 
	node = NULL;
	name_ = "Instruction Direction";
}

int InstructionDirection::execute(Core * c) 
{
	Variable * v = c->getVariableFromStack();
	if (v->array.elements.size()<2)
		return -1;
	
	Position p( v->array.elements[0]->integerValue, 
		v->array.elements[1]->integerValue );
	int res =c->body->getDirection(p);
	v = c->memory.assign_temp(c->typeContainer->find_type(TypeInteger));
	v->integerValue = res;
	c->values.push_back(v);
	return 0;
}

InstructionDirection::~InstructionDirection() { }

InstructionRandom::InstructionRandom() 
{ 
	name_ = "Instruction Number ";
}

int InstructionRandom::execute (Core * c) 
{
	Variable * v;
	v = c->memory.assign_temp(c->typeContainer->find_type(TypeInteger));
	v->integerValue = random ();
	c->values.push_back(v);
	return 0;
}
InstructionRandom::~InstructionRandom() { }
