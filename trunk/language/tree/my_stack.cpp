#include "my_stack.h"
#include <iostream>

#define MaxItems 3
Program::Program()
{
	alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._";//vsetky znaky, co a poauzivame v identifikatoroch
	alphabet = quicksort(alphabet);//zasortime aby sme mohli pouzivat pulenie intervalu
	error = false;//TODO pridat errorou hlasku
}
int Program::find_index(char a)
{
	int max = alphabet.length()-1; //za hranicu uz nesmie skocit
	int min = 0; //zaciatok
	int index = (max-min)/2;
	std::cout << alphabet <<std::endl;
//	std::cout << min << " " << index <<" " << max <<std::endl;
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
//		std::cout << alphabet[min] << " " << alphabet[index] <<" " << alphabet[max] <<std::endl;
	}
//	std::cout << "OUT" << std::endl;
	if (alphabet[min] == a)
		return min;
	if (alphabet[max] == a)
		return max;
	return -1; //nenasiel sa 
}
Tree * Program::find_string(std::string s)
{
	Tree* t  = &defined;
	int i =0;
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
/*
 *Vracia ukazovatel na samotny uzzol, ktory skryva hodnotu, v ktorom je ulozena nasa hodnota
 */
bool Program::add(std::string s, Node *n)
{
	Tree * t = find_string(s);//pridavame do tohoto kontejnera
	n->name = s;
	std::cout << "\t" << s <<std::endl; 
	std::list<Node*>::iterator iter;
	for (iter = t->items.begin(); 
		iter!=t->items.end(); 
		iter++)
	{
		if ((*iter)->name == s) {

			std::cout << "uz tam je "<< s <<std::endl;
			exit(5);
		}//kontrola, co tam nieco take uz nie je

	} //TODO zatial to bolo naprosto nanic
	t->items.push_back(n);
	//TODO else warning o preskakovani alebo prepisana hodnota alebo cos
	while(t->items.size()> MaxItems ) //pre opakovane stiepenie
	{
		//burst!
		t->inner_node = true;
		int splitted = -1,split = 0;
		std::list<Node *> n;
		while (!(t->items.empty()))
		{
			std::cout <<t->items.size() <<" : "<< t->items.front()->name<< std::endl;
//			getc(stdin);
			if (t->items.front()->name.length() == t->depth) //ak sa neda dalej
			{
				split++;//TODO ocheckovat
				n.splice(n.begin(),t->items,t->items.begin());
				continue;
			}
			int pointer = find_index(t->items.front()->name[t->depth]);
		 	if (t->next[pointer]==NULL) //
			{
				split++;
				splitted = pointer;
				t->next[pointer] = new Tree(t->depth+1);
			}
			Tree * nxt = t->next[pointer];
			nxt->items.splice(nxt->items.begin(),t->items,t->items.begin());
		}
		std::cout <<" enddd"<<n.size();
		t->items.swap(n);
		if ( split == 1 )
		{
			std::cout <<"repete! " <<splitted << std::endl;
			t = t->next[splitted];
		}
	}
	return true;
}
void Program::output(Tree * t)
{
	for (std::list<Node*>::iterator i = t->items.begin();i!=t->items.end(); i++)
		std::cout << "prvok s menom:" << (*i)->name <<std::endl;
	for (int i = 0; i < 256; i++)
	{
		if (t->next[i]!=NULL)
		{
			std::cout << "Down:" <<i << std::endl;
			output(t->next[i]);
			std::cout << "UP!" << std::endl;
		}
	}
	std::cout << "END "<<std::endl;
}
