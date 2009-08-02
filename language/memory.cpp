#include "memory.h"
#include "types.h"

Variable * Memory::assign(Create_type type,size_t id__, size_t depth_)
{
	int id = id_free_vars.top();
	std::cout << "assigning " << id << std::endl;
	id_free_vars.pop();
	Memory_record record;
	record.owner = id__;
	record.depth = depth_;
	record.variable = memory[id];
	record.id = id;
	memory[id]->owner = id__;
	if (is_simple(type.type))
	{
		memory[id]->set_variable(type.type);
		return memory[id];
	}
	if (type.type == TypeArray)
	{
		memory[id]->array->elements.clear();
		for(int i =0; i< type.range; i++)
		{
			memory[id]->array->elements.push_back(assign(*type.data_type, id__, depth_));
		}
		return memory[id];
	}
	return NULL;
}
void Memory::free(size_t depth)
{
	while((!assigned.empty())&&(assigned.back().depth == depth))
	{
		Memory_record r = assigned.back();
		assigned.pop_back();
		id_free_vars.push(r.id);
		std::cout << "dealok " << r.id << std::endl;
		r.variable->owner = -1;
	}
}
Memory::Memory(int size)
{
	memory = new Variable*[size];
	for(int i =0; i< size; i++)
		memory[i] = new Variable();
	for(int i =0; i< size; i++)
		id_free_vars.push(i);
}
