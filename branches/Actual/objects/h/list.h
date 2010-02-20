#ifndef __LIST__
#define __LIST__

#include <cstdlib>

class Object;

struct Item
{
	Object * value;
	Item * next;
	Item * previous;
	Item(Object *);
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
	void moveHead(List & dest);
	void next();
	void clear();
	void reset();
	bool remove(Object * data);
	void remove(Item * data);
	bool empty();
	Object * read();
	~List();
};

#endif
