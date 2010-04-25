#ifndef __LIST__
#define __LIST__
//TODO templata
#include <cstdlib>
#include <vector>

class Object;

struct Item
{
	Object * value;
	Item * next;
	Item * previous;
	Item(Object *);
};
struct SharedData
{
	int pointers;
	std::vector<Object *> list;
};

class List
{
	size_t size_;
	Item * tail;
public:
	List();
	Item * data;
	size_t size();
//	void add(Object * data);
	void add(Item * data);
	void moveHead(List & dest);
	void next();
	void clear();
	void reset();
	bool remove(Object * o);
	void remove();
	bool empty();
	Object * read();
	~List();
};

#endif