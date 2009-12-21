#include "../h/list.h"

List::List()
{
	items = new Item();
	items->data = NULL;
	items->next = items;
	items->previous = items;
	tail = items;
	size_ = 1;	
}
size_t List::size()
{
	return size_;
}
void List::add(Object* o)
{
	Item * i = new Item();
	i->next = items;
	i->previous = items->previous;
	items->previous->next = i;
	items->previous = i;
	i->data = o;
	size_++;
	items = i;
}
void List::clear()
{
	for (size_t i = 0;i<size_;i++)
	{
		Item * d = items;
		items = items->next;
		if (items->data==NULL)
			continue;
		delete d;
	}
	items->next =items;
	items->previous = items;
	size_ = 1;
}
bool List::remove(Object * o)
{
	for (size_t i = 0; i<size_;i++)
	{
		if(items->next->data == o)
		{
			Item * toDelete = items->next;
			items->next = toDelete->next;
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
	Item * i = items;
	items->previous->next = items->next;
	i->next->previous = i->next;
	dest.add(i);
	size_--;
}
void List::next()
{
	items = items->next;
}
