#include "instructions.h"
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
	std::cout << " Loadujem globalnu premennu: " << node->name << node->var.size();
	getc(stdin);
	if (node->var.size() == 0) 
	{
		Var v;
		v.var = c->memory.assign(node->type_of_variable, node->ID, 0);
		node->var.push_back(v);
	}	
	Value v;
	v.loaded = node->var[0].var;
	c->values.push_back(v);
	std::cout << "Hodnota:" << v.loaded->integerValue << std::endl;
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
		std::cout << "Loadujem konstantu!" << std::endl;
		getc(stdin);
		Value v;
		v.loaded = var;
		c->values.push_back(v);
		std::cout << " hodnota: " << v.loaded->integerValue << std::endl;
		return 0;
	}//else from stack
	std::cout << "loadujem array" <<std::endl; //TODO
	getc(stdin);
	Value range = c->values.back();
	c->values.pop_back();
	Value comp = c->values.back();
	c->values.pop_back();
	comp.loaded = comp.loaded->array.elements[range.loaded->integerValue];
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
	c->values.back().loaded->integerValue = (int)c->values.back().loaded->realValue;
	return 0;
}
InstructionConversionToReal::InstructionConversionToReal()
{
	name_ = "InstructionConversionToReal";
}
int InstructionConversionToReal::execute(Core * c)
{
	c->values.back().loaded->realValue = (float)c->values.back().loaded->integerValue;
	return 0;
}
InstructionStoreInteger::InstructionStoreInteger()
{
	name_ = "InstructionStoreInteger";
}
int InstructionStoreInteger::execute(Core * c)
{
	int right = c->getIntFromStack();
	c->values.back().loaded->integerValue = right;
	c->values.pop_back();
	return 0;
}
InstructionStoreReal::InstructionStoreReal()
{
	name_ = "InstructionStoreReal";
}
int InstructionStoreReal::execute(Core * c)
{
	float right = c->getFloatFromStack();
	c->values.back().loaded->realValue = right;
	c->values.pop_back();
	return 0;
}
InstructionStoreObject::InstructionStoreObject()
{
	name_ = "InstructionStoreObject";
}
int InstructionStoreObject::execute(Core * c)
{
	Object * right = c->getObjectFromStack();
	c->values.back().loaded->objectValue = right;
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
	//zoberie [pocet premennych aktualne na stacku], ulozi do svojich, v pripade varu ulozi svoje premenne(copy, pozor na pole a na recordy)
	//sucasne do return typu da novy variabl
	c->nested_functions.push_back(c->nested_function);
	c->nested_function = function;
	Var v;
	Node * ret = function->return_var;
	std::cout << v.var << "navratova adresa" << std::endl;
	v.var = c->memory.assign(ret->type_of_variable,ret->ID, c->depth ); //aby zmizlo po ukonceni
	ret->var.push_back(v);
	std::cout << "calling function"<< function->name << std::endl;
	for(size_t i = 0; i< function->parameters.size(); i++)
	{
		Var v;
		//ak pridane ako refeencia, skopiruj pointre
		//TODO skontrolovat, ci sedia parametre
		if (function->parameters[i].val_type == PARAMETER_BY_REFERENCE)
		{
			v.var = c->values.back().loaded; //mozem to tam spravit, lebo v gramatike sa to da pouzit len pramo s premennou
			//Musi byt premenna
			function->parameters[i].node->var.push_back(v);
		}
		else
		{
			//TODO co ak je parametrom array alebo location?
			v.var = c->memory.assign(function->parameters[i].node->type_of_variable,function->parameters[i].node->ID,c->depth + 1);
			function->parameters[i].node->var.push_back(v);
			Variable * vvv = c->values.back().loaded;
			switch (c->values.back().loaded->type)
			{
				case TypeInteger:
					v.var->integerValue = vvv->integerValue;
				       break;
				case TypeReal:
					v.var->realValue = vvv->realValue;
			 		break;
				case TypeObject:
					v.var->objectValue = vvv->objectValue; //TODO type_location
				default: return -1;
			}
			c->values.pop_back(); //uz skopirovana premenna
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
	std::cout << "popping out value" <<std::endl;
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
	std::cout << "jumping :" << shift << std::endl;
	c->PC+=shift;
	std::cout << "new position" << c->PC << std::endl;
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
	std::cout << "laded result: " << v.loaded->integerValue << std::endl;
	if (v.loaded->integerValue)
	{
		std::cout <<"jumping to YES position" << std::endl;
		c->PC+=yes;
		std::cout << "new position" << c->PC << std::endl;
	}
	else 
	{
		std::cout <<"jumping to NO position" << std::endl;
		c->PC+=no;
		std::cout << "new position" << c->PC << std::endl;
	}
	getc(stdin);
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
	c->PC+=jump;
	c->depth -= depth;
	std::cout << "BREAK!:) Returning to depth " << c->depth << std::endl;
	c->memory.free(c->depth+1); //vycisti do vratane az hi hlbky povodneho, loop_label je povodny, tam by to chcl nechat
	getc(stdin);
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
	getc(stdin);
	depth = depth_;
	name_ = "InstructionReturn";
}
int InstructionReturn::execute(Core * c)
{
	std::cout << "Zpatky do hlbky" << c->depth << std::endl;
	c->depth -= depth-1;
	std::cout << "zpatky do hlbky" << c->depth << std::endl;
	c->PC = c->nested_function->end -3; //za restore, end_block a ++ u PC
	std::cout << "A na instrukciu cislo" << c->PC << std::endl;
	Value v;
	v.loaded = c->nested_function->return_var->var.back().var;
	c->nested_function->return_var->var.pop_back();//zmazanie returnu po naloadovani do stacku
	c->values.push_back(v);
	std::cout << "size os values: " << c->values.size();
	for (size_t i =0; i < c->values.size(); i++)
	{
		std::cout << "value adress= " << c->values[i].loaded << std::endl;
	}
	getc(stdin);
	return 0;
}
InstructionRestore::InstructionRestore()
{
	name_ = "InstructionRestore";
}
int InstructionRestore::execute(Core *c)
{
	std::cout << "restorin'"; //zmaz prebentivne navratove hodnoty a para,etre
	c->restore();
	getc(stdin);
	return 0;
}
//--------------------------POCITANIE--------------------------------------------------
InstructionPlusPlusInteger::InstructionPlusPlusInteger()
{
	name_ = "InstructionPlusPlusInteger";
}
int InstructionPlusPlusInteger::execute(Core * c)
{
	std::cout << name_ << ":" << c->values.size() << std::endl;
	c->values.back().loaded->integerValue++; //TODO cez neajky fciu vracajucu pointer
	return 0;
}
InstructionPlusPlusReal::InstructionPlusPlusReal()
{
	name_ = "InstructionPlusPlusReal";
}
int InstructionPlusPlusReal::execute(Core * c)
{
	std::cout << name_ << ":" << c->values.size() << std::endl;
	c->values.back().loaded->realValue++;
	return 0;
}
InstructionMinusMinusInteger::InstructionMinusMinusInteger()
{
	name_ = "InstructionMinusMinusInteger";
}
int InstructionMinusMinusInteger::execute(Core * c)
{
	c->values.back().loaded->integerValue--;
	return 0;
}
InstructionMinusMinusReal::InstructionMinusMinusReal()
{
	name_ = "InstructionMinusMinusReal";
}
int InstructionMinusMinusReal::execute(Core * c)
{
	c->values.back().loaded->realValue--;
	return 0;
}
InstructionPlusInteger::InstructionPlusInteger()
{
	name_ = "InstructionPlusInteger";
	std::cout << name_ << std::endl;
}
int InstructionPlusInteger::execute(Core * c)
{
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue + right;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().loaded->type = TypeInteger;//teoreticky uz netreba
	return 0;
}
InstructionPlusReal::InstructionPlusReal()
{
	name_ = "InstructionPlusReal";
	std::cout << name_ << std::endl;
}
int InstructionPlusReal::execute(Core * c)
{
	std::cout << name_ << std::endl;
	float right = c->getFloatFromStack(); //TODO nepritupovat k stacku priamo
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue + right;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().loaded->type = TypeReal;
	return 0;
}
InstructionMinusInteger::InstructionMinusInteger()
{
	name_ = "InstructionMinusInteger";
}
int InstructionMinusInteger::execute(Core * c)
{
	std::cout << name_ << std::endl;
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue - right;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().loaded->type = TypeInteger;
	return 0;
}
InstructionMinusReal::InstructionMinusReal()
{
	name_ = "InstructionMinusReal";
}
int InstructionMinusReal::execute(Core * c)
{
	std::cout << name_ << std::endl;
	float right = c->getFloatFromStack();
	c->values.back().hlp.realValue = c->values.back().loaded->realValue - right;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().loaded->type = TypeReal;
	return 0;
}
InstructionMultiplyInteger::InstructionMultiplyInteger()
{
	name_ = "InstructionMultiplyInteger";
}
int InstructionMultiplyInteger::execute(Core * c)
{
	std::cout << name_ << std::endl;
	float right = c->getFloatFromStack();
	c->values.back().hlp.realValue = c->values.back().loaded->realValue * right;
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionMultiplyReal::InstructionMultiplyReal()
{
	name_ = "InstructionMultiplyReal";
}
int InstructionMultiplyReal::execute(Core * c)
{
	std::cout << name_ << std::endl;
	float right = c->getFloatFromStack();
	c->values.back().hlp.realValue = c->values.back().loaded->realValue * right;
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionDivideInteger::InstructionDivideInteger()
{
	name_ = "InstructionDivideInteger";
}
int InstructionDivideInteger::execute(Core * c)
{
	int right = c->getIntFromStack();
	c->values.back().hlp.realValue = c->values.back().loaded->integerValue / right;
	return 0;
}
InstructionDivideReal::InstructionDivideReal()
{
	name_ = "InstructionDivideReal";
}
int InstructionDivideReal::execute(Core * c)
{
	int right = c->getFloatFromStack();
	c->values.back().hlp.realValue = c->values.back().loaded->realValue / right;
	return 0;
}
InstructionModulo::InstructionModulo()
{
	name_ = "InstructionModulo";
}
int InstructionModulo::execute(Core * c)
{
	std::cout << name_ << std::endl;
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue % right;
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
	std::cout << name_ << std::endl;
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue & right;
	c->values.back().loaded = & c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionAnd::InstructionAnd()
{
	name_ = "InstructionAnd";
}
int InstructionAnd::execute(Core *c)
{
	std::cout << name_ << std::endl; //TODO upravit tak, zeget int, addTemp()
	int right = c->getIntFromStack();
	Value left = c->values.back();
	if ((right == 0)
		|| (left.loaded->integerValue ==0)) 
		c->values.back().hlp.integerValue = 0;
	else
		c->values.back().hlp.integerValue = 1;
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
	std::cout << name_ << std::endl;
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = c->values.back().loaded->integerValue | right;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionOr::InstructionOr()
{
	name_ = "InstructionOr";
}
int InstructionOr::execute(Core *c) //TODO skratene vyhodnocovanie??
{
	std::cout << name_ << std::endl;
	int right = c->getIntFromStack();
	Value left = c->values.back();
	if ((right != 0)
		|| (left.loaded->integerValue !=0)) 
		c->values.back().hlp.integerValue = 1;
	else
		c->values.back().hlp.integerValue = 0;
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
	std::cout << name_ << std::endl;
	c->values.back().hlp.integerValue = ~c->values.back().loaded->integerValue;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionNot::InstructionNot()
{
	name_ = "InstructionNot";
}
int InstructionNot::execute(Core *c) //POZOR, pri unarnych operaciach sa neda pouzivat int!
{
	std::cout << name_ << std::endl;
	if (c->values.back().loaded->integerValue == 0)
		c->values.back().hlp.integerValue = 1;
	else
		c->values.back().hlp.integerValue = 1;
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
//----------------------------------------------------------------------------------------------------
InstructionGtInteger::InstructionGtInteger()
{
	name_ = "InstructionGtInteger";
}
int InstructionGtInteger::execute(Core * c)
{
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue > right)? 0:1; 
	return 0;
}
InstructionGtReal::InstructionGtReal()
{
	name_ = "InstructionGtReal";
}
int InstructionGtReal::execute(Core * c)
{
	std::cout << name_ << std::endl;
	float right = c->getFloatFromStack();
	Value left = c->values.back();
	c->values.back().hlp.integerValue = (c->values.back().loaded->realValue > right)? 0:1; 
	c->values.back().loaded = &c->values.back().hlp;
	c->values.back().hlp.type = TypeInteger;
	return 0;
}
InstructionGeInteger::InstructionGeInteger()
{
	name_ = "InstructionGeInteger";
}
int InstructionGeInteger::execute(Core *c)
{
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue >= right)? 0:1; 
	return 0;
}
InstructionGeReal::InstructionGeReal()
{
	name_ = "InstructionGeReal";
}
int InstructionGeReal::execute(Core * c)
{
	std::cout << name_ << std::endl;
	float right = c->getFloatFromStack();
	Value left = c->values.back();
	c->values.back().hlp.integerValue = (c->values.back().loaded->realValue >= right)? 0:1; 
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionEqualInteger::InstructionEqualInteger()
{
	name_ = "InstructionEqualInteger";
}
int InstructionEqualInteger::execute(Core * c) //pre location nech si napisu funkciu bujde o nastejno:)
{
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue == right)? 1:0; 
	return 0;
}
InstructionEqualReal::InstructionEqualReal()
{
	name_ = "InstructionEqualReal";
}
int InstructionEqualReal::execute(Core *c)
{
	float right = c->getFloatFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->realValue == right)? 1:0; 
	return 0;
}
InstructionEqualObject::InstructionEqualObject()
{
	name_ = "InstructionEqualObject";
}
int InstructionEqualObject::execute(Core * c)
{
	std::cout << name_ << std::endl;
	Object * right = c->getObjectFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->objectValue == right)? 1:0;
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
				 ||(left_v->array.elements.size()!= right_v->array.elements.size()))
				{
					equal = false;
					break;
				}
				for(size_t i = 0; i< left_v->array.elements.size(); i++)
				{
					lefts.push(left_v->array.elements[i]);
					rights.push(right_v->array.elements[i])
				}
			}
			break;*///array sa porovnavat nebude,moc miesta a ets aj penalizacia by bola divna
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionNotEqualInteger::InstructionNotEqualInteger()
{
	name_ = "InstructionNotEqualInteger";
}
int InstructionNotEqualInteger::execute(Core * c)
{
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue != right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionNotEqualReal::InstructionNotEqualReal()
{
	name_ = "InstructionNotEqualReal";
}
int InstructionNotEqualReal::execute(Core * c)
{
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
	Object * right = c->getObjectFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->objectValue != right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionLtInteger::InstructionLtInteger()
{
	name_ = "InstructionLtInteger";
}
int InstructionLtInteger::execute(Core * c)
{
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue < right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionLtReal::InstructionLtReal()
{
	name_ = "InstructionLtReal";
}
int InstructionLtReal::execute(Core * c)
{
	float right = c->getFloatFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->realValue < right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionLeInteger::InstructionLeInteger()
{
	name_ = "InstructionLeInteger";
}
int InstructionLeInteger::execute(Core * c)
{
	int right = c->getIntFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->integerValue <= right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionLeReal::InstructionLeReal()
{
	name_ = "InstructionLeReal";
}
int InstructionLeReal::execute(Core * c)
{
	std::cout << name_ << std::endl;
	float right = c->getFloatFromStack();
	c->values.back().hlp.integerValue = (c->values.back().loaded->realValue <= right)? 1:0; 
	c->values.back().loaded = &c->values.back().hlp;
	return 0;
}
InstructionBegin::InstructionBegin()
{
	name_ = "InstructionBegin";
}
int InstructionBegin::execute(Core * c)
{
	c->depth++;
	std::cout << name_ << "going to depth" << c->depth<< std::endl;
	getc(stdin);
	return 0;
}
InstructionEndBlock::InstructionEndBlock()
{
	name_ = "InstructionEndBlock";
}
int InstructionEndBlock::execute(Core * c)
{
	std::cout << name_ << " and freeing in depth"<< c->depth <<std::endl;
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
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->See();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionStep::InstructionStep()
{
	name_ = "InstructionStep";
}
int InstructionStep::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->Step();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionWait::InstructionWait()
{
	name_ = "InstructionWait";
}
int InstructionWait::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->Wait();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionShoot::InstructionShoot()
{
	name_ = "InstructionShoot";
}
int InstructionShoot::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->Shoot();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionTurn::InstructionTurn()
{
	name_ = "InstructionTurn";
}
int InstructionTurn::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value par = s->values.back();
	s->values.pop_back();
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->Turn(par.loaded->integerValue);
	v.loaded->type = TypeInteger;
	//ak to nie je integer, tak papa
	return 0;
}
InstructionTurnR::InstructionTurnR()
{
	name_ = "InstructionTurnR";
}
int InstructionTurnR::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->TurnR();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionTurnL::InstructionTurnL()
{
	name_ = "InstructionTurnL";
}
int InstructionTurnL::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->TurnL();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionHit::InstructionHit()
{
	name_ = "InstructionHit";
}
int InstructionHit::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->Hit();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionIsPlayer::InstructionIsPlayer()
{
	name_ = "InstructionIsPlayer";
}
int InstructionIsPlayer::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->IsPlayer();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionIsWall::InstructionIsWall()
{
	name_ = "InstructionIsWall";
}
int InstructionIsWall::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->IsWall();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionIsMissille::InstructionIsMissille()
{
	name_ = "InstructionIsMissille";
}
int InstructionIsMissille::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->IsMissille();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionLocate::InstructionLocate()
{
	name_ = "InstructionLocate";
}
int InstructionLocate::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->Locate();
	v.loaded->type = TypeInteger;
	return 0;
}
InstructionIsMoving::InstructionIsMoving()
{
	name_ = "InstructionIsMoving";
}
int InstructionIsMoving::execute(Core *s)
{
	std::cout << name_ << std::endl;
	Value v;
	v.loaded = &v.hlp;
	v.loaded->integerValue = s->robot->IsMoving();
	v.loaded->type = TypeInteger;
	return 0;
}
