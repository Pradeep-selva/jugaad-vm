#include "instructions.h"

#include<bits/stdc++.h>
#include <stdexcept>

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

void tokenize(string const &str, vector<string> &out) {
    stringstream ss(str);
    string word;

    while (ss >> word) {
        out.push_back(word);
    }
}

int main() {
    stack<int> vm;

    cout<<"Enter bytecode to execute on stack VM (type 'exit' to exit)-"<<endl;

    string line;
    while (getline(cin, line) && line != "exit") {
        vector<string> tokens;
        tokenize(line, tokens);

        if(tokens.size() > 2 || tokens.size() < 1)
            throw invalid_argument("[PARSER] INVALID NUMBER OF TOKENS RECEIVED");

        int opcode = stoi(tokens.at(0));
        int operand = stoi(tokens.size() == 2 ? tokens.at(1): "0");

        struct Instruction instruction = find_instruction_by_opcode(opcode);
        instruction.execute(operand, vm);

        cout<<"\n[OPERATION EXEC] "<<instruction.name<<endl;
    }

    if(vm.size() > 1)
       throw invalid_argument("[EXECUTOR] COULD NOT RESOLVE TO A SINGLE OUTPUT"); 

    cout<<"\n--------------------"<<endl;

    cout<<"FINAL VM STATE\n";
    cout<<"--------------------"<<endl;
    traverse_stack(vm);

    return 0;
}