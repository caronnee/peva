//TODO namiesto removetemp = operacia +remove temp, aby to bolo atomicke
//TODO return value by sa mala vytvorit az v okamziku RETURN u
#include <iostream>
#include <cmath>
#include "../h/instructions.h"
#include "../../add-ons/h/macros.h"

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
	name_ = "InstructionCreate";
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
	name_ = "InstructionLoadLocal";
	group = IGroup_loadlocal;
}
InstructionLoadLocal::InstructionLoadLocal(Node * n)
{
	node = n;
	name_ = "InstructionLoadLocal";
	group = IGroup_loadlocal;
}
int InstructionLoadLocal::execute(Core * c)
{
	TEST("Loading local variable " << node->name)
	//TEST(" id =  " << node->var.back()->ID << "..." )
	//TEST(", value =  " << node->var.back()->integerValue << "..." )
	if (node->var.size() == 0)
	{
		TEST("Error, prazdna premenna, nikfy by nemalo nastat")
		throw "somethng baaaaas hapeened";
	}
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
	name_ = "InstructionLoadGlobal";
	group = IGroup_loadglobal;	
}
InstructionLoadGlobal::InstructionLoadGlobal(Node * n)
{
	node = n;
	name_ = "InstructionLoadGlobal";
	group = IGroup_loadglobal;
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
	name_ = "InstructionLoad";
	var = NULL;
	group = IGroup_load;
}
InstructionLoad::InstructionLoad(int i)
{
	constant = true;
	var = new Variable("const");
	type = TypeInteger;
	var->integerValue = i;
	name_ = "InstructionLoad";
	group = IGroup_load;
}
InstructionLoad::InstructionLoad(float f)
{
	name_ = "InstructionLoad";
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
	name_ = "InstructionConversionToInt";
	group = IGroup_conversiontoint;
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
	name_ = "InstructionConversionToReal";
	group = IGroup_conversiontoreal;
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
	name_ = "InstructionDuplicate";
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

InstructionStoreInteger::InstructionStoreInteger()
{
	name_ = "InstructionStoreInteger";
	group = IGroup_storeinteger;
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
	name_ = "InstructionStoreReal";
	group = IGroup_storereal;
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
	name_ = "InstructionStoreObject";
	group = IGroup_storeobject;
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
InstructionStore::InstructionStore()
{
	name_ = "InstructionStore";
	group = IGroup_store;
}
// pouzije sa iba pri returne
int InstructionStore::execute(Core * c)
{
	TEST("Storing complex variable ..." )
	c->copyVariable();
	TEST("OK")
	return 0;
}

InstructionStore::~InstructionStore()
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
	c->nested_functions.push_back(c->nested_function);
	c->nested_function = function;
	for( size_t i = 0; i< function->parameters.size(); i++)
	{
		Variable * v;
		//ak pridane ako referencia, skopiruj pointre
		if (function->parameters[i].val_type == PARAMETER_BY_REFERENCE)
		{
			TEST("Storing parameter by reference")
			v = c->getVariableFromStack(); //mozem to tam spravit, lebo v gramatike sa to da pouzit len pramo s premennou
			//Musi byt premenna
			function->parameters[i].node->var.push_back(v);
		}
		else
		{
			TEST("Storing parameter by value")
			c->memory.assign(function->parameters[i].node,c->depth + 1);
			Variable * vvv = c->values.back();
			function->parameters[i].node->var.back()->copyValue(vvv);
			c->values.pop_back();
		}
	}
	Variable * v;
	Node * ret = function->return_var;
	v = c->memory.assign_temp(ret->type_of_variable); //aby zmizlo po ukonceni
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
	name_ = "InstructionPop";
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
	name_ = "InstructionMustJump";
	group = IGroup_mustjump;
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
	name_ = "InstructionJump";
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
	name_ = "InstructionBreak";
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
	name_ = "InstructionContinue";
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
	name_ = "InstructionReturn";
	group = IGroup_return;
}
int InstructionReturn::execute(Core * c)
{
	TEST("RETURN: vo values je aktualne: " << c->values.size()) //zmaz prebentivne navratove hodnoty a parametre
	for (size_t i =0; i< c->values.size(); i++)
	{
		TEST(" " << c->values[i]->ID)
	}
	TEST("Return from depth" << c->depth)
	c->depth -= depth-1;
	TEST("to depth" << c->depth <<"...")
	c->PC = c->nested_function->end - 3; //za restore, end_block a ++ u PC
	Variable * v;
	v = c->nested_function->return_var->var.back();
	c->nested_function->return_var->var.pop_back();//zmazanie returnu po naloadovani do stacku
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
	name_ = "InstructionRestore";
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
	name_ = "InstructionRemoveTemp";
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
	name_ = "InstructionPlusPlusInteger";
	group = IGroup_plusplusinteger;
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
	name_ = "InstructionPlusPlusReal";
	group = IGroup_plusplusreal;
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
	name_ = "InstructionMinusMinusInteger";
	group = IGroup_minusminusinteger;
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
	name_ = "InstructionMinusMinusReal";
	group = IGroup_minusminusreal;
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
	name_ = "InstructionPlusInteger";
	group = IGroup_plusinteger;
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
	name_ = "InstructionPlusReal";
	group = IGroup_plusreal;
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
	name_ = "InstructionMinusInteger";
	group = IGroup_minusinteger;
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
	name_ = "InstructionMinusReal";
	group = IGroup_minusreal;
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
	name_ = "InstructionMultiplyInteger";
	group = IGroup_multiplyinteger;
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
	name_ = "InstructionMultiplyReal";
	group = IGroup_multiplyreal;
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
	name_ = "InstructionDivideInteger";
	group = IGroup_divideinteger;
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
	name_ = "InstructionDivideReal";
	group = IGroup_dividereal;
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
	name_ = "InstructionModulo";
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
	name_ = "InstructionBinaryAnd";
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
	name_ = "InstructionAnd";
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
	name_ = "InstructionBinaryOr";
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
	name_ = "InstructionOr";
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
	name_ = "InstructionBinaryNot";
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
	name_ = "InstructionNot";
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
	name_ = "InstructionGtInteger";
	group = IGroup_gtinteger;
}
int InstructionGtInteger::execute(Core * c)
{
	TEST("Integer > ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left > right)? 0:1; 
	TEST("OK")
	return 0;
}
InstructionGtInteger::~InstructionGtInteger()
{}
InstructionGtReal::InstructionGtReal()
{
	name_ = "InstructionGtReal";
	group = IGroup_gtreal;
}
int InstructionGtReal::execute(Core * c)
{
	TEST("Real > ...")
	float right = c->getFloatFromStack();
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left > right)? 0:1; 
	TEST("OK")
	return 0;
}
InstructionGtReal::~InstructionGtReal()
{}
InstructionGeInteger::InstructionGeInteger()
{
	name_ = "InstructionGeInteger";
	group = IGroup_geinteger;
}
int InstructionGeInteger::execute(Core *c)
{
	TEST("Integer >= ...")
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left >= right)? 0:1; 
	TEST("OK")
	return 0;
}
InstructionGeInteger::~InstructionGeInteger()
{}
InstructionGeReal::InstructionGeReal()
{
	name_ = "InstructionGeReal";
	group = IGroup_gereal;
}
int InstructionGeReal::execute(Core * c)
{
	TEST("Real >= ...")
	float right = c->getFloatFromStack();
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = (left >= right)? 0:1; 
	TEST("OK")
	return 0;
}
InstructionGeReal::~InstructionGeReal()
{}
InstructionEqualInteger::InstructionEqualInteger()
{
	name_ = "InstructionEqualInteger";
	group = IGroup_equalinteger;
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
	name_ = "InstructionEqualReal";
	group = IGroup_equalreal;
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
	name_ = "InstructionEqualObject";
	group = IGroup_equalobject;
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
	name_ = "InstructionNotEqualInteger";
	group = IGroup_notequalinteger;
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
	name_ = "InstructionNotEqualReal";
	group = IGroup_notequalreal;
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
	name_ = "InstructionNotEqualObject";
	group = IGroup_notequalobject;
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
	name_ = "InstructionLtInteger";
	group = IGroup_ltinteger;
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
	name_ = "InstructionLtReal";
	group = IGroup_ltreal;
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
	name_ = "InstructionLeInteger";
	group = IGroup_leinteger;
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
	name_ = "InstructionLeReal";
	group = IGroup_lereal;
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
	name_ = "InstructionBegin";
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
	name_ = "InstructionEndBlock";
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
	name_ = "InstructionSee";
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
	name_ = "InstructionEye";
	group = IGroup_eye;
}
int InstructionEye::execute(Core *c) 
{
	TEST("Getting object from the eye ...")
	Object * o = c->body->eye(c->values.back()->integerValue);
	c->values.pop_back(); 
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeObject)));
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
	name_ = "InstructionFetchState";
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
	name_ = "InstructionStep";
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
	name_ = "InstructionStepDefault";
	group = IGroup_stepdefault;
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
	name_ = "InstructionWait";
	group = IGroup_wait;
}
int InstructionWait::execute(Core *c) //prave jeden parameter
{
	TEST("Waiting ...")
	int waits = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = c->body->wait(waits);
	TEST("OK")
	return 0;
}
InstructionWait::~InstructionWait() {}

InstructionShootLocation::InstructionShootLocation()
{
	name_ = "InstructionShootLocation";
	group = IGroup_shootlocation;
}
int InstructionShootLocation::execute(Core *c)
{
	TEST("Shooting at location...") //TODO upravit pamat aby som nemusela ifovat
	if (c->values.back()->array.elements.size() < 2)
		return -1;
	float f = (float)
	(c->values.back()->array.elements[1]->integerValue - c->body->get_pos().y)
		/
	(float)(c->values.back()->array.elements[0]->integerValue - c->body->get_pos().x);
	int x = toDegree(atan(f));
	c->values.pop_back();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeInteger)));
	c->values.back()->integerValue = c->body->shoot(x); 
	TEST("OK")
	return 0;
}
InstructionShootLocation::~InstructionShootLocation() {}

InstructionShootAngle::InstructionShootAngle()
{
	name_ = "InstructionShootAngle";
	group = IGroup_shootangle;
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
	name_ = "InstructionTurn";
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
	name_ = "InstructionTurnR";
	group = IGroup_turnr;
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
	name_ = "InstructionTurnL";
	group = IGroup_turnl;
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
	name_ = "InstructionHit";
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
	name_ = "InstructionIsPlayer";
	group = IGroup_isplayer;
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
	name_ = "InstructionIsWall";
	group = IGroup_iswall;
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
	name_ = "InstructionIsMissille";
	group = IGroup_ismissille;
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
InstructionIsMissille::~InstructionIsMissille()
{}
InstructionLocate::InstructionLocate(Create_type t)
{
	type = t;
	name_ = "InstructionLocate";
	group = IGroup_locate;
}
int InstructionLocate::execute(Core *c) //TODO location
{
	TEST("Getting location of object ...")
	Object * o = c->getObjectFromStack();
	Position p( -1, -1 ); //FIXME neaka inteligetnejsia hodnota? Last seen nefunguje, lebo nemam ako povedat, ze to je neplatna hodnota
	if (c->body->seer.find(o))
		p = o->get_pos();
	c->values.push_back(c->memory.assign_temp(c->typeContainer->find_type(TypeLocation))); 
	c->values.back()->array.elements[0]->integerValue = p.x;
	c->values.back()->array.elements[1]->integerValue = p.y;
	TEST("OK")
	return 0;
}
InstructionLocate::~InstructionLocate() {}

InstructionIsMoving::InstructionIsMoving()
{
	name_ = "InstructionIsMoving";
	group = IGroup_ismoving;
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
	name_ = "InstructionTarget";
	group = IGroup_ismoving;
}
int InstructionTarget::execute(Core *c)
{
	TEST("Returning first unvisited place ...")
	Position p(-1,-1);
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
