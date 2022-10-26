#include "instructions.h"

#include<bits/stdc++.h>
#include<boost/algorithm/string.hpp>
#include <stdexcept>

using namespace std;

// program sections
const string MAIN_ENTRYPOINT = "main:";

/**
 * HELPERS
 */
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

/**
 * MAIN FUNCTION
 */
int main() {
    stack<int> vm;
    map<string, int> labels;

    ifstream infile("./sample/test.noobvm");

    string line;
    bool has_entered_main = false;

    while (getline(infile, line) && line != "exit") {
        boost::trim_right(line);
        boost::trim_left(line);

        cout<<line<<endl;
        vector<string> tokens;
        tokenize(line, tokens);

        if(line == MAIN_ENTRYPOINT)
            has_entered_main = true;

        if(has_entered_main) {
            if(tokens.size() > 2 || tokens.size() < 1)
                throw invalid_argument("[PARSER] INVALID NUMBER OF TOKENS RECEIVED");

            int opcode = stoi(tokens.at(0));
            string raw_operand = tokens.size() == 2 ? tokens.at(1): "#0";
            
            int operand;
            if(raw_operand[0] == '#') {
               string relevant_operand = raw_operand.substr(1, raw_operand.length()-1);
               
               if(!all_of(relevant_operand.begin(), relevant_operand.end(), ::isdigit))
                throw invalid_argument("[PARSER] # OPERAND CAN ONLY CONTAIN DIGITS"); 

                operand = stoi(relevant_operand);
            } else if (raw_operand[0] == '@') {
                string relevant_operand = raw_operand.substr(1, raw_operand.length()-1);

                if (labels.find(relevant_operand) == labels.end()) {
                    throw invalid_argument("LABEL NOT FOUND:" + relevant_operand);
                }
                
                operand = labels.at(relevant_operand);
            } else {
                throw invalid_argument("[PARSER] INVALID OPERAND PROVIDED. DOES NOT START WITH '@' OR '#'");
            }

            struct Instruction instruction = find_instruction_by_opcode(opcode);
            instruction.execute(operand, vm);

            cout<<"[OPERATION EXEC] "<<instruction.name<<endl;
        } else {
            if(tokens.size() != 2 || !all_of(tokens.at(1).begin(), tokens.at(1).end(), ::isdigit))
                throw invalid_argument("[PARSER] INVALID INPUT OF LABELS");

            labels.insert(make_pair(tokens.at(0), stoi(tokens.at(1))));
        }
    }

    if(vm.size() > 1)
       throw invalid_argument("[EXECUTOR] COULD NOT RESOLVE TO A SINGLE OUTPUT"); 

    cout<<"\n--------------------"<<endl;

    cout<<"FINAL VM STATE\n";
    cout<<"--------------------"<<endl;
    traverse_stack(vm);

    return 0;
}