#include <iostream>
#include "../h/robot.h"
#include "../../add-ons/h/macros.h"

#define MAX_EYE_ANGLE 90

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

Robot::Robot(std::string s, std::string space_, GamePoints p)
{
	space = space_;
	scheduller = NULL;

	missilles = 3;
	/* robot data */
	name = s;
	nested = "";
	errors = false;
	defined_types = new TypeContainer();
	core = new Core( defined_types);
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
	dev_null = NULL;
}

std::string Robot::getSpace()const
{
	return space;
}
std::string Robot::getName()const
{
	return name;
}
//TODO uistit sa, ze je ti nenaalokovane
void Robot::variables()
{
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
}

Create_type * Robot::find_type(Type t)
{
	last_type = defined_types->find_type(t);	
	return last_type;
}
Body * Robot::getBody()
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
		TEST("Ech? Active prazdna")
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
		TEST("Error:No NEXT") 
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
		TEST("empty active type")
	}
	return add(name, active_type.top());
}
/*
 *Vracia ukazovatel na samotny uzol, ktory skryva hodnotu, v ktorom je ulozena nasa hodnota
 */
void Robot::add_global(Instructions ins)
{
	core->PC = instructions.size();
	core->PCs.push_back(core->PC);
	for (size_t i =0; i< ins.size(); i++)
	{
		instructions.push_back(ins[i]);	
	}
}
void Robot::output(Tree * t)
{
	for (std::list<Node*>::iterator i = t->items.begin();i!=t->items.end(); i++)
		TEST("prvok s menom:" << (*i)->name ); 
	for (int i = 0; i < 256; i++)
	{
		if (t->next[i]!=NULL)
		{
			TEST("DOWN:" <<i ); 
			output(t->next[i]);
			TEST("UP!" ); 
		}
	}
	TEST("END "); 
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
	TEST("Zapamatovane mena:" ); 
	for(size_t i =0; i< core->functions.size(); i++)
	{
		TEST(core->functions[i]->name); 
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


void Robot::execute()
{
	bool done;
	while(core->PC < instructions.size())
	{
		action(done);
	}
}
bool Robot::action(bool & conditions)
{
	//TEST("Number :" << core->PC<< "@"<<instructions[core->PC]->name());
	conditions = core->body->tasks == 0;
	bool b = core->body->alive();
	if (core->body->isMoving()||!b)
		return b;
	while (scheduller->ready())
	{
		scheduller->penalize(instructions[core->PC]); //kvoli zmena PC
		instructions[core->PC]->execute(core);
		core->PC++;
	}
	return core->body->alive();
}
Robots::Robots() { }

Skin * Robots::addSkin(std::string name)
{
	Skin * s;
	for (size_t i = 0; i< skins.size(); i++)
	{
		if (skins[i]->nameOfSet == name)
			return skins[i];
	}
	s = new BotSkin(name);
	Skin *ms = new MissilleSkin(name);
	mSkins.push_back(ms);
	skins.push_back(s);
	return s;
}

void Robots::createNew(std::string name)
{
	TEST("Creating new robot");
	robots.push_back( new Robot(name, input, g) );
	robots.back()->errorList = input + ":\n";
}

void Robot::setScheduler(int type, const std::vector<int>& penals )
{
	if (!type)
	{
		scheduller = new SchedulleRound(penals);
		return;
	}
	scheduller = new SchedulleTime(type, penals); 
}
void Robots::finalize(int vis)
{
	for (size_t i=0; i<robots.size(); i++)
	{
		robots[i]->consolidate();
		if (!robots[i]->skined())
		{
			robots[i]->setSkin(addSkin("dragon"));
		}
		robots[i]->setmSkin(addmSkin(robots[i]->skinName));
		robots[i]->core->body->turn(0);
		robots[i]->getBody()->seer.setEyes(robots[i]->getBody()->eyeAngle,vis); //TODO opravit, celkost ma urcovat mapa
	}
}
void Robots::resolve()
{
	/* show robot, who's the guy that should be killed */
	for (size_t i =0; i< resolveName.size(); i++)
	{
		Body * killer = NULL, * toKill = NULL;
		for (size_t j=0; j<robots.size(); j++)
		{
			if (robots[i]->getName() == resolveName[i].name)
			{
				killer = resolveName[i].robot->getBody();
				toKill = robots[j]->getBody();
				if (robots[j]->getSpace() == resolveName[i].prefix)
					break;
			}
		}
		if (toKill!=NULL)
			killer->addKill(toKill);
		else
			parseWarningList += "Target robot " + resolveName[i].name + " at " + resolveName[i].prefix + 
				" at line " + deconvert<size_t>(resolveName[i].line) + "not recognized, ignoring." ;
	}

	/* tell the robot what means that once upon a time he should be found at start position or robot r*/
	for (size_t i =0; i< resolveStart.size(); i++)
	{
		Rectangle t(-1,-1,20,20);
		for (size_t j=0; j<robots.size(); j++)
			if (robots[j]->getName() == resolveStart[i].name)
			{
				t.x = robots[j]->getBody()->get_pos().x;
				t.y = robots[j]->getBody()->get_pos().y;
				if (robots[j]->getSpace() == resolveStart[i].prefix)
					break;
			}
		resolveStart[i].target->initPosition(t);
		if ( t.x <0 )
		{
			resolveStart[i].target->setOk();

			parseWarningList += "Start position of robot " + resolveStart[i].name + " at " + resolveStart[i].prefix + " at line "+ deconvert<size_t>(resolveStart[i].line) + "not found, ignoring." ;
		}
	}
	/* tell robot what means position '0,1,2...' in the map */
	for (size_t j=0; j<robots.size(); j++)
		robots[j]->getBody()->initTargetPlaces();
}
void Robots::set(Options o, size_t value)
{
	switch(o) //TODO po zlinkovani
	{
		case OptionHealth:
			TEST("setting health to:" << value ); 
			robots.back()->core->body->hitpoints = value;
			break;
		case OptionSee:
			TEST("setting eyes angle to:" << value ); 
			robots.back()->core->body->eyeAngle = value % MAX_EYE_ANGLE;
			break;
		case OptionMemory: 
			if (robots.back()->dev_null)
				break; //TODO warning
			robots.back()->core->memory.realloc(value); //TODO skobtrolovat,ci to nepresvihava celkovy pocet
			robots.back()->variables();
			break;
		case OptionAttack:
			TEST("setting Attack x to:" << value ); 
			robots.back()->core->body->attack_ = value;
			break;
		case OptionDefense:
			TEST("setting defense to " << value ); 
			robots.back()->core->body->defense = value;
			break;
		case OptionMisilleAttack:
			TEST("setting Missille attack to " << value ); 
			robots.back()->getBody()->mAttack = value;
			break;
		case OptionMisilleHealth:
			TEST("setting Missille health to:" << value ); 
			robots.back()->getBody()->mHealth = value;
			break;
		case OptionStep:
			TEST("setting step to:" << value ); 
			robots.back()->core->body->default_steps = value;
			break;

	}
}

void Robot::error(unsigned line, ErrorCode e, std::string m)
{
	switch (e)
	{
		case WarningTargetNotFound:
			warning = true;
			warningList += "Line: " + deconvert<size_t>(line) + ", name of robot to kill ( " + m + ") not found\n";
			break;
		case WarningKillAlreadyDefined:
			warning = true;
			warningList += "Line:" + deconvert<int>(line) + ", ignoring, this kill was already defined\n";
			break;
		case WarningConversionToInt:
			warning = true;
			warningList += "Line:" + deconvert<int>(line) + ", conversion from real to int\n";
			break;
		case WarningRedefinedOption:
			warning = true;
			warningList += "Line:" + deconvert<int>(line) + ", option already defined, using new value\n";
		case ErrorVariableNotFound:
		case ErrorVariableNotDefined:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + ", variable " + m + " not defined\n";
			break;
		case ErrorToMuchInitializers:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + ", too much initializers\n";
			break;
		case ErrorTypeNotRecognized:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + ", type not recognized\n";
			break;
		case ErrorConversionImpossible:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + ", conversion impossible\n";
			break;
		case ErrorOperationNotSupported:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + ", operation is not supported\n";
			break;
		case ErrorWrongNumberOfParameters:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + ", wrong number of parameters\n";
			break;
		case ErrorFunctionNotDefined:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + ", function Not defined\n";
			break;
		case ErrorOutOfRange:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + ", type out of range\n";
			break;
			
		default:
			errors = true;
			errorList += "Line:" + deconvert<int>(line) + ", unrecognized error\n";
			break;
	}
}

void Robot::consolidate()
{
	if(!scheduller)
		scheduller = new SchedulleRound(); 
	std::vector<InstructionBreak *> breaks;
	std::vector<InstructionBegin *> begins;
	std::vector<InstructionContinue *> conts;
	std::vector<int> beg;
	for(size_t i =0; i<instructions.size(); i++) 
	{
		if (instructions[i] == NULL)
		{
			TEST("Null instruction, something forgotten?")
			continue;
		}
		TEST(i << instructions[i]->name()<<",..\t")
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
	instructions.push_back(new InstructionMustJump(-instructions.size()+find_f("main")->begin -1));
}
Robot::~Robot()
{
	if (scheduller)
		delete scheduller;
	if (core)
		delete core;
	if (dev_null)
		delete dev_null;
	if (nullable)
		delete nullable;
	if (defined_types)
		delete defined_types;


	//delete instructions

	TEST("Instuctions size:" << instructions.size() );
	for (size_t i = 0; i < instructions.size(); i++)
	{
		if (instructions[i] == NULL)
		{
			TEST("Eeeeek!") 
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
	Skin *ms = new MissilleSkin( name );
	mSkins.push_back(ms);
	return ms;
}

//zbytocne!
void Robot::setmSkin(Skin* mSkin)
{
	for(size_t i=0; i<missilles; i++)
	{
		Missille *m = new Missille(mSkin, core->body);
		core->body->addAmmo(m);
	}
}

bool Robot::skined()
{
	return core->body->hasSkin();
}
Robots::~Robots()
{
	clean();
}

void Robots::clean()
{
	parseErrorsList = "";
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
	resolveName.clear();
	resolveStart.clear();
	robots.clear();
}
/* error can occur before robot is created */
void Robots::parseError(std::string error)
{
	parseErrorsList += input + ":" + error;
}
