#include <iostream>
#include "../h/robot.h"

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
	missilles = 10;
	/* robot data */
	name = s;
	nested = "";
	errors = false;
	defined_types = new TypeContainer();
	core = new Core( defined_types);
	toKill = NULL;
	nullable = new Object(NULL);
	
	defined_types->add(new Create_type(TypeUndefined));
	defined_types->add(new Create_type(TypeVoid));
	defined_types->add(new Create_type(TypeReal));
	defined_types->add(new Create_type(TypeInteger));
	defined_types->add(new Create_type(TypeObject));
	Create_type * t = new Create_type(TypeLocation);
	t->add("x",defined_types->find_type(TypeInteger));
	t->add("y",defined_types->find_type(TypeInteger));
	defined_types->add(t);
	Create_type * c = new Create_type(TypeArray, 0); //pre SEE
	c->composite(defined_types->find_type(TypeObject));
	defined_types->add(c);

	/*	Pridavanie defaultnych premennych	*/

	dev_null = new Node("dev/null", defined_types->find_type(TypeUndefined), -1);

	Node * n = defined.add("true",defined_types->find_type(TypeInteger));
	n->nested = Global;
	core->memory.assign(n, 0);
	n->var[0]->integerValue = 1;

	n = defined.add("false",defined_types->find_type(TypeInteger));
	n->nested = Global;
	core->memory.assign(n, 0);
	n->var[0]->integerValue = 0;

	//pridana premenna pre NULL;
	n = defined.add("NULL",defined_types->find_type(TypeObject));
	n->nested = Global;
	core->memory.assign(n, 0);
	n->var[0]->objectValue = nullable;
	
	//pridana premenna pre this;
	n = defined.add("this",defined_types->find_type(TypeObject));
	n->nested = Global;
	core->memory.assign(n,0);
	n->var[0]->objectValue = core->body;
	
	//pridana premenna pre viditelnost
	n = defined.add("seen",c);
	n->nested = Global;

}
Create_type * Robot::find_type(Type t)
{
	last_type = defined_types->find_type(t);	
	return last_type;
}
Body * Robot::getBody ()
{
	return core->body;
}
void Robot::setSkin(Skin * s)
{
	skinName = s->nameOfSet;
	core->body->setSkin(s);
}
void Robot::declare_type()
{
	active_type.push(last_type);
}
void Robot::leave_type()
{
	if (active_type.empty())
	{ 
		std::cout << "Ech? Active prazdna"; getc(stdin);
		return;
	}
	active_type.top()->reset(); // prejde, pretoze hierarchicka struktura(nemoze zas ebou rovnake triedy, takze vzdy ked resetujeme, bude to potom mio stacku)
	active_type.pop();
}
void Robot::declare_next()
{
	Create_type * t = active_type.top()->next();
	if (NULL)
	{
		std::cout << "Error:No NEXT"; getc(stdin);
		error(-1, Robot::ErrorOutOfRange);
		return;
	}
	active_type.push(t);
}
Create_type * Robot::find_array_type(int range, Create_type * descend)
{
	last_type = defined_types->find_array_type(range, descend);
	return last_type;
}

Function * Robot::find_f(std::string nam)
{
	if (core->nested_function->name == nam)
	{
		return core->nested_function;
	}
	for(size_t i =0; i< core->functions.size(); i++)
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
	std::string name_ = nested + name;
	Node * n = defined.add(name_, type);
	if (n == NULL)
		return dev_null;
	return n;

}

Node * Robot::add(std::string name)
{
	if (active_type.empty())
	{
		std::cout << "empty active type";
	}
	return add(name, active_type.top());
}
/*
 *Vracia ukazovatel na samotny uzol, ktory skryva hodnotu, v ktorom je ulozena nasa hodnota
 */
void Robot::add_global(Instructions ins)
{
	core->PC = instructions.size();
	for (size_t i =0; i< ins.size(); i++)
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
	for (size_t i =0; i<ins.size(); i++)
	{
		instructions.push_back(ins[i]);
	}
}
void Robot::add_function( Instructions ins)
{
	core->nested_function->begin = instructions.size();
	core->nested_function->end = core->nested_function->begin + ins.size()+1;
	core->functions.push_back(core->nested_function);
	for (size_t i =0; i< ins.size(); i++)
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
	for(size_t i =0; i< core->functions.size(); i++)
	{
		std::cout<< core->functions[i]->name<<std::endl; 
	}
	for(size_t i =0; i< instructions.size(); i++)
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
	xmlCleanupParser();
}

void Robot::add_kill(size_t id)
{
	killTarget.push_back(id);
}
void Robot::execute()
{
	while(core->PC < instructions.size())
	{
		action();
	}
}
void Robot::action()
{
	std::cout << "Number :" << core->PC<< "@"<<instructions[core->PC]->name()<<std::endl;
	if (core->body->isMoving())
		return;
	while (scheduller->ready())
	{
		instructions[core->PC]->execute(core);
		scheduller->penalize(instructions[core->PC]);
		core->PC++;
	}
}
Robots::Robots(GamePoints g_)
{
	g = g_;
	actualRobot = NULL;
}
Robots::Robots()
{
	actualRobot = NULL;
}
Skin * Robots::addSkin(std::string name)
{
	Skin * s;
	for (size_t i = 0; i< skins.size(); i++)
	{
		if (skins[i]->nameOfSet == name)
			return skins[i];
	}
	s = new Skin(name, Skin::BotSkin);
	Skin *ms = new Skin(name, Skin::MissilleSkin );
	mSkins.push_back(ms);
	skins.push_back(s);
	return s;
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
		case OptionId:
			std::cout << "setting id to" << value << std::endl;
			break;
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
		targets.push_back(new TargetVisit(0));
	}
	for(size_t i = targets.size() - positions.size(); i< positions.size(); i++)
	{
		//nezalezi na poradi
		targets[i]->initPosition(positions[i]);
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
	scheduller = new SchedulleRound(); //TPDP konfigurovatelne
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
			conts.push_back(c);		
			continue;
		}
		InstructionBreak *b= dynamic_cast<InstructionBreak *>(instructions[i]);
		if (b)
		{
			breaks.push_back(b);
			continue;
		}
		InstructionBegin *be=dynamic_cast<InstructionBegin *>(instructions[i]);
		if(be)
		{
			if (!be->depth) //ak nie je zaciatkom, end
				continue;
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
			//resolve vsetky breaky az po NULL
			while ((!breaks.empty())&&(breaks.back()!=NULL))
			{
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
	}
}
Robot::~Robot()
{
	delete scheduller;
	delete core;
	delete dev_null;
	delete toKill;
	delete nullable;
	delete defined_types;

	for (std::vector<Target *>::iterator i = targets.begin(); 
		i!= targets.end(); i++)
	{
		delete (*i);
	}
	targets.clear();

	//delete instructions

	std::cout << "Instuctions size:" << instructions.size() << std::endl;
	for (size_t i = 0; i < instructions.size(); i++)
	{
		if (instructions[i] == NULL)
		{
			std::cout << "Eeeeek!"; getc(stdin);
		}
		delete instructions[i];
	}
	instructions.clear();
}
Skin * Robots::addmSkin( std::string name)
{
	for (size_t i = 0; i< mSkins.size(); i++)
	{
		if (mSkins[i]->nameOfSet == name)
			return mSkins[i];
	}
	Skin *ms = new Skin(name, Skin::MissilleSkin );
	mSkins.push_back(ms);
	return ms;
}

//zbytocne!
void Robot::setmSkin(Skin* mSkin)
{
	for(size_t i=0; i<missilles; i++)
		core->body->addAmmo(new Missille(mSkin, core->body));
}

void Robots::checkSkins()
{
	for (size_t i =0; i< robots.size(); i++)
	{
		if (!robots[i]->skined())
		{
			robots[i]->setSkin(addSkin("dragon"));
		}
		robots[i]->setmSkin(addmSkin(robots[i]->skinName));
		robots[i]->core->body->turn(0);
	}
}
bool Robot::skined()
{
	return core->body->hasSkin();
}
Robots::~Robots()
{
	//deleting skins
	while(!skins.empty())
	{
		delete(skins.back());
		skins.pop_back();
	}
	while(!mSkins.empty())
	{
		delete(mSkins.back());
		mSkins.pop_back();
	}
	for (size_t i = 0; i< robots.size(); i++)
	{
		delete robots[i];
	}
	robots.clear();
	actualRobot = NULL;
}

Robot::Robot()
{
	name = "Robot";
	missilles = 10; //TODO konfigrovatelne
}

