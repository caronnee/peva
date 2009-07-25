#include "./parser_functions.h"

/* Maximalny pocet dimenzii u pola*/
#define MAX_DIMENSION 7 

Instruction * instruction_load(Program *p, std::string s)
{
	Node *n = p->find_var(s); 
	if(n->nested == Local)
		return new InstructionLoadLocal(n);
	else  
		return new InstructionLoadGlobal(n);
}
void reg_main(Program* p, Instructions ins)
{
	p->PC = p->instructions.size();
	p->add(ins);
}

void reg(Program * p,Create_type t, std::string name, std::vector<Constr> c, Instructions b)
{
	p->add_function(t, name,c,b);
}

Instructions join_instructions(Instructions i1, Instructions i2)
{
	Instructions res = i1;
	for (int i =0; i < i2.size(); i++)
	{
		res.push_back(i2[i]);
	}
	return res;
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
