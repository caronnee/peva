#ifndef __LIST__
#define __LIST__

#include "objects.h"

struct Item
{
	Object * value;
	Item * next;
	Item * previous;
};

class List
{
	size_t size_;
	Item * tail;
public:
	List();
	Item * data;
	size_t size();
	void add(Object * data);
	void add(Item * data);
	void clear();
	bool remove(Object * data);
	void moveHead(List & dest);
	void next();
	void reset();
	Object * read();
};

#endif
