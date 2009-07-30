#ifndef __BISON_HELP__
#define __BISON_HELP__

#include "./program.h"
#include "./header1.h"

typedef std::vector<std::string> strings;

Instruction * instruction_load(Program * p, std::string s);
void reg_main(Program * p,Instructions ins);
void reg(Program *p, Create_type t, std::string name,std::vector<Parameter_entry> s, Instructions i);
Instructions join_instructions(Instructions a, Instructions b);
void set_breaks(Program * p, Instructions i);

Instruction * operRel(Operation op);
Instruction * operMul(Operation op);
Instruction * operAdd(Operation op);
Instruction * operOr(Operation op);
Instruction * feature (ObjectFeatures feat);
#endif
