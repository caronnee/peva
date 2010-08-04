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
#include "../../scheduller/h/scheduller.h"

#define DELIMINER_CHAR '#'

struct MyXmlData
{
	xmlDocPtr doc;
	xmlNodePtr root_ptr;
	xmlNodePtr node;
};
class Robot
{

	/* name of the robot */
	std::string name;

	/* scheduller to be used */
	Scheduller * scheduller;

	/* in which input was robot defined, for determningt 
	 * namespace when target kill or start place  */
	std::string space;

	/* node used when an exception occurs in addig to tree */
	Node * nullableNode;

public:
	/* game points */
	GamePoints points;

	/* logical error codes */
	enum ErrorCode
	{
		WarningKillAlreadyDefined,
		WarningConversionToInt,
		WarningRedefinedOption,
		WarningTargetNotFound,
		WarningMalformedInteger,
		WarningMalformedReal,
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

	/* return nam of input where robot was created */
	std::string getSpace()const;

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
	Node * add(unsigned line, std::string name, Create_type * t);

	/* adds node under name name and assigns it undefined type */
	Node * add(unsigned line, std::string name);

	/* returns fnction with name s, NULL if none exists */
	Function * find_f(std::string s);

	/* adds instrction to stack */
	void add(Instructions ins);

	/* sets robot's state to state in function */
	void enter(std::string s, std::vector<Parameter_entry> p,Create_type *t);

	/* adds function to robot's function list */
	void add_function( unsigned line, Instructions ins);

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

public:
	/* core handling memory, periferies etc. */
	Core * core;

	/* name of the skin, usefil for determinin missiles skins*/	
	std::string skinName;

	/* constructor */
	Robot(std::string name, std::string space, GamePoints g);

	/* return complex information about robot */
	std::string info();
	
	/* sets robot to*/
	void init(int vis);

	/* returns simple type form container */
	Create_type * find_type(Type t);

	/* returns complex type form container, if none, creates one */
	Create_type * find_array_type(int range, Create_type * descend);

	/* remembers actal type as incomplete and for later finishing */
	void declare_type();

	/* same as type, bt for arays */
	void declare_next(unsigned line);

	/* removes last declared type and considers it as done*/
	void leave_type();

	/* sames to xml file 'machine.xml' */
	void save_to_xml();

	/* sets main skin */
	void setSkin(Skin * a);

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
	OptionMissilles
};

struct ResolveName
{
	Robot * robot;
	std::string prefix; //koho ma killnut
	std::string name; //koho ma killnut
	size_t line;
};
struct ResolveStart
{
	TargetVisit * target;
	std::string prefix; //koho ma killnut
	std::string name;
	size_t line;
};

struct Robots
{	
	/* gamepoints global */
	GamePoints points;

	/* which input is being processed */
	std::string input;

	/* resolves every not resolved question, like start etc. */
	void resolve();

	/* function destroying any mess that could remain */
	void clean();

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

	/* creste new empty robot */
	void createNew(std::string name);

	/* sets robot option*/            //TODO premistnit do robota
	void set(Options op, size_t value);

	/* sets for function, removes temporarily values etc. */
	void finalize(int mapVisbility);

	/* add skins to already loaded skins witout duplicities */
	Skin * addSkin(std::string name);

	/* warns that input fle is not in right format */
	void parseError(std::string error);

	/* string about parse errors */
	std::string parseErrorsList;

	/* string about parse warnings */
	std::string parseWarningList;
	
	/* destructor */
	~Robots();
};
#endif
