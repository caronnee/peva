#ifndef ___STACK___
#define ___STACK___
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include "./instructions.h"
#include "./tree.h"
#include "functions.h"
#include "targets.h"

#define DELIMINER_CHAR '#'
typedef std::vector<Instruction *> Instructions;
typedef std::vector<Value> Values;

struct Constr
{
	std::string id;
	Instructions ins;
	bool default_set;
	Constr();
	Constr(std::string a);
	Constr(std::string a, int def);
	Constr(std::string a, Instructions i);
};

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
	bool error;
	std::string nested;
	std::string name;

	
	std::list<TargetVisit *> targets;
	TargetKillNumber * toKill;

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
	Node * add(std::string name, Create_type t);
	Function * find_f(std::string s);
	void add(Instructions ins);
	Node * create_type(Type t);
	void enter(std::string s, Create_type t);
	void add_function(std::vector<Parameter_entry> c, Instructions ins);
	void leave();
	void execute();
	int last_loop_number;
	std::stack<int> loop_labels;
	void enter_loop();
	void end_loop();
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

struct StartPosition
{
	size_t ID;
	Position position;
};
struct Robots
{	
	GamePoints g;
	Robot * actualRobot;
	std::vector<Robot *> robots;
	Robots(GamePoints g);
	std::vector<StartPosition> startPositions; //najprv sa vygeneruje mapa, nacitaju sa start positions a potom sa spusti bison
	void createNew(std::string name);
	void set(Options op, size_t value);
	Position get_start_position(size_t ID);
};
#endif
