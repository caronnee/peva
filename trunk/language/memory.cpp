#include "memory.h"
#include "types.h"

Variable * Memory::next_id(size_t ID)
{
	for(size_t i = position; i<memory_size; i++) 
	{
		if (memory[i]->owner == (size_t)-1 )
		{
			memory[i]->owner = ID;
			return memory[i];
		}
	}
	for(size_t i =0; i<position; i++) 
	{
		if (memory[i]->owner == (size_t)-1)
		{
			memory[i]->owner = ID;
			return memory[i];
		}
	}
	int id = rand()%memory_size;
	return memory[id];
}

Memory::Memory(int size)
{
	memory_size = size;
	position = 0;
	srand(time(NULL));
	memory = new Variable*[size];
	for(int i =0; i< size; i++)
		memory[i] = new Variable();
}

Variable * Memory::assign(Create_type type, size_t id, size_t depth_)
{
	Memory_record m;
	m.variable = find_free(type, id);
	m.depth = depth_;
	assigned.push_back(m);
	std::cout << "assignovane #elements:" << m.variable->array.elements.size() << std::endl;
	return m.variable;
}

Variable * Memory::assign_temp(Create_type t)
{
	Variable * v = find_free(t, 0); // 0 ako temprarily, TODO dat to nodes
	temp.push(v);
	return v;
}
void Memory::set_free(Variable * v)
{
	std::stack<Variable *> vars;
	vars.push(v);
	Variable * tmp;
	while(!vars.empty())
	{
		tmp = vars.top();
		tmp->owner = -1;
		vars.pop();
		for(size_t i =0; i<tmp->array.elements.size(); i++)		 
		{
			vars.push(tmp->array.elements[i]);
		}
		tmp->array.elements.clear();
	}
}

void Memory::free_tmp()
{
	if (temp.size()>0)
	{
		set_free(temp.front());	
		temp.pop();
	}
	else
		std::cout <<"Error! Trying to free a nonempty temp" << std::endl;
}
void Memory::fill(Variable * &v, 
		  Create_type & t, 
		  std::stack<Variable *> &variables_to_assign, 
		  std::stack<Create_type> & types_to_assign,
		  size_t ID)
{
	if (!t.is_simple())
	{
		Variable * tmp = NULL;
		for(int i =0; i<t.range; i++) 
		{
			tmp = next_id(ID);
			if (!t.element().is_simple())
			{
				types_to_assign.push(t.element());
				variables_to_assign.push(tmp);
			}
			v->array.elements.push_back(tmp);
		}
		for(size_t i =0; i<t.nested_vars.size(); i++) 
		{
			tmp = next_id(ID);
			if (!t.is_simple())
			{
				types_to_assign.push(t.nested_vars[i].type);
				variables_to_assign.push(tmp);
			}
			v->array.elements.push_back(tmp);
		}

	}
}

Variable * Memory::find_free(Create_type t, size_t ID)
{
	//bez rekurzie pre istotu
	std::stack<Create_type> types_to_assign;
	std::stack<Variable *> variables_to_assign;
	Variable * v = next_id(ID);
	Variable * ret_v = v;
	variables_to_assign.push(v);

	fill(v,t, variables_to_assign, types_to_assign, ID);

	while(!types_to_assign.empty())
	{
		t = types_to_assign.top();
		types_to_assign.pop();
		v = variables_to_assign.top();
		variables_to_assign.pop();
		fill(v,t,variables_to_assign, types_to_assign, ID);
	}
	return ret_v;
}

void Memory::free(size_t depth)
{
	while((!assigned.empty())&&(assigned.back().depth >= depth))
	{
		Memory_record r = assigned.back();
		assigned.pop_back();
		set_free(r.variable); //TODO pre velke arrays a pod. to nejak penalizovat?
	}
	std::cout << "Memory freed"<< std::endl;
}

void Memory::realloc(int size)
{
	if (memory)
		delete memory;
	memory_size = size;
	memory = new Variable*[size];
	for(int i =0; i< size; i++)
		memory[i] = new Variable();
}

Variable * Memory::random()
{
	return memory[rand()%memory_size];
}
