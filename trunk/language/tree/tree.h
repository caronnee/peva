#ifndef ___TREE___
#define ___TREE___
#include <list>
#include "node.h"

std::string quicksort(std::string s); // TODO template

struct Tree
{
	bool inner_node;
	int depth;
	Tree * next[256];//TODO dynamicke linkovanie
	std::list<Node *> items;//ukazatel z jednoducheho dovodu -> inak je to prasarna, vyparsovavat z listu:)
	Tree();
	Tree(int d);
private:
	void reset();
};
#endif
