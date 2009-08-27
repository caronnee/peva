#include "./parser_functions.h"
#include <iostream>

/* Maximalny pocet dimenzii u pola*/
#define MAX_DIMENSION 7 

Instruction * instruction_load(Robot *p, std::string s)
{
	Node *n = p->find_var(s); 
	if (n == NULL)
	{
		std::cout << "hehehe:" << s << std::endl;
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

void reg(Robot * p, std::vector<Parameter_entry> c, Instructions b)
{
	p->add_function(c,b);
}

Instructions join_instructions(const Instructions i1, const Instructions i2)
{
	Instructions res = i1;
	for (size_t i =0; i < i2.size(); i++)
	{
		res.push_back(i2[i]);
	}
	return res;
}
void set_breaks(Robot * p, Instructions ins)
{
	size_t size = ins.size();
	std::cout << "Last loop number" << p->last_loop_number <<std::endl;
	getc(stdin);
	for (size_t i = 0; i< size; i++)
	{
		std::cout << "\t\t" << ins[i]->name_ << ins[i]->breaks()<< "\t" ;
//		getc(stdin);
		if(ins[i]->breaks() == p->last_loop_number)
		{
			std::cout << "IN:" << i <<std::endl;
			getc(stdin);
			InstructionBreak * b = (InstructionBreak *)ins[i];
			b->jump = size - i -1;
			b->depth -= p->core->depth; //rozdiel medzi zaciatkom breaku a jeho koncom
		}
	}
	std::cout << "Nenajdeny break!" <<std::endl;
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
		case OperationNotEqual:
			return new InstructionNotEqual();
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
Instruction * feature ( ObjectFeatures feat )
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
		case FeatureStep:
			return new InstructionStep();
		case FeatureSee:
			return new InstructionSee();
		case FeatureHit:
			return new InstructionHit();
		case FeatureShoot:
			return new InstructionShoot();//nutne musi zobrat
		case FeatureTurn:
			return new InstructionTurn();
		case FeatureTurnR:
			return new InstructionTurnR();
		case FeatureTurnL:
			std::cout << "ralh" << std::endl;
			getc(stdin);
			return new InstructionTurnL();
		case FeatureWait:
			return new InstructionWait();
		default:
			std::cout << "Vraciam NULL" << std::endl;
			getc(stdin);	
			return NULL;		
	}
}
