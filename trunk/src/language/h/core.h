#ifndef ___CORE____
#define ___CORE____

#include "memory.h"
#include "variable.h"
#include "functions.h"
#include "typeContainer.h"
#include "../../objects/h/body.h"

typedef std::vector<Variable *> Values;

struct Core
{
	/* variable that should be remembered for later */
	Variable *savedVar;

	/* types alredy defined */
	TypeContainer * typeContainer;

	/* program couter */
	size_t PC;

	/* return proram counter after finishing function */
	std::vector<size_t> PCs;

	/* function actually in process */
	Function * nested_function;

	/* function already defined */
	std::vector<Function *> functions;

	/* functions in process */
	std::vector<Function *> nested_functions;

	/* how many beginblock have we entered and not left */
	int depth;

	/* body controlled by core */
	Body * body; //periferie, stav robota, interakcia s mapou

	/* nody memory */
	Memory memory;

	/* variables loaded */
	Values values;	

	/* jump to new function */
	void save(int j);

	/* returns from function */
	void restore(); 

	/* returns variable from stack */
	Variable * getVariableFromStack();        
                                                  
	/* returns variable from stack */
	int getIntFromStack();                    
                                                  
	/* returns variable from stack */
	float getFloatFromStack();

	/* returns object from stack */
	Object * getObjectFromStack();

	/* loads array element, if any, else loads dev_null */
	void loadElement(int range);

public:
	/* contructor */
	Core(TypeContainer *t);

	/* load a variable onto stack */
	void addValue(Variable * v);

	/* performs integer assign */
	void saveInteger();

	/* performs float assign */
	void saveFloat();

	/* performs object assign */
	void saveObject();

	/* optimalization when assigning arrays and structs with temporal */
	void switchVariable();

	/* deprecated, not save against copying the same variable */
	void copyVariable();

	/* detructor */
	~Core();
};
#endif
