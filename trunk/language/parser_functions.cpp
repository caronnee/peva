//TODO dat to do vlastneho namespacu
#include "./parser_functions.h"
#include <iostream>

/* Maximalny pocet dimenzii u pola*/
#define MAX_DIMENSION 7 

Element ident_load(unsigned line, Robot * r, std::string s)
{
	Element st;
	Node *n = r->find_var(s); 
	if (n == NULL)
	{
		r->error(line,Robot::Robot::ErrorVariableNotFound);
		std::cout << "nenaslo mi premennu" <<std::endl;
		return st;
	}
	if(n->nested == Local)
		st.ins.push_back(new InstructionLoadLocal(n));
	else  
		st.ins.push_back(new InstructionLoadGlobal(n));
	st.output.push_back(n->type_of_variable);
	return st;
}
Instruction * possible_conversion(Type to, Type from)
{
	if ((to == TypeInteger) && (from == TypeReal))
		return new InstructionConversionToInt();
	if ((from == TypeInteger) && (to == TypeReal))
		return new InstructionConversionToReal();
	return NULL;
}
//constr je load vsetkych funkcii
Instructions assign_default(int line, Robot * r,Node * n, Constr& l)
{
	Instructions ins;
	std::vector<int> access_id;//co vsetko ma loadnut
	std::vector<int> last_range;//co vsetko ma loadnut
	std::vector<Create_type *> types;
	while (!types.empty())
	{
		Create_type * t = types.back();
		if (is_simple(t->type))
		{
			if (n->nested == Local)
			ins.push_back(new InstructionLoadLocal(n));
			else 
			ins.push_back(new InstructionLoadGlobal(n));
			for(size_t i =0; i> access_id.size(); i++)
			{
			ins.push_back(new InstructionLoad(access_id[i]));
				switch (t->type)
				{
					case TypeInteger:
						if (l.output.back().type == TypeReal)
						ins.push_back(new InstructionConversionToInt());
						else if (l.output.back()!=t->type)
						{
							r->error(line, Robot::ErrorConversionImpossible);
							return ins;
						}
					ins.push_back(new InstructionStoreInteger());
							break;
					case TypeReal:
							if (l.output.back().type == TypeInteger)
							ins.push_back(new InstructionConversionToInt());
							else if (l.output.back()!=t->type)
							{
								r->error(line, Robot::ErrorConversionImpossible);
								return ins;
							}
						ins.push_back(new InstructionStoreReal());
							break;
					case TypeObject:
							if(t->type!=TypeObject)
							{
								r->error(line,Robot::ErrorConversionImpossible);
								return ins;
							}
						ins.push_back(new InstructionStoreObject());
					default:
						       	r->error(line,Robot::ErrorTypeNotRecognized);
							break;
				}
			}
			access_id.back()++;
			while ((!access_id.empty())&&(access_id.back() == last_range.back()))
			{
				access_id.pop_back();
				last_range.pop_back();
				if (!access_id.empty())
					access_id.back()++;
			}

		}
	}
	return ins;
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
	//std::cout << "Nenajdeny break!" <<std::endl;
}
Element operRel(int l, Robot * r, Operation op, Create_type t1, Create_type t2)
{
	Element e;
	Instruction * il = conversionToReal(t1.type, t2.type);
	if (il!=NULL)
	{
		e.ins.push_back(il);
		e.output.push_back(Create_type(TypeReal));
	}
	else if ( t1!=t2)
	{
		r->error(l,Robot::ErrorConversionImpossible);
		return e;
	}
	else
		e.output.push_back(t1);
	switch (e.output[0].type)
	{
		case TypeInteger:
			switch(op)
			{
				case OperationLess:
					e.ins.push_back(new InstructionLtInteger());
					break;
				case OperationLessEqual:
					e.ins.push_back(new InstructionLeInteger());
					break;
				case OperationEqual:
					e.ins.push_back(new InstructionEqualInteger());
					break;
				case OperationGreater:
					e.ins.push_back(new InstructionGtInteger());
					break;
				case OperationGreaterEqual:
					e.ins.push_back(new InstructionGeInteger());
					break;
				case OperationNotEqual:
					e.ins.push_back(new InstructionNotEqualInteger());
					break;
				default: ;
			}
			break;
		case TypeReal:
			switch(op)
			{
				case OperationLess:
					e.ins.push_back(new InstructionLtReal());
					break;
				case OperationLessEqual:
					e.ins.push_back(new InstructionLeReal());
					break;
				case OperationEqual:
					e.ins.push_back(new InstructionEqualReal());
					break;
				case OperationGreater:
					e.ins.push_back(new InstructionGtReal());
					break;
				case OperationGreaterEqual:
					e.ins.push_back(new InstructionGeReal());
					break;
				case OperationNotEqual:
					e.ins.push_back(new InstructionNotEqualReal());
					break;
				default: ;
			}
			break;
		case TypeObject:
			switch(op)
			{
				case OperationEqual:
					e.ins.push_back(new InstructionEqualObject());
					break;
				case OperationNotEqual:
					e.ins.push_back(new InstructionNotEqualObject());
					break;
				default: r->error(l, Robot::ErrorOperationNotSupported);
			}
			break;
		default:
			r->error(l, Robot::ErrorOperationNotSupported);
	}
	return e;
}
Instruction * conversionToReal(Type t1, Type t2)
{
	if (((t1 == TypeInteger)&& (t2 == TypeReal))||((t1 == TypeReal) && (t2 == TypeInteger)))
	
		return new InstructionConversionToReal();
	return NULL;
}
Element operMul(int line, Robot * r, Operation op, Create_type t1, Create_type t2)
{	
	Element e;
	Instruction * i = conversionToReal(t1.type, t2.type);
	Type output = t1.type;
	if (i!=NULL)
	{
		std::cout << "konvertujem na real"<< t1.type<< " "<< t2.type << std::endl;
		output = TypeReal;
		e.ins.push_back(i);
	}
	switch (output)
	{
		case TypeInteger:
			switch (op)
			{
				case OperationMultiply:
					e.ins.push_back(new InstructionMultiplyInteger());
					break;
				case OperationDivide:
					e.ins.push_back( new InstructionDivideInteger());
					break;
				case OperationModulo:
					e.ins.push_back( new InstructionModulo());
					break;
				case OperationAnd:
					e.ins.push_back( new InstructionBinaryAnd());
					break;
				case OperationOr:
					e.ins.push_back( new InstructionBinaryOr());
					break;
				case OperationNot:
					e.ins.push_back( new InstructionBinaryNot());
					break;
				default: r->error(line,Robot::ErrorOperationNotSupported);
			}
			break;
		case TypeReal:
			switch (op)
			{
				case OperationMultiply:
					e.ins.push_back(new InstructionMultiplyReal());
					break;
				case OperationDivide:
					e.ins.push_back( new InstructionDivideReal());
					break;
				default: r->error(line,Robot::ErrorOperationNotSupported);
			}		
			break;
		default: r->error(line,Robot::ErrorOperationNotSupported);
	}
	e.output.push_back(Create_type(output));
	return e;
}
Element operAdd(int line, Robot * r,Operation op, Create_type t1, Create_type t2)
{
	Element e;
	Instruction *i = conversionToReal(t1.type,t2.type);
	Type output = t1.type;;
	if (i!=NULL)
	{
		output = TypeReal;
		e.ins.push_back(i);
	}
	else if (t1!=t2)
	{
		r->error(line, Robot::ErrorOperationNotSupported);
		return e;
	}
	switch (output)
	{
		case TypeInteger:
			switch(op)
			{
				case OperationPlus:
					e.ins.push_back( new InstructionPlusInteger());
					break;
				case OperationMinus:
					e.ins.push_back( new InstructionMinusInteger());
					break;
				default:
					r->error(line, Robot::ErrorOperationNotSupported);
			}
			break;
		case TypeReal:
			switch(op)
			{
				case OperationPlus:
					e.ins.push_back( new InstructionPlusReal());
					break;
				case OperationMinus:
					e.ins.push_back( new InstructionMinusReal());
					break;
				default:
					r->error(line, Robot::ErrorOperationNotSupported);
			}
			break;
		default:
			r->error(line, Robot::ErrorOperationNotSupported);
	}
	e.output.push_back(Create_type(output));
	return e;
}

Element operOr(int line, Robot * r,Operation op, Create_type t1, Create_type t2) //Bool_OR
{
	Element e;
	//ak nie je bool, oniec
	if ((t1.type != TypeInteger)||(t2.type!=TypeInteger))
	{
		r->error(line, Robot::ErrorOperationNotSupported);
	}
	switch(op)
	{
		case OperationBoolNot:
			e.ins.push_back( new InstructionBinaryNot());
			break;
		case OperationBoolOr:
			e.ins.push_back( new InstructionBinaryOr());
			break;
		default: 
			r->error(line, Robot::ErrorOperationNotSupported);
	}
	e.output.push_back(Create_type(TypeInteger));
	return e;
}
Instructions feature ( int line, Robot *r, ObjectFeatures feat, Create_type t )
{
	Instructions ins;
	if (t!=TypeObject)
	{
		r->error(line, Robot::ErrorOperationNotSupported);
		return ins;
	}
	switch(feat)
	{
		case FeatureIsPlayer:
			ins.push_back( new InstructionIsPlayer());
			break;
	       	case FeatureIsWall:
			ins.push_back( new InstructionIsWall());
			break;
	 	case FeatureIsMissille:
			ins.push_back( new InstructionIsMissille());
			break;
		case FeatureIsMoving:
			ins.push_back( new InstructionIsMoving());
			break;
		case FeatureLocate:
			ins.push_back( new InstructionLocate());
			break;
		case FeatureStep:
			ins.push_back( new InstructionStep());
			break;
		case FeatureSee:
			ins.push_back( new InstructionSee());
			break;
		case FeatureHit:
			ins.push_back( new InstructionHit());
			break;
		case FeatureShoot:
			ins.push_back( new InstructionShoot());//nutne musi zobrat
			break;
		case FeatureTurn:
			ins.push_back( new InstructionTurn());
			break;
		case FeatureTurnR:
			ins.push_back( new InstructionTurnR());
			break;
		case FeatureTurnL:
			ins.push_back( new InstructionTurnL());
			break;
		case FeatureWait:
			ins.push_back( new InstructionWait());
			break;
		default:
			r->error(line, Robot::ErrorOperationNotSupported);
	}
	return ins;
}
