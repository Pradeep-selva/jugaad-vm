#include "instructions.h"

#include<bits/stdc++.h>
#include <stdexcept>

using namespace std;

// opcodes for instructions
const int PUSH_OPCODE = 0;
const int ADD_OPCODE = 1;

// arg counts for opcodes
const int PUSH_ARG_COUNT = 0;
const int ADD_ARG_COUNT = 2;

vector<int> pop_vm_elements(stack<int>& vm, int num_args) {
    vector<int> args;

    while(num_args--) {
        args.push_back(vm.top());
        vm.pop();
    }

    return args;
}

void exec_push(int arg, stack<int>& vm) {
    vm.push(arg);
}

void exec_add(int arg, stack<int>& vm) {
    if(vm.size() <= ADD_ARG_COUNT)
        throw invalid_argument("[ADD] STACK OUT OF BOUNDS");

    vector<int> args = pop_vm_elements(vm, ADD_ARG_COUNT);
    int sum = 0;

    while(!args.empty()) {
        sum+=args.back();
        args.pop_back();
    }

    vm.push(sum);
}

struct Instruction push = {PUSH_OPCODE, "push", PUSH_ARG_COUNT, exec_push};
struct Instruction add = {ADD_OPCODE, "add", ADD_ARG_COUNT, exec_add};

map<int, struct Instruction> instructions_table = {
    {ADD_OPCODE, add},
    {PUSH_OPCODE, push}
};
