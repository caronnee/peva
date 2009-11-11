#ifndef ___ROBOT____
#define ___ROBOT____
#include "robot.h"
#include <iostream>

FirstSection::FirstSection()
{
	hitpoints = 100;
	sizeOfMemory = 100;
	seeX = seeY = 5;
}
SecondSection::SecondSection()
{
	missileAttack = 25;
	missileDefense = 25;
	defense = 25;
	attack = 25;
}

Robot::Robot(std::string s, GamePoints p)
{
	name = s;
	nested = "";
	errors = false;
	core = new Core();
	toKill = NULL;
	
	defined_types.push_back(new Create_type(TypeUndefined));
	defined_types.push_back(new Create_type(TypeVoid));
	defined_types.push_back(new Create_type(TypeReal));
	defined_types.push_back(new Create_type(TypeInteger));
	defined_types.push_back(new Create_type(TypeObject));
	defined_types.push_back(new Create_type(TypeLocation));
	defined_types.back()->add("x",find_type(TypeInteger));
	defined_types.back()->add("y",find_type(TypeInteger));
	Create_type * c = new Create_type(TypeArray, 0); //pre SEE
	c->composite(find_type(TypeObject));
	defined_types.push_back(c);

	/*	Pridavanie defaultnych premennych	*/

	dev_null = new Node("dev/null", find_type(TypeUndefined), -1);

	Node * n = defined.add("true",find_type(TypeInteger));
	n->nested = Global;
	core->memory.assign(n, 0);
	n->var[0]->integerValue = 1;

	n = defined.add("false",find_type(TypeInteger));
	n->nested = Global;
	core->memory.assign(n, 0);
	n->var[0]->integerValue = 0;

	//pridana premenna pre NULL;
	n = defined.add("NULL",find_type(TypeObject));
	n->nested = Global;
	core->memory.assign(n, 0);
	n->var[0]->objectValue = NULL;
	
	//pridana premenna pre this;
	n = defined.add("this",find_type(TypeObject));
	n->nested = Global;
	core->memory.assign(n,0);
	n->var[0]->objectValue = body;
	
	//pridana premenna pre viditelnost
	n = defined.add("seen",c);
	n->nested = Global;
}
Create_type * Robot::find_type(Type t)
{
	for (size_t i= 0; i< defined_types.size(); i++)
		if (defined_types[i]->type == t)
			return defined_types[i];
	return NULL;//ZAVAZNA CHYBA! Ale zo strany programatora;), mozno by to stalo za excepsnu
}

Create_type * Robot::find_array_type(int range, Create_type * descend)
{
	for (size_t i= 0; i< defined_types.size(); i++)
		if ((defined_types[i]->type == TypeArray)&&(defined_types[i]->data_type == descend))
			return defined_types[i];
	Create_type * t = new Create_type(TypeArray, range);
	t->composite(descend);
	defined_types.push_back(t);
	return t;
}

Function * Robot::find_f(std::string nam)
{
	if (core->nested_function->name == nam)
	{
		return core->nested_function;
	}
	for(int i =0; i< core->functions.size(); i++)
	{
		if(core->functions[i]->name == nam)
		{
			return core->functions[i];
		}
	}
	return NULL;
}

Node * Robot::find_var(std::string var_name, bool & b)
{
	//najskor a hlada medzi premennymi deklarovanymi vo funkcii
	std::string s = nested + var_name;
	Tree * t = defined.find_string(s);
	for (std::list<Node*>::iterator i = t->items.begin(); 
			i != t->items.end(); 
			i++)
	{
		if ((*i)->name == s)
		{
			b = true;
			return (*i);
		}
	}
	//hlada sa medzi globalnymi premennymi
	s = var_name;
	t = defined.find_string(s);
	for (std::list<Node*>::iterator i = t->items.begin(); 
			i != t->items.end(); 
			i++)
	{
		if ((*i)->name == s)
		{
			b = true;
			return (*i);
		}
	}
	b = false;
	return dev_null;
}
Node * Robot::add(std::string name, Create_type * type)
{
	Node * n = defined.add(nested + name, type);
	if (n == NULL)
		return dev_null;
	return n;

}
/*
 *Vracia ukazovatel na samotny uzol, ktory skryva hodnotu, v ktorom je ulozena nasa hodnota
 */
void Robot::add_global(Instructions ins)
{
	core->PC = instructions.size();
	for (int i =0; i< ins.size(); i++)
	{
		instructions.push_back(ins[i]);	
	}
}
void Robot::output(Tree * t)
{
	for (std::list<Node*>::iterator i = t->items.begin();i!=t->items.end(); i++)
		std::cout << "prvok s menom:" << (*i)->name <<std::endl; 
	for (int i = 0; i < 256; i++)
	{
		if (t->next[i]!=NULL)
		{
			std::cout << "Down:" <<i << std::endl; 
			output(t->next[i]);
			std::cout << "UP!" << std::endl; 
		}
	}
	std::cout << "END "<<std::endl; 
}
void Robot::add(Instructions ins)
{
	for (int i =0; i<ins.size(); i++)
	{
		instructions.push_back(ins[i]);
	}
}
void Robot::add_function( Instructions ins)
{
	core->nested_function->begin = instructions.size();
	core->nested_function->end = core->nested_function->begin + ins.size()+1;
	core->functions.push_back(core->nested_function);
	for (int i =0; i< ins.size(); i++)
	{
		instructions.push_back(ins[i]);
	}
	if(core->nested_function->name != "main") //TODO mohla by vracat tiez nejaku hodnotu a vracat sa na 'begin'
		instructions.push_back(new InstructionRestore()); //pre procedury
}
void Robot::enter(std::string name, std::vector<Parameter_entry> params, Create_type * return_type) //CONTINUE, add parameters_list
{
//	nested += name + DELIMINER_CHAR;
	core->nested_function = new Function(name, params,add("",return_type));
}
void Robot::leave() //odide z funkcie
{
	nested = "";
	core->nested_function = NULL;
}
void Robot::save_to_xml()
{
	LIBXML_TEST_VERSION;

	data.doc = xmlNewDoc(BAD_CAST "1.0");
	data.root_ptr = xmlNewNode(NULL, BAD_CAST "Machine");
	xmlDocSetRootElement(data.doc, data.root_ptr);
	xmlNodePtr parent = data.root_ptr;
	xmlNodePtr ptr;
	int fce_num = 0;
	std::cout<< "Zapamatovane mena:" <<std::endl; 
	for(int i =0; i< core->functions.size(); i++)
	{
		std::cout<< core->functions[i]->name<<std::endl; 
	}
	for(int i =0; i< instructions.size(); i++)
	{
		if(core->functions[fce_num]->end == i)
		{
			xmlAddChild(data.root_ptr, parent);
			parent = data.root_ptr;
			fce_num++;
		}
		if(core->functions[fce_num]->begin == i)
			parent = xmlNewNode(NULL, BAD_CAST core->functions[fce_num]->name.c_str());
		ptr = instructions[i]->xml_format();
		xmlAddChild(parent, ptr);
	}
	xmlAddChild(data.root_ptr, parent);
	xmlSaveFormatFileEnc("machine.xml", data.doc, "UTF-8", 1);
	xmlFreeDoc(data.doc);
}

void Robot::execute()
{
	while(core->PC < instructions.size())
	{
		std::cout << "Number :" << core->PC<< "@"<<instructions[core->PC]->name();//getc(stdin);
		instructions[core->PC]->execute(core);
		std::cout << " OOOOOK"; //getc(stdin);
		core->PC++;
	//	getc(stdin);
		//sleep(1);
	}
}
Robots::Robots(GamePoints g_)
{
	g = g_;
	actualRobot = NULL;
}
void Robots::createNew(std::string name)
{
	std::cout << "Creating new robot" << std::endl; 
	if (actualRobot!=NULL)
		robots.push_back(actualRobot);
	actualRobot = new Robot(name, g);
	std::cout << "New robot created" << std::endl; 	
}

void Robots::set(Options o, size_t value)
{
	switch(o) //TODO po zlinkovani
	{
		case OptionHealth:
			std::cout << "setting health to:" << value << std::endl; 
			break;
		case OptionSeeX:	       
			std::cout << "setting SEE x to:" << value << std::endl; 
			break;
		case OptionSeeY:
			std::cout << "setting SEE y to:" << value << std::endl; 
			break;
		case OptionSee:
			std::cout << "setting SEE to:" << value << std::endl; 
			break;
		case OptionMemory: //NEFUNGUJE kvoli tomu, ze uz su pridane hodnoty ako NULL
			actualRobot->core->memory.realloc(value); //TODO skobtrolovat,ci to nepresvihava celkovy pocet
			break;
		case OptionAttack:
			std::cout << "setting Attack x to:" << value << std::endl; 
			break;
		case OptionDefense:
			std::cout << "setting defense to " << value << std::endl; 
			break;
		case OptionMisilleAttack:
			std::cout << "setting Missille attack to " << value << std::endl; 
			break;
		case OptionMisilleHealth:
			std::cout << "setting Missille health to:" << value << std::endl; 
			break;
	}
}

void Robot::addKilled(unsigned i,Operation op, size_t number)
{
	if (toKill !=NULL)
	{
		error(i,WarningKillAlreadyDefined);
		return;
	}
	switch (op)
	{
		case OperationNotEqual:
			toKill = new TargetKillNumberNot(number);
			break;
		case OperationLess:
			toKill = new TargetKillNumberLess(number);
			break;
		case OperationLessEqual:
			toKill = new TargetKillNumberLessThen(number);
			break;
		case OperationGreater:
			toKill = new TargetKillNumberMore(number);
			break;
		case OperationGreaterEqual:
			toKill = new TargetKillNumberMoreThen(number);
			break;
		default:
			toKill = new TargetKillNumber(number);
			break;	
	}
}

void Robot::addVisit(std::vector<Position> positions)
{
	for(size_t i =0; i< positions.size(); i++)
	{
		targets.push_back(new TargetVisit(positions[i]));
	}
}

void Robot::addVisitSeq(std::vector<Position> positions)
{
	targets.push_back(new TargetVisitSequence(positions));
}
void Robot::error(unsigned line, ErrorCode e, std::string m)
{
	switch (e)
	{
		case WarningKillAlreadyDefined:
			warning = true;
			warningList += "Line:" + deconvert<int>(line) + "Line"+ deconvert<int>(line) + "Line:" + deconvert<int>(line) + ":Ignoring, kill was already defined\n";
			break;
		case WarningConversionToInt:
			warning = true;
			warningList += "Line:" + deconvert<int>(line) + "Conversion from real to int\n";
			break;
		case WarningRedefinedOption:
			warning = true;
			warningList += "Line:" + deconvert<int>(line) + "Option already defined, using new value\n";
		case ErrorVariableNotFound:
		case ErrorVariableNotDefined:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + "Variable" + m + " not defined\n";
			break;
		case ErrorToMuchInitializers:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + "Too much initializers\n";
			break;
		case ErrorTypeNotRecognized:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + "Type not recognized\n";
			break;
		case ErrorConversionImpossible:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + "Conversion impossible\n";
			break;
		case ErrorOperationNotSupported:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + "Operation is not supported\n";
			break;
		case ErrorWrongNumberOfParameters:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + "Wrong number of parameters\n";
			break;
		case ErrorFunctionNotDefined:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + "Function Not defined\n";
			break;
		case ErrorOutOfRange:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + "Type out of range\n";
			break;
			
		default:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + "Unrecognized error\n";
			break;
	}
}

void Robot::consolidate()
{
	std::vector<InstructionBreak *> breaks;
	std::vector<InstructionBegin *> begins;
	std::vector<InstructionContinue *> conts;
	std::vector<int> beg;
	for(size_t i =0; i<instructions.size(); i++) 
	{
		if (instructions[i] == NULL)
		{
			std::cout << "Null instruction, something forgotten?";getc(stdin);
			continue;
		}
		std::cout << i << instructions[i]->name()<<",..\t";
		InstructionContinue *c = dynamic_cast<InstructionContinue *>(instructions[i]);
		if (c)
		{
			std::cout << i <<",1."<<std::endl;
			conts.push_back(c);		
			continue;
		}
		InstructionBreak *b= dynamic_cast<InstructionBreak *>(instructions[i]);
		if (b)
		{
			std::cout << i <<",2."<<std::endl;
			breaks.push_back(b);
			continue;
		}
		InstructionBegin *be=dynamic_cast<InstructionBegin *>(instructions[i]);
		if(be)
		{
			if (!be->depth) //ak nie je zaciatkom, end
				continue;
			std::cout << i <<",3."<< instructions[i]->name() <<std::endl;
			breaks.push_back(NULL);
			conts.push_back(NULL);
			begins.push_back(be);
			beg.push_back(i);
			continue;
		}
		InstructionEndBlock * e= dynamic_cast<InstructionEndBlock *>(instructions[i]);
		if(e)
		{
			if (!e->end_loop)
				continue;
			std::cout << i <<",4."<<breaks.empty() <<std::endl;
			//resolve vsetky breaky az po NULL
			while ((!breaks.empty())&&(breaks.back()!=NULL))
			{
				std::cout <<begins.size(); 
				breaks.back()->set(i+e->end_loop, begins.back()->depth);
				breaks.pop_back();
			}
			while ((!conts.empty())&&(conts.back()!=NULL))
			{
				conts.back()->set(i -1, begins.back()->depth);
				conts.pop_back();
			}
			if (!conts.empty())
				conts.pop_back();
			if(!breaks.empty())
				breaks.pop_back();
			begins.pop_back();
			beg.pop_back();
			continue;
		}
		std::cout << i << "!" << std::endl;
	}
}
Robot::~Robot()
{
	std::cout << "hee";
	getc(stdin);
	delete core;
	delete dev_null;
	delete toKill;
	delete body;

	for (size_t i = 0; i< defined_types.size(); i++)
	{
		delete defined_types[i];
	}

	for (std::list<TargetVisit *>::iterator i = targets.begin(); 
		i!= targets.end(); i++)
	{
		delete (*i);
	}

	//delete instructions

	for (size_t i = 0; i < instructions.size(); i++)
	{
		delete instructions[i];
	}
}
#endif
