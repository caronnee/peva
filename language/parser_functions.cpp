#include "./parser_functions.h"
#include <iostream>

/* Maximalny pocet dimenzii u pola*/
#define MAX_DIMENSION 7 

Instruction * instruction_load(Program *p, std::string s)
{
	Node *n = p->find_var(s); 
	if (n == NULL)
	{
		std::cout << "hehehe:" << s<< std::endl;
		p->error = 1;
		getc(stdin);
	}
	if(n->nested == Local)
	{
		return new InstructionLoadLocal(n);
	}
	else  
	{
		return new InstructionLoadGlobal(n);
	}
}

void reg(Program * p,Create_type t, std::string name, std::vector<Parameter_entry> c, Instructions b)
{
	Node * ret ; //TODO krajsie
	if( t.type == TypeVoid)
	{
		ret = NULL;
	}
	else 
		ret = p->add("",t);
	p->add_function(ret, name,c,b);
}

Instructions join_instructions(Instructions i1, Instructions i2)
{
	Instructions res = i1;
	for (size_t i =0; i < i2.size(); i++)
	{
		res.push_back(i2[i]);
	}
	return res;
}
void set_breaks(Program * p, Instructions ins)
{
	size_t size = ins.size();
	std::cout << p->last_loop_number <<std::endl;
	getc(stdin);
	for (size_t i = 0; i< size; i++)
	{
		std::cout << "\t\thuuu" << ins[i]->breaks()<<std::endl;
		std::cout << "\t\t" << ins[i]->name_ <<std::endl;
		if(ins[i]->breaks() == p->last_loop_number)
		{
			InstructionBreak * b = (InstructionBreak *)ins[i];
			b->jump = size - i;
		}
	}
	std::cout << "BLE" <<std::endl;
}
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
Instruction *operMul(Operation op)
{
	switch (op)
	{
		case OperationMultiply:
			return new InstructionMultiply();
		case OperationDivide:
			return new InstructionDivide();
		case OperationModulo:
			return new InstructionModulo();
		case OperationAnd:
			return new InstructionBinaryAnd();
		case OperationOr:
			return new InstructionBinaryOr();
		case OperationNot:
			return new InstructionNot();
		default: return NULL;
	}
}
Instruction * operAdd(Operation op) // add
{
	switch(op)
	{
		case OperationPlus:
			return new InstructionPlus();
		case OperationMinus:
			return new InstructionMinus();
		default:
			return NULL;
	}
}
Instruction * operOr(Operation op) //Bool_OR
{
	switch(op)
	{
		case OperationBoolNot:
			return new InstructionBinaryNot();
		case OperationBoolOr:
			return new InstructionBinaryOr();
		default: return NULL;
	}
}
Instruction * feature (ObjectFeatures feat)
{
	switch(feat)
	{
		case FeatureIsPlayer:
		       return new InstructionIsPlayer();
	       	case FeatureIsWall:
			return new InstructionIsWall();
	 	case FeatureIsMissille:
			return new InstructionIsMissille();
		case FeatureIsMoving:
			return new InstructionIsMoving();
		case FeatureLocate:
			return new InstructionLocate();
		default:
			return NULL;		
	}
}
