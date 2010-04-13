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
	/* number of fll missilles */
	size_t missilles;

	/* name of the robot */
	std::string name;

	/* scheduller to be used */
	Scheduller * scheduller;

public:

	/* logical error codes */
	enum ErrorCode
	{
		WarningKillAlreadyDefined,
		WarningConversionToInt,
		WarningRedefinedOption,
		WarningTargetNotFound,
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

	/* returns name of robot, should be name */
	std::string getName()const;

	/* node accepting every vale for wrong access */
	Node * dev_null;

	/* acces for NULL */
	Object * nullable;

	/* flags if there asre errors */
	bool errors;

	/* flags if there are warnings */
	bool warning;

	/* if errors, detail information */
	std::string errorList;

	/* if warnings, detail information */
	std::string warningList;

	/* string descibing stack of functions */ //TODO needed?
	std::string nested;
	
	/* container for defined types */
	TypeContainer * defined_types;

	/* tree holding veriables defined by string */
	Tree defined;

	/* instructions to be done */
	Instructions instructions; 

	/* results inf instruction */
	Values values;

	/* for savin to xml docment */ //TODO iba lokalne?
	MyXmlData data;

	/* sets which scheduler to be used */
	void setScheduler(int type, const std::vector<int>& penals);

	/* adds global instruction and set initial PC */
	void add_global(Instructions ins);

	/* prints tree to standart output */
	void output(Tree * tree);

	/* finds node in tree, if none, returns NULL */
	Node * find_var(std::string s, bool & b);

	/* adds node in tree with type t and under name name*/
	Node * add(std::string name, Create_type * t);

	/* adds node under name name and assigns it undefined type */
	Node * add(std::string name);

	/* returns fnction with name s, NULL if none exists */
	Function * find_f(std::string s);

	/* adds instrction to stack */
	void add(Instructions ins);

	/* sets robot's state to state in function */
	void enter(std::string s, std::vector<Parameter_entry> p,Create_type *t);
	/* adds function to robot's function list */
	void add_function( Instructions ins);

	/* leaves function */
	void leave();

	/* execute instructions in loop */
	void execute();

	/* execte actual instruction */
	bool action(bool & areConditionsFulfilled);

	/* handling errors occured in bison */
	void error(unsigned int line, ErrorCode c,std::string message="Unrecognized");
	/* sets instruction in right order */
	void consolidate();

	/* declared types */
	std::stack<Create_type *> active_type;

	/* last declared type, type of variables following */
	Create_type * last_type;

	/* misille parameters */
	size_t mAttack,mHealth;
public:
	/* core handling memory, periferies etc. */
	Core * core;

	/* name of the skin, usefil for determinin missiles skins*/	
	std::string skinName;

	/* constructor */
	Robot(std::string name, GamePoints g);
	
	/* returns simple type form container */
	Create_type * find_type(Type t);

	/* returns complex type form container, if none, creates one */
	Create_type * find_array_type(int range, Create_type * descend);

	/* remebers actal type as incomplete and for later finishing */
	void declare_type();

	/* same as type, bt for arays */
	void declare_next();

	/* removes last declared type and considers it as done*/
	void leave_type();

	/* sames to xml file 'machine.xml' */
	void save_to_xml();

	/* sets main skin */
	void setSkin(Skin * a);

	/* sets missiles skins */
	void setmSkin(Skin * a);

	/* returns flag if the robot has been assigned a skin */
	bool skined();

	/* recreating defalt variables, sch as this null etc. */
	void variables();

	/* return body that robot controls */
	Body * getBody();

	/* desctructor */
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
	size_t line;
};
struct ResolveStart
{
	TargetVisit * target;
	std::string name;
	size_t line;
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

	/* target robots start positions unknown in processing time */
	std::vector<ResolveStart> resolveStart;

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
