#ifndef ____ROBOT____
#define ____ROBOT____

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include "instructions.h"
#include "tree.h"
#include "functions.h"
#include "targets.h"
#include "enums.h"
#include "parser_classes.h"
#include "typeContainer.h"
#include "../../graphic/h/images.h"
#include "../../objects/h/objects.h"
#include "../../objects/h/missille.h"
#include "../../scheduller/h/scheduller.h"

#define DELIMINER_CHAR '#'

struct FirstSection
{
	int hitpoints;
	int sizeOfMemory;
	int seeX, seeY;
	FirstSection();
};
struct SecondSection
{
	int missileAttack;
	int missileDefense;
	int defense;
	int attack;
	SecondSection();
};
struct GamePoints
{
	FirstSection firstSection;
	SecondSection secondSection;
};
struct MyXmlData
{
	xmlDocPtr doc;
	xmlNodePtr root_ptr;
	xmlNodePtr node;
};
class Robot
{
	size_t missilles;
public:
	enum ErrorCode
	{
		WarningKillAlreadyDefined,
		WarningConversionToInt,
		WarningRedefinedOption,
		ErrorVariableNotDefined,
		ErrorToMuchInitializers,
		ErrorTypeNotRecognized,
		ErrorConversionImpossible,
		ErrorVariableNotFound,
		ErrorOperationNotSupported,
		ErrorWrongNumberOfParameters,
		ErrorFunctionNotDefined,
		ErrorBreak,
		ErrorContinue,
		ErrorOutOfRange
	};

	Node * dev_null;
	Object * nullable;
	bool errors;
	bool warning;
	std::string errorList;
	std::string warningList;
	std::string nested;
	std::string name;
	
	std::list<TargetVisit *> targets;
	TargetKillNumber * toKill;
	std::vector<size_t> killTarget;

	TypeContainer * defined_types;

	Tree defined;//root burst stromu
	Instructions instructions; 
	Values values;
	MyXmlData data;

	Scheduller * scheduller;
	Core * core;
	void add_global(Instructions ins);
	void output(Tree * t);
	Node * find_var(std::string s, bool & b);
	/* Vracia, ci sa podarilo pridat alebo nie*/
	Node * add(std::string name, Create_type * t);
	Node * add(std::string name);
	Function * find_f(std::string s);
	void add(Instructions ins);
	Node * create_type(Type t);
	
	void enter(std::string s, std::vector<Parameter_entry> p,Create_type *t);
	void add_function( Instructions ins);
	void leave();
	void execute();
	virtual void action();
	void addKilled(unsigned l,Operation op, size_t number);
	void addVisit(std::vector<Position> pos);
	void addVisitSeq(std::vector<Position> pos);
	//TODO zmenit na hlasky, co budu statcike a nie dynamicke
	void error(unsigned int line, ErrorCode c,std::string message="Unrecognized");
	void consolidate();
	//TODO tot by mohlo byt tiez typeContainer?
	std::stack<Create_type *> active_type;
	Create_type * last_type;
public:
	
	std::string skinName;
	Robot(std::string name, GamePoints g);
	Robot();
	
	Create_type * find_type(Type t);
	Create_type * find_array_type(int range, Create_type * descend);
	void declare_type();
	void declare_next();
	void leave_type();
	void save_to_xml();
	void add_kill(size_t id);
	void setSkin(Skin * a);
	void setmSkin(Skin * a);
	bool skined();
	Body * getBody();
	~Robot();
};

enum Options
{
	OptionHealth,
	OptionSeeX,
	OptionSeeY,
	OptionSee,
	OptionMemory,
	OptionAttack,
	OptionDefense,
	OptionMisilleAttack,
	OptionMisilleHealth,
	OptionId
};

struct ResolveName
{
	Robot * robot;
	std::string name; //koho ma killnut
};

struct Robots
{	
	GamePoints g;
	Robot * actualRobot;
	std::vector<Robot *> robots;
	std::vector<ResolveName> resolveName;
	Robots(GamePoints g);
	Robots();

	std::stack<std::string> resolveKill;
	std::vector<Skin *> skins;
	std::vector<Skin *> mSkins;

	void createNew(std::string name);
	void set(Options op, size_t value);
	void checkSkins();
	Skin * addSkin(std::string name);
	Skin * addmSkin(std::string name);
	~Robots();
};
#endif
