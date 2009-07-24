#ifndef __BISON_HELP__
#define __BISON_HELP__

#include "./tree/my_stack.h"
#include "./header1.h"

typedef std::vector<std::string> strings;
void add_variables(Program * p, std::vector<Constr> s, Create_type t);

void reg_main(Program * p,Instructions ins);
void reg(Program *p, Create_type t, std::string name,std::vector<Constr> s, Instructions i);
Instructions join_instructions(Instructions a, Instructions b);

Instruction * operRel(Operation op);
Instruction * operMul(Operation op);
Instruction * operAdd(Operation op);
Instruction * operOr(Operation op);
#endif
