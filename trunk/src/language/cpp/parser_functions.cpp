//TODO dat to do vlastneho namespacu
#include "../h/parser_functions.h"
#include <iostream>
#include "../../add-ons/h/macros.h"

/* Maximalny pocet dimenzii u pola*/
#define MAX_DIMENSION 7 

/*Instructions check_integer(unsigned line, Element e)
{
	Instructions ins;
	ins = e.ins;
	if (e.output.back().type == TypeReal)
	{
		ins.push_back(new InstructionConversionToInt(line));
	}
	return ins;
}*/
Element ident_load(unsigned line, Robot * r, std::string s)
{
	Element st;
	bool ok;
	Node *n = r->find_var(s, ok); 
	if (!ok)
	{
		r->error(line,Robot::ErrorVariableNotFound, '\''+s+'\'');
		st.output.push_back(*r->find_type(TypeUndefined));
		return st;
	}
	if(n->nested == Local)
		st.ins.push_back(new InstructionLoadLocal(line, n));
	else  
		st.ins.push_back(new InstructionLoadGlobal(line, n));
	st.output.push_back(*n->type_of_variable);	
	return st;
}
Instruction * possible_conversion(unsigned line, Type to, Type from)
{
	if ((to == TypeInteger) && (from == TypeReal))
		return new InstructionConversionToInt(line);
	if ((from == TypeInteger) && (to == TypeReal))
		return new InstructionConversionToReal(line);
	return NULL;
}

Element operRel(int line, Robot * r, Operation op, Create_type t1, Create_type t2)
{
	Element e;
	Instruction * il = conversionToReal(line, t1.type, t2.type);
	if (il!=NULL)
	{
		e.ins.push_back(il);
		e.output.push_back(*r->find_type(TypeReal));
	}
	else if ( t1!=t2)
	{
		r->error(line,Robot::ErrorConversionImpossible);
		return e;
	}
	else
		e.output.push_back(*r->find_type(TypeInteger));
	switch (t1.type)
	{
		case TypeInteger:
			switch(op)
			{
				case OperationLess:
					e.ins.push_back(new InstructionLtInteger(line));
					break;
				case OperationLessEqual:
					e.ins.push_back(new InstructionLeInteger(line));
					break;
				case OperationEqual:
					e.ins.push_back(new InstructionEqualInteger(line));
					break;
				case OperationGreater:
					e.ins.push_back(new InstructionGtInteger(line));
					break;
				case OperationGreaterEqual:
					e.ins.push_back(new InstructionGeInteger(line));
					break;
				case OperationNotEqual:
					e.ins.push_back(new InstructionNotEqualInteger(line));
					break;
				default: ;
			}
			break;
		case TypeReal:
			switch(op)
			{
				case OperationLess:
					e.ins.push_back(new InstructionLtReal(line));
					break;
				case OperationLessEqual:
					e.ins.push_back(new InstructionLeReal(line));
					break;
				case OperationEqual:
					e.ins.push_back(new InstructionEqualReal(line));
					break;
				case OperationGreater:
					e.ins.push_back(new InstructionGtReal(line));
					break;
				case OperationGreaterEqual:
					e.ins.push_back(new InstructionGeReal(line));
					break;
				case OperationNotEqual:
					e.ins.push_back(new InstructionNotEqualReal(line));
					break;
				default: ;
			}
			break;
		case TypeObject:
			switch(op)
			{
				case OperationEqual:
					e.ins.push_back(new InstructionEqualObject(line));
					break;
				case OperationNotEqual:
					e.ins.push_back(new InstructionNotEqualObject(line));
					break;
				default: r->error(line, Robot::ErrorOperationNotSupported);
			}
			break;
		default:
			r->error(line, Robot::ErrorOperationNotSupported);
	}
	return e;
}
Instruction * conversionToReal(unsigned line, Type t1, Type t2)
{
	if (((t1 == TypeInteger)&& (t2 == TypeReal))||((t1 == TypeReal) && (t2 == TypeInteger)))
	
		return new InstructionConversionToReal(line);
	return NULL;
}
Element operMul(int line, Robot * r, Operation op, Create_type t1, Create_type t2)
{	
	Element e;
	Instruction * i = conversionToReal(line, t1.type, t2.type);
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
					e.ins.push_back(new InstructionMultiplyInteger(line));
					break;
				case OperationDivide:
					e.ins.push_back( new InstructionDivideInteger(line));
					break;
				case OperationModulo:
					e.ins.push_back( new InstructionModulo(line));
					break;
				case OperationAnd:
					e.ins.push_back( new InstructionBinaryAnd(line));
					break;
				case OperationOr:
					e.ins.push_back( new InstructionBinaryOr(line));
					break;
				case OperationNot:
					e.ins.push_back( new InstructionBinaryNot(line));
					break;
				default: r->error(line,Robot::ErrorOperationNotSupported);
			}
			break;
		case TypeReal:
			switch (op)
			{
				case OperationMultiply:
					e.ins.push_back(new InstructionMultiplyReal(line));
					break;
				case OperationDivide:
					e.ins.push_back( new InstructionDivideReal(line));
					break;
				default: r->error(line,Robot::ErrorOperationNotSupported);
			}		
			break;
		default: r->error(line,Robot::ErrorOperationNotSupported);
	}
	e.temp.push_back(true);
	e.output.push_back(Create_type(output));
	return e;
}
Element operAdd(int line, Robot * r,Operation op, Create_type t1, Create_type t2)
{
	Element e;
	Instruction *i = conversionToReal(line, t1.type,t2.type);
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
					e.ins.push_back( new InstructionPlusInteger(line));
					break;
				case OperationMinus:
					e.ins.push_back( new InstructionMinusInteger(line));
					break;
				default:
					r->error(line, Robot::ErrorOperationNotSupported);
			}
			break;
		case TypeReal:
			switch(op)
			{
				case OperationPlus:
					e.ins.push_back( new InstructionPlusReal(line));
					break;
				case OperationMinus:
					e.ins.push_back( new InstructionMinusReal(line));
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
			e.ins.push_back( new InstructionBinaryNot(line));
			break;
		case OperationBoolOr:
			e.ins.push_back( new InstructionBinaryOr(line));
			break;
		default: 
			r->error(line, Robot::ErrorOperationNotSupported);
	}
	e.output.push_back(Create_type(TypeInteger));
	return e;
}//FIXME rozdelit na tie, co vyzaduju object a tie, co vyzaduju integer
//TODO pre viacere odstrait nully, ale to sa mi teraz nestane, len pre pripad, zby som povoloval aj errorove veci
Element feature ( int line, Robot *r, ObjectFeatures feat, Element e )
{
	Element ee;
	ee.ins = e.ins;
	if ((!ee.ins.empty())&&(ee.ins.back() == NULL)) //aktualne moze mat len jedno output -> FIXME aj pre viacere, maze NULLy
	{
		ee.ins.pop_back();
	}
	for (size_t i =0; i< e.temp.size(); i++)
	{
		if (e.temp[i])
		{
			ee.ins.push_back(new InstructionRemoveTemp(line));
		}
	}
	switch(feat)
	{
		case FeatureDirection:
			if (e.output.size() != 1)
			{
				r->error(line, Robot::ErrorWrongNumberOfParameters);
				break;
			}
			if (e.output.back().type != TypeLocation)
			{
				r->error(line, Robot::ErrorConversionImpossible);
				break;
			}
			ee.output.push_back(*r->find_type(TypeInteger));
			ee.ins.push_back(new InstructionDirection(line));
			break;
		case FeatureTarget:
			if ((e.output.size() > 0))
			{
				r->error(line, Robot::ErrorWrongNumberOfParameters);
				break;
			}
			ee.output.push_back(*r->find_type(TypeLocation));
			ee.ins.push_back( new InstructionTarget(line));
			
			break;
		case FeatureWait:
			if (e.output.size() != 1)
			{
				r->error(line, Robot::ErrorWrongNumberOfParameters);
				break;
			}
			if (e.output.back().type == TypeReal)
			{
				e.output.back() = *r->find_type(TypeInteger);
				ee.ins.push_back(new InstructionConversionToInt(line));
			}
			if (e.output.back()!= *r->find_type(TypeInteger))
			{
				r->error(line, Robot::ErrorConversionImpossible);
				break;
			}
			ee.ins.push_back(new InstructionWait(line));
			ee.ins.push_back(new InstructionFetchState(line));
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureIsPlayer:
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionIsPlayer(line));
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureIsEnemy:
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionIsEnemy(line));
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureIsWall:
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionIsWall(line));
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureIsMissille:
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionIsMissille(line));
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureIsMoving:
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionIsMoving(line));
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureLocate: //vracia poziciu objektu, ak ho r vidi, ak nie, vyhodi -1, -1;
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionLocate(line));
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeLocation));
			break;
		case FeatureSeeEnemy:
			if (e.output.size() == 0)
			{
				ee.ins.push_back( new InstructionSeeEnemy(line));
			}
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureSee:
			if (e.output.size() == 0)
			{
				ee.ins.push_back( new InstructionSee(line));
			}
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureHit: 
			if ((e.output.size() == 1) && (e.output.back().type == TypeObject))
				ee.ins.push_back( new InstructionHit(line));
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureTurn:
			if (e.output.size() != 1)
			{
				r->error(line, Robot::ErrorWrongNumberOfParameters);
				break;
			}
			if (e.output.back().type == TypeReal)
			{
				ee.ins.push_back( new InstructionConversionToInt(line));
				if (e.temp.back())
					ee.ins.push_back( new InstructionRemoveTemp(line));
				e.temp.back() = true;
				e.output.back() = *r->find_type(TypeInteger);
			}
			if (e.output.back().type != TypeInteger)
			{
				r->error(line, Robot::ErrorConversionImpossible);
				break;
			}
			ee.ins.push_back( new InstructionTurn(line));
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureTurnR:
			if (e.output.size() == 0)
				ee.ins.push_back( new InstructionTurnR(line));
			else
				r->error(line, Robot::ErrorWrongNumberOfParameters);
			ee.output.push_back(*r->find_type(TypeInteger));
			break;
		case FeatureTurnL:
			if (e.output.size() == 0)
				ee.ins.push_back( new InstructionTurnL(line));
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
				ee.ins.push_back(new InstructionConversionToInt(line));
				ee.ins.push_back(new InstructionRemoveTemp(line));
				e.output.back() = *r->find_type(TypeInteger);
			}
			if (e.output.back() == *r->find_type(TypeInteger))
			{
				ee.ins.push_back(new InstructionShootAngle(line));
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
					ee.ins.push_back(new InstructionStepDefault(line));
					ee.ins.push_back(new InstructionFetchState(line));
					break;
				}
				if (e.output.size() == 1)
				{
					if (e.output.back() == *r->find_type(TypeReal))
					{	
						ee.ins.push_back(new InstructionConversionToInt(line));
						ee.ins.push_back(new InstructionRemoveTemp(line));
						e.output.back() = *r->find_type(TypeInteger); 
					}
					if (e.output.back() == *r->find_type(TypeInteger))
					{
						ee.ins.push_back(new InstructionStep(line));
						ee.ins.push_back(new InstructionFetchState(line));
						break;
					}
					r->error(line, Robot::ErrorOperationNotSupported);
					break;
				}
				r->error(line, Robot::ErrorOperationNotSupported);
				break;
			}
		default:
			r->error(line, Robot::ErrorOperationNotSupported);
	}
	return ee;
}
Instructions get_load_type ( unsigned line, Create_type t )
{
	Instructions fullAccessBack;
	if (!t.is_simple())
		fullAccessBack.push_back(new InstructionSaveVariable(line));
	std::vector<int> toLoad;
	std::vector<Create_type> types;
	Create_type type = t;
	types.push_back(type);
	while(!types.empty())
	{	
		type = types.back();
		types.pop_back();
		if (type.is_simple())
		{
			for(size_t i =0; i < toLoad.size(); i++)
			{
				fullAccessBack.push_back(new InstructionLoad(line, toLoad[i]));
				fullAccessBack.push_back(new InstructionLoad(line));
			}
			if (!toLoad.empty())
				toLoad.back()--;
			while((!toLoad.empty()) && (toLoad.back() < 0 ))
			{
				toLoad.pop_back();
				if (toLoad.empty())
					break;
				toLoad.back()--;
			}			
			if (!toLoad.empty())
				fullAccessBack.push_back(new InstructionLoadVariable(line));
			continue;
		}
		toLoad.push_back(type.range + type.nested_vars.size()-1);
		for (size_t i =0; i< type.range; i++)
			types.push_back(*type.data_type);
		for (size_t i =0; i< type.nested_vars.size(); i++)
			types.push_back(*type.nested_vars[i].type);
	}
	return fullAccessBack;
}

Instructions get_store_type(unsigned line, Create_type t )
{
	Instructions fullAccessBack;
	if (!t.is_simple())
		fullAccessBack.push_back(new InstructionSaveVariable(line));
	std::vector<Position> toLoad;
	std::vector<Create_type> types;
	Create_type type = t;
	types.push_back(type);
	while(!types.empty())
	{	
		type = types.back();
		types.pop_back();
		if (type.is_simple())
		{
			for(size_t i =0; i < toLoad.size(); i++)
			{
				fullAccessBack.push_back(new InstructionLoad(line, toLoad[i].x));
				fullAccessBack.push_back(new InstructionLoad(line));
			}
			switch(type.type)
			{
				case TypeInteger:
					fullAccessBack.push_back(new InstructionStoreInteger(line));
					break;
				case TypeReal:
					fullAccessBack.push_back(new InstructionStoreReal(line));
					break;
				case TypeObject:
					fullAccessBack.push_back(new InstructionStoreObject(line));
					break;
				default:
					throw "No instrucion for saving such a type";
			}
			if (!toLoad.empty())
				toLoad.back().x++;
			while((!toLoad.empty()) && (toLoad.back().x > toLoad.back().y ))
			{
				toLoad.pop_back();
				if (toLoad.empty())
					break;
				toLoad.back().x++;
			}			
			if (!toLoad.empty())
				fullAccessBack.push_back(new InstructionLoadVariable(line));
			continue;
		}
		toLoad.push_back(Position(0, type.range + type.nested_vars.size()-1));
		for (size_t i =0; i< type.range; i++)
			types.push_back(*type.data_type);
		for (size_t i =0; i< type.nested_vars.size(); i++)
			types.push_back(*type.nested_vars[i].type);
	}
	return fullAccessBack;
}
