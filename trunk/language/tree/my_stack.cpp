#include "my_stack.h"
#include <iostream>

#define MaxItems 3
Program::Program()
{
	nested = 0;
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

Node * Program::find_var(std::string s)
{
	Tree * t = find_string(s);
	for (std::list<Node*>::iterator i = t->items.begin(); 
			i != t->items.end(); 
			i++)
	{
		if ((*i)->name == s)
			return (*i);
	}
	return NULL;
}
/*
 *Vracia ukazovatel na samotny uzol, ktory skryva hodnotu, v ktorom je ulozena nasa hodnota
 */

//TODO presunut k stromu, kam to tematicky patri
Node * Program::add(std::string s, Create_type type)
{
	std::cout << "pridavam meno:" << s << std::endl;
	Tree * t = find_string(s);//pridavame do tohoto kontejnera
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

	} //TODO nejaka rozumnejsia metoda

	Node * nod = new Node(s, type);
	if (nested)
		nod->nested = Local;
	t->items.push_back(nod);
	//TODO else warning o preskakovani alebo prepisana hodnota alebo cos
	while(t->items.size()> MaxItems ) //pre opakovane stiepenie
	{
		//burst!
//		getc(stdin);
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
	return nod;
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
void Program::add(Instructions ins)
{
	for (int i =0; i<ins.size(); i++)
	{
		instructions.push_back(ins[i]);
	}
}
void Program::add_function(Create_type t, std::string name, std::vector<Constr> c, Instructions ins)
{
//TODO
}
void Program::enter()
{

}
void Program::leave()
{

}
void Program::save_to_xml()
{
	LIBXML_TEST_VERSION;

	data.doc = xmlNewDoc(BAD_CAST "1.0");
	data.root_ptr = xmlNewNode(NULL, BAD_CAST "Machine");
	xmlDocSetRootElement(data.doc, data.root_ptr);
	xmlNodePtr ptr;
	for(int i =0; i< instructions.size(); i++)
	{
		//ptr = instructions[i]->xml_format();
	}
	xmlSaveFormatFileEnc("machine.xml", data.doc, "UTF-8", 1);
	xmlFreeDoc(data.doc);
}
