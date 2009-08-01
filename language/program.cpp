#include "./program.h"
#include <iostream>

Constr::Constr()
{
	default_set = false;
	id ="";
}
Constr::Constr(std::string a)
{
	id =a;
	default_set  =false;
}
Constr::Constr(std::string a, int def)
{
	id  = a;
	default_set = true;
	ins.push_back(new InstructionLoad(def));
}
Constr::Constr(std::string a, Instructions i)
{
	id = a;
	ins = i;
	default_set = true;
}

Program::Program()
{
	last_loop_number = 0;
	nested = "";
	error = false;//TODO pridat errorou hlasku
	core = new Core();
}

Function * Program::find_f(std::string nam)
{
	for(int i =0; i< core->functions.size(); i++)
	{
		if(core->functions[i]->name == nam)
		{
			return core->functions[i];
		}
	}
	return NULL;
}

Node * Program::find_var(std::string var_name)
{
	std::string s = nested + var_name;
	Tree * t = defined.find_string(s);
	for (std::list<Node*>::iterator i = t->items.begin(); 
			i != t->items.end(); 
			i++)
	{
		if ((*i)->name == s)
			return (*i);
	}
	s = var_name;
	t = defined.find_string(s);
	for (std::list<Node*>::iterator i = t->items.begin(); 
			i != t->items.end(); 
			i++)
	{
		if ((*i)->name == s)
			return (*i);
	}
	return NULL;
}
Node * Program::add(std::string name, Create_type type)
{
	return defined.add(nested + name, type);
}
/*
 *Vracia ukazovatel na samotny uzol, ktory skryva hodnotu, v ktorom je ulozena nasa hodnota
 */
void Program::add_global(Instructions ins)
{
	core->PC = instructions.size();
	for (int i =0; i< ins.size(); i++)
	{
		instructions.push_back(ins[i]);	
	}
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
void Program::add_function(Node * n, std::string name, std::vector<Parameter_entry> c, Instructions ins)
{
	Function* f = new Function(name, c,n);
	f->begin = instructions.size();
	f->end = f->begin + ins.size()+1;
	core->functions.push_back(f);
	for (int i =0; i< ins.size(); i++)
	{
		instructions.push_back(ins[i]);
	}
	if(name == "main")
	{
		instructions.push_back(new InstructionMustJump(ins.size()*-1));
	}
	else
		instructions.push_back(new InstructionRestore()); //pre procedury
}
void Program::enter(std::string name)
{
	nested+= name + DELIMINER_CHAR;
}
void Program::leave() //odide z funkcie
{
	nested = "";
}
void Program::save_to_xml()
{
	LIBXML_TEST_VERSION;

	data.doc = xmlNewDoc(BAD_CAST "1.0");
	data.root_ptr = xmlNewNode(NULL, BAD_CAST "Machine");
	xmlDocSetRootElement(data.doc, data.root_ptr);
	xmlNodePtr parent = data.root_ptr;
	xmlNodePtr ptr;
	int fce_num = 0;
	std::cout<< "Zapamatovane mena:" <<std::endl;
	for(int i =0; i< core->functions.size(); i++)
	{
		std::cout<< core->functions[i]->name<<std::endl;
	}
	for(int i =0; i< instructions.size(); i++)
	{
		.//std::cout << i << "," << instructions[i]->name_ <<std::endl;
		if(core->functions[fce_num]->end == i)
		{
			xmlAddChild(data.root_ptr, parent);
			parent = data.root_ptr;
			fce_num++;
		}
		if(core->functions[fce_num]->begin == i)
			parent = xmlNewNode(NULL, BAD_CAST core->functions[fce_num]->name.c_str());
		ptr = instructions[i]->xml_format();
		xmlAddChild(parent, ptr);
	}
	xmlAddChild(data.root_ptr, parent);
	xmlSaveFormatFileEnc("machine.xml", data.doc, "UTF-8", 1);
	xmlFreeDoc(data.doc);
}

void Program::enter_loop()
{
	last_loop_number++; //v podstate loop_zanorenie
	loop_labels.push(last_loop_number);
}
void Program::end_loop()
{
	last_loop_number--;
	loop_labels.pop();
}