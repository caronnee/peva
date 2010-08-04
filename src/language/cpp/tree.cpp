#include <cstdio>
#include <iostream>
#include "../h/tree.h"
#include "../../add-ons/h/macros.h"

void Tree::reset()
{
	alphabet = quicksort("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._");
	number_of_nodes = 0;
	inner_node = false;
	depth = 0;
	for (int i =0; i< 256; i++)
	{
		if (next[i])
			delete next[i];
		next[i] = NULL;
	}
	while (!items.empty())
	{
		delete (*(items.begin()));
		items.pop_front();
	}
	block_of_nodes.clear();
}

void Tree::new_block()
{
	block_of_nodes.push_back(NULL);
}

void Tree::leave_block()
{
	while(!block_of_nodes.empty() && (block_of_nodes.back()!=NULL))
	{
		block_of_nodes.back()->active = false;
		block_of_nodes.pop_back();
	}
	if (!block_of_nodes.empty())
		block_of_nodes.pop_back();
}
Tree::Tree()
{
	for (size_t i = 0; i< ASCII_NUMBER; i++)
		next[i] = NULL;
	reset();
}
Tree::Tree(int d)
{
	for (size_t i = 0; i< ASCII_NUMBER; i++)
		next[i] = NULL;
	reset();
	depth = d;
}

int Tree::find_index(char a)
{
//	TEST(alphabet)
	int max = alphabet.length()-1; //za hranicu uz nesmie skocit
	int min = 0; //zaciatok
	int index = (max-min)/2;
	TEST(alphabet)
//	TEST(min << " " << index <<" " << max)
	while ((max-min)>1) //ked uz je jedna, presli sme vsetko a nie je tam
	{
		if (alphabet[index] == a)
			return index;
		if (alphabet[index] > a)
		{
			max = index; //viac ako za indexom to nebude
			index-=(max-min)/2;
		}
		if (alphabet[index] < a)
		{
			min = index;
			index+=(max-min)/2;
		}
//		TEST(alphabet[min] << " " << alphabet[index] <<" " << alphabet[max])
	}
//	TEST("OUT")
	if (alphabet[min] == a)
		return min;
	if (alphabet[max] == a)
		return max;
	TEST("ALLERT:not found")
	return -1; //nenasiel sa 
}

std::string quicksort(std::string s)
{
	if (s.length()<=1)
		return s;
	std::string s1 ="",s2 ="";
	for (size_t i =1; i< s.length();i++)
		if (s[i] < s[0]) s1+=s[i];
		else s2+=s[i];
	return quicksort(s1) + s[0] + quicksort(s2);
}
Tree * Tree::find_string(std::string s)
{
	Tree* t  = this;
	size_t i =0;
	while (t->inner_node == true)
	{
		int pointer = find_index(s[i]);
		if (t->next[pointer]==NULL)
		{
			t->next[pointer] = new Tree(t->depth+1);
		}
		t = t->next[pointer];
		i++;
		if (i == s.length())
			break;
	}
	return t;
}

Node * Tree::find(std::string name)
{
	Tree * t = find_string(name);
	std::list<Node*>::iterator iter;
	for (iter = t->items.begin(); 
			iter!=t->items.end(); 
			iter++)
	{
		if ((*iter)->name == name)
			return *iter;
	}
	return NULL;
}

Node * Tree::add(std::string s, Create_type * type)
{
	TEST("pridavam meno:" << s << " typu "<< type->type)
	Tree * t = find_string(s);//pridavame do tohoto kontejnera
	std::list<Node*>::iterator iter;
	for (iter = t->items.begin(); 
			iter!=t->items.end(); 
			iter++)
	{
		if ((*iter)->name == s)
		{
			if ((*iter)->active)
			{
				throw "Such variable already exists! (" + s + ")";
			}
			if ((*iter)->type_of_variable != type )
			{
				throw "Variable is not active but types are different! It's a bug. Please contact me!";
			}
			return *iter;
		}

	} //TODO nejaka rozumnejsia metoda

	number_of_nodes++;
	Node * nod = new Node(s, type, number_of_nodes);
	if (s.find(DELIMINER_CHAR) == std::string::npos)
	{
		nod->nested = Global;
	}
//	TEST("adresa" << nod)
	bool nested = false;
	for (size_t i =0; i< s.length(); i++)
	{
		if (s[i] == DELIMINER_CHAR)
		{
			nested = true;
			break;
		}
			
	}
	if (nested)
		nod->nested = Local;
	t->items.push_back(nod);
	//TODO else warning o preskakovani alebo prepisana hodnota alebo cos
	while(t->items.size()> MaxItems ) //pre opakovane stiepenie
	{
		t->inner_node = true;
		int splitted = -1,split = 0;
		std::list<Node *> n;
		while (!(t->items.empty()))
		{
			if (t->items.front()->name.length() == t->depth) //ak sa neda dalej
			{
				split++;//TODO ocheckovat
				n.splice(n.begin(),t->items,t->items.begin());
				continue;
			}
			int pointer = find_index(t->items.front()->name[t->depth]);
//			TEST(t->items.front()->name[t->depth] << "$:"<<pointer)
		 	if (t->next[pointer]==NULL) //
			{
			//	TEST("splittling")
				split++;
				splitted = pointer;
				t->next[pointer] = new Tree(t->depth+1);
			}
			
			Tree * nxt = t->next[pointer];
			nxt->items.splice(nxt->items.begin(),t->items,t->items.begin());
		}
//		TEST(" enddd"<<n.size())
		t->items.swap(n);
		if ( split == 1 )
		{
			//TEST("repete! " <<splitted)
			t = t->next[splitted];
		}
	}
	nod->active = true;
	block_of_nodes.push_back(nod);
	//TEST("adresa return " << nod)
	return nod;
}
Tree::~Tree()
{
	reset();
}
