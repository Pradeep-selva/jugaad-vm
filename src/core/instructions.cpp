#include "instructions.h"

#include<bits/stdc++.h>
#include <stdexcept>

using namespace std;

/*
 * opcodes for instructions
*/
// stack ops
const int IDLE_OPCODE = -1;
const int PUSH_OPCODE = 0;
// arithmetic ops
const int ADD_OPCODE = 1;
const int SUB_OPCODE = 2;
const int MUL_OPCODE = 3;
const int DIV_OPCODE = 4;
// rel ops
const int EQ_OPCODE = 5;
const int NEQ_OPCODE = 6;
const int LT_OPCODE = 7;
const int LTE_OPCODE = 8;
const int GT_OPCODE = 9;
const int GTE_OPCODE = 10;

// arg counts for opcodes
const int PUSH_ARG_COUNT = 0;
const int ARITHMETIC_ARG_COUNT = 2;

/**
 * executor helpers
 */
vector<int> pop_vm_elements(stack<int>& vm, int num_args) {
    vector<int> args;

    while(num_args--) {
        args.push_back(vm.top());
        vm.pop();
    }

    return args;
}

void validate_arg_count(stack<int> vm, int num_args = ARITHMETIC_ARG_COUNT) {
    if(vm.size() < num_args)
        throw invalid_argument("[ADD] STACK OUT OF BOUNDS");
}

/**
 * opcode executor functions
 */
int exec_idle(int arg, stack<int>& vm) {
    return 0;
}

int exec_push(int arg, stack<int>& vm) {
    vm.push(arg);
    return 0;
}

int exec_add(int arg, stack<int>& vm) {
    validate_arg_count(vm);

    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);
    int sum = 0;

    while(!args.empty()) {
        sum += args.back();
        args.pop_back();
    }

    vm.push(sum);
    return sum;
}

int exec_sub(int arg, stack<int>& vm) {
   validate_arg_count(vm); 

    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);
    int result = args[1] - args[0];

    vm.push(result);
    return result;
}

int exec_mul(int arg, stack<int>& vm) {
    validate_arg_count(vm);

    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);
    int product = 1;

    while(!args.empty()) {
        product *= args.back();
        args.pop_back();
    }

    vm.push(product);
    return product;
}

int exec_div(int arg, stack<int>& vm) {
   validate_arg_count(vm);

    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);
    int result = (int)(args[1] / args[0]);

    vm.push(result);
    return result;
}

int exec_eq(int arg, stack<int>& vm) {
    validate_arg_count(vm);
    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);

    vm.push(
        args[1] == args[0] ? 1 : 0
    );
    return 0;
}

int exec_neq(int arg, stack<int>& vm) {
    validate_arg_count(vm);
    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);

    vm.push(
        args[1] != args[0] ? 1 : 0
    );
    return 0;
}

int exec_lt(int arg, stack<int>& vm) {
    validate_arg_count(vm);
    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);

    vm.push(
        args[1] < args[0] ? 1 : 0
    );
    return 0;
}

int exec_lte(int arg, stack<int>& vm) {
    validate_arg_count(vm);
    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);

    vm.push(
        args[1] <= args[0] ? 1 : 0
    );
    return 0;
}

int exec_gt(int arg, stack<int>& vm) {
    validate_arg_count(vm);
    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);

    vm.push(
        args[1] > args[0] ? 1 : 0
    );
    return 0;
}

int exec_gte(int arg, stack<int>& vm) {
    validate_arg_count(vm);
    vector<int> args = pop_vm_elements(vm, ARITHMETIC_ARG_COUNT);

    vm.push(
        args[1] >= args[0] ? 1 : 0
    );
    return 0;
}

/**
 * opcode definitions 
 */
// stack ops
struct Instruction push = {PUSH_OPCODE, "push", PUSH_ARG_COUNT, false, exec_push};
struct Instruction idle = {IDLE_OPCODE, "idle", PUSH_ARG_COUNT, false, exec_idle};
// arithmetic ops
struct Instruction add = {ADD_OPCODE, "add", ARITHMETIC_ARG_COUNT, true, exec_add};
struct Instruction sub = {SUB_OPCODE, "sub", ARITHMETIC_ARG_COUNT, true, exec_sub};
struct Instruction mul = {MUL_OPCODE, "mul", ARITHMETIC_ARG_COUNT, true, exec_mul};
struct Instruction _div = {DIV_OPCODE, "div", ARITHMETIC_ARG_COUNT, true, exec_div};
// rel ops
struct Instruction eq = {EQ_OPCODE, "eq", ARITHMETIC_ARG_COUNT, false, exec_eq};
struct Instruction neq = {NEQ_OPCODE, "neq", ARITHMETIC_ARG_COUNT, false, exec_neq};
struct Instruction lt = {LT_OPCODE, "lt", ARITHMETIC_ARG_COUNT, false, exec_lt};
struct Instruction lte = {LTE_OPCODE, "lte", ARITHMETIC_ARG_COUNT, false, exec_lte};
struct Instruction gt = {GT_OPCODE, "gt", ARITHMETIC_ARG_COUNT, false, exec_gt};
struct Instruction gte = {GTE_OPCODE, "gte", ARITHMETIC_ARG_COUNT, false, exec_gte};

/**
 * instruction table init 
 */
map<int, struct Instruction> instructions_table = {
    {IDLE_OPCODE, idle},
    {PUSH_OPCODE, push},
    {ADD_OPCODE, add},
    {SUB_OPCODE, sub},
    {MUL_OPCODE, mul},
    {DIV_OPCODE, _div},
    {EQ_OPCODE, eq},
    {NEQ_OPCODE, neq},
    {LT_OPCODE, lt},
    {LTE_OPCODE, lte},
    {GT_OPCODE, gt},
    {GTE_OPCODE, gte}
};

/**
 * util functions for instruction table
 */
struct Instruction find_instruction_by_opcode(int opcode) {
    if (instructions_table.find(opcode) == instructions_table.end()) {
        throw invalid_argument("OPCODE NOT FOUND:" + to_string(opcode));
    }
    
    return instructions_table.at(opcode);
}