//TODO dat to do vlastneho namespacu
#include "./parser_functions.h"
#include <iostream>

/* Maximalny pocet dimenzii u pola*/
#define MAX_DIMENSION 7 

Instructions check_integer(Element e)
{
	Instructions ins;
	ins = e.ins;
	if (e.output.back().type == TypeReal)
	{
		ins.push_back(new InstructionConversionToInt());
	}
	return ins;
}
Element ident_load(unsigned line, Robot * r, std::string s)
{
	Element st;
	bool ok;
	Node *n = r->find_var(s, ok); 
	if (!ok)
	{
		std::cout << "Error, variable not found";getc(stdin);
		r->error(line,Robot::Robot::ErrorVariableNotFound);
	}
	if(n->nested == Local)
		st.ins.push_back(new InstructionLoadLocal(n));
	else  
		st.ins.push_back(new InstructionLoadGlobal(n));
	std::cout << "Tu sa este dostanem eident 2:"<<n->type_of_variable; getc(stdin);
	st.output.push_back(*n->type_of_variable);	
	std::cout << "Tu sa este dojdshgskjgbhkrsjdstanem eident 2:"<<n->type_of_variable; getc(stdin);
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

Instructions join_instructions(const Instructions i1, const Instructions i2)
{
	Instructions res = i1;
	for (size_t i =0; i < i2.size(); i++)
	{
		res.push_back(i2[i]);
	}
	return res;
}

Element operRel(int l, Robot * r, Operation op, Create_type t1, Create_type t2)
{
	Element e;
	Instruction * il = conversionToReal(t1.type, t2.type);
	if (il!=NULL)
	{
		e.ins.push_back(il);
		e.output.push_back(*r->find_type(TypeReal));
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
	e.ins.push_back(new InstructionRemoveTemp());
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
Element feature ( int line, Robot *r, ObjectFeatures feat, Element e )
{
	Element ee;
	ee.ins = e.ins;
	if ((!ee.ins.empty())&&(ee.ins.back() == NULL)) //aktualne moze mat len jedno output -> FIXME aj pre viacere
	{
		ee.ins.pop_back();
	}
	switch(feat)
	{
		case FeatureIsPlayer:
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionIsPlayer());
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureIsWall:
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionIsWall());
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureIsMissille:
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionIsMissille());
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureIsMoving:
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionIsMoving());
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureLocate: //vracia poziciu objektu, ak ho r vidi, ak nie, vyhodi -1, -1;
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionLocate(*r->find_type(TypeLocation)));
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeLocation));
			break;
		case FeatureSee:
			if (e.output.size() == 0)
			{
				bool ok;
				ee.ins.push_back( new InstructionSee(r->find_var("seen", ok)));
			}
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureHit: //obbjekt nieco zasiahol, vracia NULL ak nikoho, Objekt ak ano. Robot musi strelu vidiet
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionHit());
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeObject));
			break;
		case FeatureTurn:
			if (e.output.size() == 1) 
				ee.ins.push_back( new InstructionTurn());
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureTurnR:
			if (e.output.size() == 0)
				ee.ins.push_back( new InstructionTurnR());
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureTurnL:
			if (e.output.size() == 0)
				ee.ins.push_back( new InstructionTurnL());
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureShoot:
			if (e.output.size() != 1)
			{
				r->error(line, Robot::ErrorWrongNumberOfParameters);
				break;
			}
			if (e.output.back() == *r->find_type(TypeReal))
			{
				ee.ins.push_back(new InstructionConversionToInt());
				e.output.back() = *r->find_type(TypeInteger);
			}
			if (e.output.back() == *r->find_type(TypeInteger))
			{
				ee.ins.push_back(new InstructionShootAngle);
				ee.output.push_back(*r->find_type(TypeInteger));
				break;
			}
			if (e.output.back() == *r->find_type(TypeLocation))
			{
				ee.ins.push_back(new InstructionShootLocation());
				ee.output.push_back(*r->find_type(TypeInteger));
				break;
			}
			r->error(line, Robot::ErrorOperationNotSupported);
			break;
		case FeatureStep:
			{
				ee.output.push_back(*r->find_type(TypeInteger));
				if(e.output.size() == 0)
				{
					ee.ins.push_back(new InstructionStepDefault());
					break;
				}
				if (e.output.size() == 1)
				{
					if (e.output.back() == *r->find_type(TypeReal))
					{	
						ee.ins.push_back(new InstructionConversionToInt());
						e.output.back() = *r->find_type(TypeInteger); 
						e.temp.back() = true;
					}
					if (e.output.back() == *r->find_type(TypeInteger))
					{
						ee.ins.push_back(new InstructionStep());
						break;
					}
					r->error(line, Robot::ErrorOperationNotSupported);
					break;
				}
				r->error(line, Robot::ErrorOperationNotSupported);
				break;
			}
		default:
			r->error(line, Robot::Robot::ErrorOperationNotSupported);
	}
	return ee;
}
Instruction * get_store_type ( unsigned l, Robot * r, Create_type t)
{

	switch ( t.type )
	{
		case  TypeReal:
			return new InstructionStoreReal();
		case TypeInteger:
			return new InstructionStoreInteger();
		case TypeObject:
			return new InstructionStoreObject();
		default:
			return new InstructionStore();
	}
}
