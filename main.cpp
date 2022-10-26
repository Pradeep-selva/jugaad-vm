#include "instructions.h"

#include<bits/stdc++.h>
using namespace std;

void traverse_stack(stack<int> & st) {
    if(st.empty())
        return;
    int x = st.top();
    cout << x << " ";
    st.pop();
    traverse_stack(st);
    st.push(x);
}

int main() {
    stack<int> vm;

    cout<<"0 1"<<endl;
    cout<<"0 2"<<endl;
    cout<<"1"<<endl;
    cout<<"---------"<<endl;

    struct Instruction push = find_instruction_by_opcode(0);
    struct Instruction add = find_instruction_by_opcode(1);

    push.execute(1, vm);
    push.execute(2, vm);

    cout<<"INITIAL STATE\n";
    traverse_stack(vm);

    cout<<endl<<endl;

    cout<<"FINAL STATE\n";
    add.execute(0, vm);
    traverse_stack(vm);

    return 0;
}