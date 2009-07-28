#include "./program.h"

Constr::Constr()
{
	default_set = false;
	id ="";
}
Constr::Constr(std::string a)
{
	id = a;
	default_set = false;
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
Parameter_entry::Parameter_entry()
{
	name = "Not_defined";
}
Parameter_entry::Parameter_entry(std::string n, Parameter_type pt, Create_type t)
{
	name = n;
	val_type = pt;
}
Function::Function(std::string n, std::vector<Parameter_entry> v, Create_type t)
{
	name =n;
	parameters = v;
	return_type = t; //potom sa priradi, ked bude funkcia zavolana
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
	for(int i =0; i< functions.size(); i++)
	{
		if(functions[i].name == nam)
		{
			return &functions[i];
		}
	}
	return NULL;
}
