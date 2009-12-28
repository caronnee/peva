#include "../h/list.h"

List::List()
{
	data = new Item();
	data->value = NULL;
	data->next = data;
	data->previous = data;
	tail = data;
	size_ = 1;	
}
size_t List::size()
{
	return size_;
}
void List::add(Object* o)
{
	Item * i = new Item();
	i->next = data;
	i->previous = data->previous;
	data->previous->next = i;
	data->previous = i;
	i->value = o;
	size_++;
	data = i;
}
void List::clear()
{
	for (size_t i = 0;i<size_;i++)
	{
		Item * d = data;
		data = data->next;
		if (data->value==NULL)
			continue;
		delete d;
	}
	data->next =data;
	data->previous = data;
	size_ = 1;
}
bool List::remove(Object * o)
{
	for (size_t i = 0; i<size_;i++)
	{
		if(data->next->value == o)
		{
			Item * toDelete = data->next;
			data->next = toDelete->next;
			toDelete->previous->next = toDelete->next;
			delete toDelete;
			size_--;
			return true;
		}
	}
	return false;
}
void List::add(Item *item)
{
	item->next = tail->next;
	item->previous = tail;
	tail->next->previous = item;
	tail->next = item;
	size_++;
}

void List::moveHead(List & dest)
{
	Item * i = data;
	data = data->next;
	data->previous = i->previous;
	data->previous->next = data;
	dest.add(i);
	size_--;
}
void List::next()
{
	data = data->next;
}
void List::reset()
{
	data = tail;
}
Object * List::read()
{
	next();
	Object * o = data->value;
	return o;
}
bool List::empty()
{
	return !(size_ > 1);
}
List::~List()
{
	tail = NULL;
	delete data;
	size_ = 0;
}
