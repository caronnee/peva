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
	std::string name;
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

	std::string getName()const;
	Node * dev_null;
	Object * nullable;
	bool errors;
	bool warning;
	std::string errorList;
	std::string warningList;
	std::string nested;
	
	TypeContainer * defined_types;

	Tree defined;//root burst stromu
	Instructions instructions; 
	Values values;
	MyXmlData data;

	void setScheduler(int type, const std::vector<int>& penals);
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
	bool action(bool & areConditionsFulfilled);
	//TODO zmenit na hlasky, co budu statcike a nie dynamicke
	void error(unsigned int line, ErrorCode c,std::string message="Unrecognized");
	void consolidate();
	//TODO tot by mohlo byt tiez typeContainer?
	std::stack<Create_type *> active_type;
	Create_type * last_type;
public:
	
	std::string skinName;
	Robot(std::string name, GamePoints g);
	
	Create_type * find_type(Type t);
	Create_type * find_array_type(int range, Create_type * descend);
	void declare_type();
	void declare_next();
	void leave_type();
	void save_to_xml();
	void setSkin(Skin * a);
	void setmSkin(Skin * a);
	bool skined();

	void variables();
	Body * getBody();
	size_t mAttack,mHealth;
	~Robot();
};

enum Options
{
	OptionHealth,
	OptionSee,
	OptionMemory,
	OptionAttack,
	OptionStep,
	OptionDefense,
	OptionMisilleAttack,
	OptionMisilleHealth,
};

struct ResolveName
{
	Robot * robot;
	std::string name; //koho ma killnut
};

struct Robots
{	
	/* which input is being processed */
	std::string input;

	/* gamepoints to be rearranged */
	GamePoints g;

	/* function destroying any mess that could remain */
	void clean();

	/* targets that are unknown in processing time */
	std::vector<Target *> resolveTargets;

	/* robots already processed */
	std::vector<Robot *> robots;

	/* target robots names unknoewn in processing time */
	std::vector<ResolveName> resolveName;

	/* contructor */
	Robots();
	
	/* skins for robot */
	std::vector<Skin *> skins;

	/*missile sin, actually not used */
	std::vector<Skin *> mSkins;

	/* creste new empty robot */
	void createNew(std::string name);

	/* sets robot option*/            //TODO premistnit do robota
	void set(Options op, size_t value);

	/* sets for function, removes temporarily values etc. */
	void finalize();

	/* add skins to already loaded skins witout duplicities */
	Skin * addSkin(std::string name);

	/* add missiles skins to already loaded skins witout duplicities */
	Skin * addmSkin(std::string name);

	/* warns that input fle is not in right format */
	void parseError(std::string error);

	/* string about parse errors */
	std::string parseErrorsList;

	/* destructor */
	~Robots();
};
#endif
