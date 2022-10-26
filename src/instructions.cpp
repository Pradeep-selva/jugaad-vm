#include "instructions.h"

#include<bits/stdc++.h>
#include <stdexcept>

using namespace std;

// opcodes for instructions
const int PUSH_OPCODE = 0;
const int ADD_OPCODE = 1;
const int SUB_OPCODE = 2;
const int MUL_OPCODE = 3;
const int DIV_OPCODE = 4;

// arg counts for opcodes
const int PUSH_ARG_COUNT = 0;
const int ARITHMETIC_ARG_COUNT = 2;

// helper
vector<int> pop_vm_elements(stack<int>& vm, int num_args) {
    vector<int> args;

    while(num_args--) {
        args.push_back(vm.top());
        vm.pop();
    }

    return args;
}

/**
 * opcode executor functions
 */
void exec_push(int arg, stack<int>& vm) {
    vm.push(arg);
}

void exec_add(int arg, stack<int>& vm) {
    if(vm.size() < ARITHMETIC_ARG_COUNT)
        throw invalid_argument("[ADD] STACK OUT OF BOUNDS");

    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);
    int sum = 0;

    while(!args.empty()) {
        sum += args.back();
        args.pop_back();
    }

    vm.push(sum);
}

void exec_sub(int arg, stack<int>& vm) {
   if(vm.size() < ARITHMETIC_ARG_COUNT)
        throw invalid_argument("[ADD] STACK OUT OF BOUNDS");

    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);

    int subtract_from = args.back();
    args.pop_back();
    int subtract_value = args.back();

    vm.push(subtract_from - subtract_value);
}

void exec_mul(int arg, stack<int>& vm) {
    if(vm.size() < ARITHMETIC_ARG_COUNT)
        throw invalid_argument("[ADD] STACK OUT OF BOUNDS");

    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);
    int product = 1;

    while(!args.empty()) {
        product *= args.back();
        args.pop_back();
    }

    vm.push(product);
}

void exec_div(int arg, stack<int>& vm) {
   if(vm.size() < ARITHMETIC_ARG_COUNT)
        throw invalid_argument("[ADD] STACK OUT OF BOUNDS");

    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);

    int divide_value = args.back();
    args.pop_back();
    int divide_by = args.back();

    vm.push((int)(divide_value / divide_by));
}

/**
 * opcode definitions 
 */
struct Instruction push = {PUSH_OPCODE, "push", PUSH_ARG_COUNT, exec_push};
struct Instruction add = {ADD_OPCODE, "add", ARITHMETIC_ARG_COUNT, exec_add};
struct Instruction sub = {SUB_OPCODE, "sub", ARITHMETIC_ARG_COUNT, exec_sub};
struct Instruction mul = {MUL_OPCODE, "mul", ARITHMETIC_ARG_COUNT, exec_mul};
struct Instruction _div = {DIV_OPCODE, "div", ARITHMETIC_ARG_COUNT, exec_div};

/**
 * instruction table init 
 */
map<int, struct Instruction> instructions_table = {
    {PUSH_OPCODE, push},
    {ADD_OPCODE, add},
    {SUB_OPCODE, sub},
    {MUL_OPCODE, mul},
    {DIV_OPCODE, _div}
};

/**
 * util functions for instruction table
 */
struct Instruction find_instruction_by_opcode(int opcode) {
    if (instructions_table.find(opcode) == instructions_table.end()) {
        throw invalid_argument("OPCODE NOT FOUND:" + to_string(opcode));
    } else {
        return instructions_table.at(opcode);
    }
}