#ifndef ___STACK___
#define ___STACK___
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
struct Robot 
{
	enum ErrorCode
	{
		WarningKillAlreadyDefined,
		WarningConversionToInt,
		WarningRedefinedOption,
		WarningQouOfRange,
		ErrorVariableNotDefined,
		ErrorToMuchInitializers,
		ErrorTypeNotRecognized,
		ErrorConversionImpossible,
		ErrorVariableNotFound,
		ErrorOperationNotSupported,
		ErrorWrongNumberOfParameters,
		ErrorFunctionNotDefined,
		ErrorOutOfRange
	};
	bool errors;
	bool warning;
	std::string errorList;
	std::string warningList;
	std::string nested;
	std::string name;
	
	Create_type * find_type(Type t);
	Create_type * find_array_type(int i, Create_type * t);

	std::list<TargetVisit *> targets;
	TargetKillNumber * toKill;

	std::vector<Create_type *> defined_types;
	Tree defined;//root burst stromu
	Instructions instructions; //kopa predefinovanych instrukcii
	Values values;//stack ukazatelov do stromu
	MyXmlData data;
	void save_to_xml();
	Robot(std::string name, GamePoints g);
	Core * core;
	void add_global(Instructions ins);
	void output(Tree * t);
	Node * find_var(std::string);
	/* Vracia, ci sa podarilo pridat alebo nie*/
	Node * add(std::string name, Create_type * t);
	Function * find_f(std::string s);
	void add(Instructions ins);
	Node * create_type(Type t);
	void enter(std::string s, Create_type *t);
	void add_function(std::vector<Parameter_entry> c, Instructions ins);
	void leave();
	void execute();
	int last_loop_number;
	std::stack<int> loop_labels;
	void enter_loop();
	void end_loop();
	void addKilled(unsigned l,Operation op, size_t number);
	void addVisit(std::vector<Position> pos);
	void addVisitSeq(std::vector<Position> pos);
	void error(unsigned int line, ErrorCode c,std::string message="");
private:
	Robot_body * body;
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

struct Robots
{	
	GamePoints g;
	Robot * actualRobot;
	std::vector<Robot *> robots;
	Robots(GamePoints g);
	void createNew(std::string name);
	void set(Options op, size_t value);
};
#endif