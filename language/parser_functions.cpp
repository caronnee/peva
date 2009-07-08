#include "./tree/my_stack.h"

void add(Program * p, std::vector<std::string> n, Type t)
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
Node * add_array(Program *p, std::string s)
{
	Node *n = p->add_string(s, TypeArray);
	n->array = new Array();
	n->array->range=255; //TODO definovana hodnota
	return n;
}
/*Node * add_array(Program *p, std::string s, std::vector<int> range, Type t)
{
	Node* n = p->add_string(s, TypeArray);
	n->array = new Array();
	;
	return n;
}*/
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
