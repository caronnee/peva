#include "./parser_functions.h"

/* Maximalny pocet dimenzii u pola*/
#define MAX_DIMENSION 7 

void add_variables(Program *p, std::vector<Constr> s, Create_type t)
{
	for (int i =0; i< s.size(); i++)
	{
		p->add(s[i].id,t); //TODO checkovat, ci to preslo OK
	}
}
/*void add(Program * p, std::vector<std::string> n, Type t)
{
	for (int i =0; i< n.size(); i++)
	{
	}
}
void add(Program * p, std::vector<Node *> n, Type t)
{
	for (int i =0; i< n.size(); i++)
	{
		if ((n[i]->type!=TypeUndefined)&&(t == n[i]->type)) //ak bol typ pridany, skontroluj, ci sedi, ak nie, vyhod chybu
		{
			p->error = true;
			continue;
		}
		n[i]->type = t;
	}
}
void add(Program * p, std::string s, Type t)
{
	Node *n = p->add_string(s,t);
	n->type = t;//TODO zistit, ci sa etse niekde neschovava
}
void add(Program * p, std::string s, int value)
{
	Node *n = p->add_string(s,TypeInteger);
	n->IntegerValue = value;
}
void add(Program * p, std::string s, float value)
{	
	Node *n = p->add_string(s,TypeInteger);
	n->IntegerValue = value;
}
void add(Program * p, std::string s, Location point)
{
	Node * n = p->add_string(s, TypeLocation);
	n->LocationValue = point;
}
void set_element_type(Program *p, std::vector<Node *> arr, Type t)
{
	for (int i =0; i< arra.size(); i++)
	{
		arr[i].element_type = t; //TODO nejaka inicializacia
	}
}
Node * add_array(Program *p, std::string s)
{
	Node *n = p->add_string(s, TypeArray);
	n->array = new Array();
	n->array->range=255; //TODO definovana hodnota
	return n->array;
}
Node * add_array(Program *p, std::string s, std::vector<int> range, Type t)
{
	if (range.size()>MAX_DIMENSION)
		return NULL;
	Node* n = p->add_string(s, TypeArray);
	Node * p = new(s, t);
	for (int i = range.size()-1; ->=0; i--)
	{
		Node *p = create_array(range[i], p);
	}
	return n;
}

void create_array(Node *node, std::vector<int> range)
{
	if(range.size() == 1)
	{
		node->array = new Node(range[0]);
		for (int i =0; i< range[0]; i++)
		{
			n->array.elements[i]->type = TypeUndefined;//TODO nemuselo by tu byt
		}
	}	
}
/*void add_array(std::vector<Node *> nodes, Type t)
{
	Node * n;
	for (int i =0; i < nodes.size();i++)
	{
		n = nodes[i];
		int r = n->array->range[0]; //aspon 1 prvok to budem mat urcite
		for(int i =1; i< n->array->range.size(); i++)
			r*=n->array->range[i];
		n->array->values.resize(r,Node(n->name,t)); //tu sa to samozrejme inicializuje spravne
	}
}*/
Instruction * operRel(Operation op)
{
	switch(op)
	{
		case OperationLess:
			return new InstructionLt();
		case OperationLessEqual:
			return new InstructionLe();
		case OperationEqual:
			return new InstructionEqual();
		case OperationGreater:
			return new InstructionGt();
		case OperationGreaterEqual:
			return new InstructionGe();
		default: return NULL;
	}
}
