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
	TypeContainer * typeContainer;
	size_t PC;
	std::vector<size_t> PCs;
	Function * nested_function;
	std::vector<Function *> functions;
	std::vector<Function *> nested_functions;
	int depth;
	bool error;
	Body * body; //periferie, stav robota, interakcia s mapou
	Memory memory;
	Values values;	
	void save(int j);
	void restore(); //+ pushnut vsetky parametre zadanej funkcie o jedno

	Variable * getVariableFromStack();
	int getIntFromStack();
	float getFloatFromStack();
	Object * getObjectFromStack();
	void loadElement(int range);
public:
	Core(TypeContainer *t);
	void saveInteger();
	void saveFloat();
	void saveObject();
	void switchVariable();
	void copyVariable();
	~Core();
};
#endif
