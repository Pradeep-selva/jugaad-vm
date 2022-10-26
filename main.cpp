#include "source.h"

#include<bits/stdc++.h>
using namespace std;

int add(vector<int> args) {
    int sum = 0;

    while(!args.empty()) {
        sum+=args.back();
        args.pop_back();
    }

    return sum;
}

int main() {
    stack<int> vm;

    cout<<"push 1"<<endl;
    vm.push(1);
    cout<<"push 2"<<endl;
    vm.push(2);
    cout<<"add"<<endl;

    struct Instruction ins = {0,"add",2,add};
    cout<<"-------"<<endl;

    vector<int> args;
    int num_args = ins.num_args;
    while(num_args--) {
        args.push_back(vm.top());
        vm.pop();
    }

    cout<<"Result of "<<ins.name<<" is "<<ins.execute(args);
    return 0;
}