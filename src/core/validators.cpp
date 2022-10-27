#include "validators.h"

#include<bits/stdc++.h>
#include <stdexcept>

using namespace std;

void check_token_size(vector<string> tokens) {
    if(tokens.size() > 2 || tokens.size() < 1)
        throw invalid_argument("[PARSER] INVALID NUMBER OF TOKENS RECEIVED");
}

void check_vm_size(stack<int> vm) {
    if(vm.size() > 1)
       throw invalid_argument("[EXECUTOR] COULD NOT RESOLVE TO A SINGLE OUTPUT"); 
}

bool is_token_numeric(string token) {
    return all_of(token.begin(), token.end(), ::isdigit);
}