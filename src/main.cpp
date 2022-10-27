#include "config/globals.h"

#include "core/instructions.h"
#include "core/labels.h"
#include "core/common.h"

#include<bits/stdc++.h>
#include <stdexcept>
#include<boost/algorithm/string.hpp>

using namespace std;

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

        if(line == "" || line == "\n") continue;

        if(line == MAIN_ENTRYPOINT) {
            has_entered_main = true;
            continue;
        }

        if(has_entered_main) {
            if(tokens.size() > 2 || tokens.size() < 1)
                throw invalid_argument("[PARSER] INVALID NUMBER OF TOKENS RECEIVED");

            int opcode = stoi(tokens.at(0));
            string raw_operand = tokens.size() == 2 ? tokens.at(1): "#0";
            
            int operand;
            if(raw_operand[0] == '#') {
               string relevant_operand = extract_operand(raw_operand);
               
               if(!all_of(relevant_operand.begin(), relevant_operand.end(), ::isdigit))
                throw invalid_argument("[PARSER] # OPERAND CAN ONLY CONTAIN DIGITS"); 

                operand = stoi(relevant_operand);
            } else if (raw_operand[0] == '@') {
                string relevant_operand = extract_operand(raw_operand);
                operand = get_operand_from_label_if_exists(labels, relevant_operand);
            } else {
                throw invalid_argument("[PARSER] INVALID OPERAND PROVIDED. DOES NOT START WITH '@' OR '#'");
            }

            struct Instruction instruction = find_instruction_by_opcode(opcode);
            instruction.execute(operand, vm);

            cout<<"[OPERATION EXEC] "<<instruction.name<<endl;
        } else {
            if(tokens.size() != 2 || !all_of(tokens.at(1).begin(), tokens.at(1).end(), ::isdigit))
                throw invalid_argument("[PARSER] INVALID INPUT OF LABELS");

            insert_label_if_unique(labels, make_pair(tokens.at(0), stoi(tokens.at(1))));
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