#ifndef ___CORE____
#define ___CORE____

struct Value
{
	Variable hlp;
	Variable * loaded;
};

struct Core
{
	size_t PC;
	int depth;
//	Robot * R; //periferie, stav robota, interakcia s mapou
//	Map * map;
	Memory M;
	std::vector<Values> values;	
};
#endif
