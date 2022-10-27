#include "config/globals.h"

#include "core/instructions.h"
#include "core/labels.h"
#include "core/common.h"
#include "core/validators.h"

#include <stdexcept>
#include<bits/stdc++.h>
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
            check_token_size(tokens);

            int operand;
            int opcode = stoi(tokens.at(0));

            string raw_operand = tokens.size() == 2 ? tokens.at(1): SKIP_WRITE_OPERAND;
            string relevant_operand = extract_operand(raw_operand);            

            switch(raw_operand[0]) {
                case '#':
                    if(!is_token_numeric(relevant_operand))
                        throw invalid_argument("[PARSER] # OPERAND CAN ONLY CONTAIN DIGITS"); 

                    operand = stoi(relevant_operand);
                    break;
                
                case '@':
                    operand = get_operand_from_label_if_exists(labels, relevant_operand);
                    break;

                case '>':
                    operand = 0;
                    break;

                default:
                    throw invalid_argument(
                        "[PARSER] INVALID OPERAND PROVIDED. DOES NOT START WITH '@', '#', '>'"
                    );
            }

            struct Instruction instruction = find_instruction_by_opcode(opcode);
            int op_result = instruction.execute(operand, vm);

            if(instruction.write_to_label && raw_operand != SKIP_WRITE_OPERAND) {
                insert_label_if_unique(
                    labels, 
                    make_pair(relevant_operand, op_result)
                );
                cout<<"[LABEL] WRITTEN OP RESULT TO: "<<relevant_operand<<endl;
            }

            cout<<"[OPERATION EXEC] "<<instruction.name<<endl;
        } else {
            if(tokens.size() != 2 || !is_token_numeric(tokens.at(1)))
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