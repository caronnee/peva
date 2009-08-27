#ifndef __BISON_HELP__
#define __BISON_HELP__

#include "./robot.h"
#include "./header1.h"

typedef std::vector<std::string> strings;

Instruction * instruction_load(Robot * p, std::string s);
void reg(Robot *p, std::vector<Parameter_entry> s, Instructions i);
Instructions join_instructions(Instructions a, Instructions b);
void set_breaks(Robot * p, Instructions i);

Instruction * operRel(Operation op);
Instruction * operMul(Operation op);
Instruction * operAdd(Operation op);
Instruction * operOr(Operation op);
Instruction * feature (ObjectFeatures feat);
#endif
