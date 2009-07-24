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
void reg_main(Program* p, Instruction ins)
{
	p>PC = p->stack.size();
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
Instruction * operAdd(Operation op)
{
	switch(op)
	{
		case OperationPlus:
			return new InstructionPlus();
		case OperationMinus:
			return new InstructionMinus();
	}
}
 Instruction * OperOr(Operation op)
{
	switch(op)
	{
		case OperationBoolNot:
			return new InstructionBinaryNot();
		case OperationBoolAnd:
			return new InstructionBinaryAnd();
		case OperationBoolOr:
			return new InstructionBinaryOr();
		default: return NULL;
	}
}
