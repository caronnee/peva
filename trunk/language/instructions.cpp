#include "instructions.h"
#include <iostream>

//FIXME premenovat floatfrom an real, aby to olo konzistentne
//TODO zmeit na list

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
	std::cout << "Assigning variable" << node->name << "...";
	Variable * v = c->memory.assign(*node->type_of_variable,node->ID, c->depth);
	node->var.push_back(v); //pridali sme pre akutialne zanorenie premenu
	std::cout << "OK" << std::endl;
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
	std::cout << "Loading local variable " << node->name << "...";
	c->values.push_back(node->var.back());
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
int InstructionLoadGlobal::execute(Core * c) //FIXME kedyto potrebujem? nikdy tam nedam viac ako jednu premennu, pretoze sa nezanorujem,osetrene  bisone
{
	std::cout << " Loading global variable: " << node->name << "...";
	Variable * v;
	v = node->var[0];
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
	var = new Variable("const");
	type = TypeInteger;
	var->integerValue = i;
	name_ = "InstructionLoad";
}
InstructionLoad::InstructionLoad(float f)
{
	name_ = "InstructionLoad";
	constant = true;
	type = TypeReal;
	var = new Variable("const");
	var->realValue = f;
}
int InstructionLoad::execute(Core *c)
{
	if(constant)
	{
		std::cout << "Loading constant ...";
		c->values.push_back(var);
		std::cout << "OK" << std::endl;
		return 0;
	}//else from stack
	std::cout << "Loading array, element number:" << c->values.back()->integerValue <<"...";
	int range = c->getIntFromStack();
	c->loadElement(range);
	std::cout << "\t\t\t" << c->values.back();
	std::cout << "OK" << std::endl;
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
InstructionConversionToInt::InstructionConversionToInt()
{
	name_ = "InstructionConversionToInt";
}
int InstructionConversionToInt::execute(Core * c)
{
	std::cout << "Converting " << c->values.back()->realValue;
	float f=c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (int)f;
	std::cout << " to integer" << c->values.back()->integerValue << "...";
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionConversionToReal::InstructionConversionToReal()
{
	name_ = "InstructionConversionToReal";
}
int InstructionConversionToReal::execute(Core * c)
{
	std::cout << "Converting" <<c->values.back()->integerValue;
	float f = (float)c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->realValue = f;
	std::cout << "to real" << c->values.back()->realValue << "...";
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
	c->values.push_back(c->values.back());
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionStoreInteger::InstructionStoreInteger()
{
	name_ = "InstructionStoreInteger";
}
int InstructionStoreInteger::execute(Core * c)
{
	std::cout<<"Storing integer, value: " << c->values.back()->integerValue;
	c->saveInteger();
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionStoreReal::InstructionStoreReal()
{
	name_ = "InstructionStoreReal";
}
int InstructionStoreReal::execute(Core * c)
{
	std::cout<<"Storing real, value" <<c->values.back()->realValue<< "..." ;
	c->saveFloat();
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionStoreObject::InstructionStoreObject()
{
	name_ = "InstructionStoreObject";
}
int InstructionStoreObject::execute(Core * c)
{
	std::cout << "Storing object, address:" << c->values.back()->objectValue <<"...";
	c->saveObject();
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
	function = f_;
	name_ = "Call";
}
int Call::execute(Core * c) //TODO zmenit kopirovanie parametrov
{
	std::cout << "Calling function: " << function->name << std::endl;
	c->nested_functions.push_back(c->nested_function);
	c->nested_function = function;
	for( size_t i = 0; i< function->parameters.size(); i++)
	{
		Variable * v;
		//ak pridane ako referencia, skopiruj pointre
		if (function->parameters[i].val_type == PARAMETER_BY_REFERENCE)
		{
			std::cout << "Storing parameter by reference" << std::endl;
			v = c->values.back(); //mozem to tam spravit, lebo v gramatike sa to da pouzit len pramo s premennou
			//Musi byt premenna
			function->parameters[i].node->var.push_back(v);
		}
		else
		{
			std::cout << "Storing parameter by value" << std::endl;getc(stdin);
			v = c->memory.assign(*function->parameters[i].node->type_of_variable,function->parameters[i].node->ID,c->depth + 1);
			function->parameters[i].node->var.push_back(v);
			Variable * vvv = c->values.back();
			v->copyValue(vvv);
			c->values.pop_back();
		}
	}
	Variable * v;
	Node * ret = function->return_var;
	v = c->memory.assign_temp(*ret->type_of_variable); //aby zmizlo po ukonceni
	ret->var.push_back(v);//skopiruje si zo stacku hodnoty svojich parametrov
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
	Variable * v = c->values.back();
	c->values.pop_back();
	if (v->integerValue)
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
	c->PC = c->nested_function->end - 3; //za restore, end_block a ++ u PC
	Variable * v;
	v = c->nested_function->return_var->var.back();
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
	std::cout << "Restorin' "; //zmaz prebentivne navratove hodnoty a parametre
	c->restore();
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionRemoveTemp::InstructionRemoveTemp()
{
	name_ = "InstructionRemoveTemp";
}
int InstructionRemoveTemp::execute(Core * c)
{
	c->memory.free_tmp();
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
	c->values.back()->integerValue++;
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
	c->values.back()->realValue++;
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
	c->values.back()->integerValue--;
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
	c->values.back()->realValue--;
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = left + right;
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
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeReal)));
	c->values.back()->realValue = left + right;
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = left - right;
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
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeReal)));
	c->values.back()->realValue = left - right;
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
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = left * right;
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
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeReal)));
	c->values.back()->realValue = left * right;
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = left / right;
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
	int left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeReal)));
	c->values.back()->realValue = left / right;
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = left % right;
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
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = left & right;
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));

	if ((right == 0)
         || (left ==0)) 
		c->values.back()->integerValue = 0;
	else
		c->values.back()->integerValue = 1;
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = left | right;
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionOr::InstructionOr()
{
	name_ = "InstructionOr";
}
int InstructionOr::execute(Core *c) //TODO skratene vyhodnocovanie??
{
	std::cout << " || ...";
	int right = c->getIntFromStack();
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	if ((right != 0)
	 || (left !=0)) 
		c->values.back()->integerValue = 1;
	else
		c->values.back()->integerValue = 0;
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
	int var = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = ~var;
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
	int var = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	if (var == 0)
		c->values.back()->integerValue = 1;
	else
		c->values.back()->integerValue = 0;
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left > right)? 0:1; 
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
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left > right)? 0:1; 
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left >= right)? 0:1; 
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
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left >= right)? 0:1; 
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left == right)? 1:0; 
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
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left == right)? 1:0; 
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
	Object * left = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left == right)? 1:0;
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left != right)? 1:0; 
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
	int left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->realValue = (left != right)? 1:0; 
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
	Object * left = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left != right)? 1:0; 
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left < right)? 1:0; 
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
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left < right)? 1:0; 
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
	int left = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left <= right)? 1:0; 
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
	float left = c->getFloatFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = (left <= right)? 1:0; 
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
//-------------------------ROBOT ACTIONS-------------------------
InstructionSee::InstructionSee(Node * n) //uzol ktory sa ma naplnit viditelnymi objektami
{
	node = n;
	name_ = "InstructionSee";
}
int InstructionSee::execute(Core *c) //	ziadne dlasie parametre
{
	std::cout << "Filling objects in robot's see angle ...";
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = c->robot->See(); //TODO, kam to naplni
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionStep::InstructionStep()
{
	name_ = "InstructionStep";
}
int InstructionStep::execute(Core *c) //prave jeden parameter
{
	std::cout << "Stepping ...";
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = c->robot->Step();
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionStepDefault::InstructionStepDefault()
{
	name_ = "InstructionStepDefault";
}
int InstructionStepDefault::execute(Core *c) //prave jeden parameter
{
	std::cout << "Stepping default...";
	int steps = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = c->robot->Step(steps);
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionWait::InstructionWait()
{
	name_ = "InstructionWait";
}
int InstructionWait::execute(Core *c) //prave jeden parameter
{
	std::cout << "Waiting ...";
	int waits = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = c->robot->Wait(waits);
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionShootLocation::InstructionShootLocation()
{
	name_ = "InstructionShootLocation";
}
int InstructionShootLocation::execute(Core *c) //prave jeden parameter
{
	std::cout << "Shooting at location...";
	int x = c->values.back()->array.elements[0]->integerValue;
	int y = c->values.back()->array.elements[1]->integerValue;
	c->values.pop_back();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = c->robot->Shoot(x,y); //TODO vypocitat angle, smer x a smer y
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionShootAngle::InstructionShootAngle()
{
	name_ = "InstructionShootAngle";
}
int InstructionShootAngle::execute(Core *c) //TODO
{
	std::cout << "Shooting at angle...TODO convert";
	int an = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = c->robot->Shoot(an,an); //TODO angle
	std::cout << "OK" << std::endl;
	return 0;
}
InstructionTurn::InstructionTurn()
{
	name_ = "InstructionTurn";
}
int InstructionTurn::execute(Core *c)
{
	std::cout << "Turning ...";
	int par = c->getIntFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = c->robot->Turn(par); //TODO angle
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionTurnR::InstructionTurnR()
{
	name_ = "InstructionTurnR";
}
int InstructionTurnR::execute(Core *c)
{
	std::cout << "Turning right ...";
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = c->robot->TurnR();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionTurnL::InstructionTurnL()
{
	name_ = "InstructionTurnL";
}
int InstructionTurnL::execute(Core *c)
{
	std::cout << "Turning left ...";
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = c->robot->TurnL();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionHit::InstructionHit()
{
	name_ = "InstructionHit";
}
int InstructionHit::execute(Core *c)
{
	std::cout << "Checking hit state of object ...";
	Object * o = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = o->Hit();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionIsPlayer::InstructionIsPlayer()
{
	name_ = "InstructionIsPlayer";
}
int InstructionIsPlayer::execute(Core *c)
{
	std::cout << "Checking playerism ...";
	Object * o = c->getObjectFromStack();	
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = o->IsPlayer();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionIsWall::InstructionIsWall()
{
	name_ = "InstructionIsWall";
}
int InstructionIsWall::execute(Core *c)
{
	std::cout << "Checking wallism ...";
	Object * o = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = o->IsWall();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionIsMissille::InstructionIsMissille()
{
	name_ = "InstructionIsMissille";
}
int InstructionIsMissille::execute(Core *c)
{
	std::cout <<"Checking missilism ..."; //s jednym parametrom
	Object * o = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = o->IsMissille();
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionLocate::InstructionLocate()
{
	name_ = "InstructionLocate";
}
int InstructionLocate::execute(Core *c) //TODO location
{
	std::cout << "Getting location of object ...";
	Object * o = c->getObjectFromStack();
	Position p = o->Locate();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeLocation))); //BIG TODO referencia na location, lebo netusi, ao location vyzera
	c->values.back()->array.elements[0]->integerValue = p.x;
	c->values.back()->array.elements[1]->integerValue = p.y;
	std::cout << "OK" <<std::endl;
	return 0;
}
InstructionIsMoving::InstructionIsMoving()
{
	name_ = "InstructionIsMoving";
}
int InstructionIsMoving::execute(Core *c)
{
	std::cout << "Checking movement ...";
	Object * o = c->getObjectFromStack();
	c->values.push_back(c->memory.assign_temp(Create_type(TypeInteger)));
	c->values.back()->integerValue = o->IsMoving();
	std::cout << "OK" <<std::endl;
	return 0;
}
