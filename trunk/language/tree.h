#ifndef __TREE_____
#define __TREE_____

#include <list>
#include "node.h"

#define DELIMINER_CHAR '#'
#define MaxItems 33
#define ASCII_NUMBER 256

std::string quicksort(std::string s); // TODO template

struct Tree
{
	int number_of_nodes;
	std::vector<Node *> block_of_nodes;
	std::string alphabet;
	bool inner_node;
	size_t depth;
	Tree * next[ASCII_NUMBER];//TODO dynamicke linkovanie
	std::list<Node *> items;//ukazatel z jednoducheho dovodu -> inak je to prasarna, vyparsovavat z listu:)
	Tree();
	Tree(int d);
	Tree * find_string(std::string a);
	int find_index(char a);
	Node * add(std::string s, Create_type* type);
	void new_block();
	void leave_block();
private:
	void reset();
public:
	~Tree();
};

#endif
