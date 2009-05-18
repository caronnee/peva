#include "my_stack.h"
#include <iostream>

Instruction::Instruction(InstructionType t, std::string p)
{
	instruction = t;
	parameter = p;
}
Node::Node() //toto sa normalne nebude pouzivat
{
	last_access = 0;
	type = TypeUndefined;
	int active = 0;//ked ju bison vytvori, este niej aktivana
	ProgramPointer = -1;
	//location, obejct, real numbers a pod, nahodne cisla
}
Node::Node(std::string s,Type t)
{
	last_access = 0;
	type = TypeUndefined;
	int active = 0;//ked ju bison vytvori, este niej aktivana
	ProgramPointer = -1;

	name = s;
	type = t;
}
Tree::Tree()
{
	inner_node = false;
	depth = 0;
	for (int i =0; i< 256; i++)
		next[i] = NULL;
}
Tree::Tree(int d)
{
	inner_node = false;
	depth = 0;
	for (int i =0; i< 256; i++)
		next[i] = NULL;
	depth = d;
}
std::string quicksort(std::string s)
{
	if (s.length()<=1)
		return s;
	std::string s1 ="",s2 ="";
	for (int i =1; i< s.length();i++)
		if (s[i] < s[0]) s1+=s[i];
		else s2+=s[i];
	return quicksort(s1) + s[0] + quicksort(s2);
}
BotProgram::BotProgram()
{
	alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._";//vsetky znaky, co a poauzivame v identifikatoroch
	alphabet = quicksort(alphabet);//zasortime aby sme mohli pouzivat pulenie intervalu
}
int BotProgram::find_index(char a)
{
	int max = alphabet.length(); //za hranicu uz nesmie skocit
	int min = 0; //zaciatok
	int index = (max-min)/2;
	while ((max - min) > 1) //ked uz je jedna, presli sme vsetko a nie je tam
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
	}
	return -1; //nenasiel sa 
}
Tree * BotProgram::find_string(std::string s)
{
	Tree* t  = &defined;
	int i =0;
	std::cout << "looking for string " << s << std::endl;
	while (t->inner_node == true)
	{
		int pointer = find_index(s[i]);
		if (t->next[pointer]==NULL)
		{
			std::cout <<"creating " << pointer <<std::endl;
			t->next[pointer] = new Tree(t->depth+1);
		}
		t = t->next[pointer];
		i++;
		if (i == s.length())
			break;
	}
	return t;
}
void BotProgram::add_string(std::string s, Type type)
{
	Tree * t = find_string(s);//pridavame do tohoto kontejnera
	Node d(s,type);
	std::list<Node>::iterator iter;
	for (iter = t->items.begin(); 
		iter!=t->items.end(); 
		iter++)
	{
		if (iter->name == s) break;//kontrola, co tam nieco take uz nie je
	}
	std::cout << "Adding string " << s <<std::endl;
	t->items.push_back(d);
	//TODO else warning o preskakovani alebo prepisana hodnota alebo cos
	while(t->items.size()> MaxItems ) //pre opakovane stiepenie
	{
		//burst!
		t->inner_node = true;
		int splitted = -1,split = 0;
		std::cout << "Burstujem!" <<std::endl;
		std::list<Node> n;
		while (!(t->items.empty()))
		{
			if (t->items.begin()->name.length() == t->depth) //ak sa neda dalej
			{
				n.splice(n.begin(),t->items,t->items.begin());
				continue;
			}
			int pointer = find_index(t->items.begin()->name[t->depth]);
		 	if (t->next[pointer]==NULL) //
			{
				split++;
				splitted = pointer;
				std::cerr << "creating "<< std::endl;
				t->next[pointer] = new Tree(t->depth+1);
			}
			Tree * nxt = t->next[pointer];
			nxt->items.splice(nxt->items.begin(),t->items,t->items.begin());
		}
		t->items.swap(n);
		if ( split == 1 )
		{
			std::cout <<"repete! " <<splitted << std::endl;
			t = t->next[splitted];
		}
	}
}
void BotProgram::output(Tree * t)
{
	if (t == &defined) std::cout << "jadskyfgkewjygf " <<std::endl;
	std::cout << "v hlbke " << t->depth <<std::endl;
	for (std::list<Node>::iterator i = t->items.begin();i!=t->items.end(); i++)
		std::cout << "prvok s menom:" << i->name <<std::endl;
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
