#ifndef ___TREE___
#define ___TREE___
#include <list>
#include <string>
#include "node.h"

#define DELIMINER_CHAR '#'
#define MaxItems 3

std::string quicksort(std::string s); // TODO template

struct Tree
{
	std::string alphabet;
	bool inner_node;
	size_t depth;
	Tree * next[256];//TODO dynamicke linkovanie
	std::list<Node *> items;//ukazatel z jednoducheho dovodu -> inak je to prasarna, vyparsovavat z listu:)
	Tree();
	Tree(int d);
	Tree * find_string(std::string a);
	int find_index(char a);
	Node * add(std::string s, Create_type type);
private:
	void reset();
};
#endif
