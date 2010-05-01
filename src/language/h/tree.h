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
	/* Block of nodes that are active */
	std::vector<Node *> block_of_nodes;
	std::string alphabet;
	bool inner_node;
	size_t depth;
	Tree * next[ASCII_NUMBER];//TODO dynamicke linkovanie
	std::list<Node *> items;
	Tree * find_string(std::string a);
	int find_index(char a);

private:
	/* for splitting decisions */
	int number_of_nodes;

	/* removes nodes and cleas tree */
	void reset();

public:
	/* constructor */
	Tree();

	/* constructor trree in depth @depth */
	Tree(int depth);

	/* creates a block to to filled with new active nodes */
	void new_block();

	/* sets a block of recently defined nodes as inactive */
	void leave_block();

	/* add a record to a tree with create type */
	Node * add(std::string s, Create_type* type);

	/* finds a node previous defined, null if not defined */
	Node * find(std::string s);

	/* destructor */
	~Tree();
};

#endif
