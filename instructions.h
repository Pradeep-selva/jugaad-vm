#include <string>
#include<vector>
#include<functional>
#include<map>
#include<stack>

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

struct Instruction {
    int op_code;
    std::string name;
    int num_args;
    std::function<
        void (int arg, std::stack<int>& vm)
    > execute;
};

#endif

#ifndef INSTRUCTION_MAP_H
#define INSTRUCTION_MAP_H

std::map<int, struct Instruction> instructions_table;

#endif

#ifndef INSTRUCTION_MAP_HELPER_H
#define INSTRUCTION_MAP_HELPER_H

struct Instruction find_instruction_by_opcode(int opcode);

#endif

