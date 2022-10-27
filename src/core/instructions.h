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
    bool write_to_label;
    std::function<
        int (int arg, std::stack<int>& vm)
    > execute;
};

#endif

#ifndef INSTRUCTION_MAP_HELPER_H
#define INSTRUCTION_MAP_HELPER_H

struct Instruction find_instruction_by_opcode(int opcode);

#endif

