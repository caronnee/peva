#include "./robot.h"
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
	errors = false;//TODO pridat errorou hlasku
	core = new Core();
	toKill = NULL;
}

Function * Robot::find_f(std::string nam)
{
	for(int i =0; i< core->functions.size(); i++)
	{
		if(core->functions[i]->name == nam)
		{
			return core->functions[i];
		}
	}
	return core->nested_function;
}

Node * Robot::find_var(std::string var_name)
{
	std::string s = nested + var_name;
	Tree * t = defined.find_string(s);
	for (std::list<Node*>::iterator i = t->items.begin(); 
			i != t->items.end(); 
			i++)
	{
		if ((*i)->name == s)
			return (*i);
	}
	s = var_name;
	t = defined.find_string(s);
	for (std::list<Node*>::iterator i = t->items.begin(); 
			i != t->items.end(); 
			i++)
	{
		if ((*i)->name == s)
			return (*i);
	}
	return NULL;
}
Node * Robot::add(std::string name, Create_type type)
{
	return defined.add(nested + name, type);
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
void Robot::add_function(std::vector<Parameter_entry> c, Instructions ins)
{
	core->nested_function->parameters = c;
	core->nested_function->begin = instructions.size();
	core->nested_function->end = core->nested_function->begin + ins.size()+1;
	core->functions.push_back(core->nested_function);
	for (int i =0; i< ins.size(); i++)
	{
		instructions.push_back(ins[i]);
	}
	if(core->nested_function->name == "main")
	{
//		instructions.push_back(new InstructionMustJump(ins.size()*-1));
		core->PC = core->nested_function->begin;
	}
	else
	{
		instructions.push_back(new InstructionRestore()); //pre procedury
	}
}
void Robot::enter(std::string name, Create_type return_type)
{
	nested += name + DELIMINER_CHAR;
	core->nested_function = new Function(name, add("",return_type));
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
		//std::cout << i << "," << instructions[i]->name_ <<std::endl;
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
		instructions[core->PC]->execute(core);
		core->PC++;
	}
}
Robots::Robots(GamePoints g_)
{
	g = g_;
	actualRobot = NULL;
}
void Robots::createNew(std::string name)
{
	actualRobot = new Robot(name, g);
}

void Robot::enter_loop()
{
	last_loop_number++; //v podstate loop_zanorenie
	loop_labels.push(last_loop_number);
}
void Robot::end_loop()
{
	last_loop_number--;
	loop_labels.pop();
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
		case OptionMemory:
			actualRobot->core->memory.realok(value); //TODO skobtrolovat,ci to nepresvihava celkovy pocet
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
		default:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + "Unrecognized error\n";
			break;
	}
}
