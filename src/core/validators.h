#include<vector>
#include<string>
#include<stack>

#ifndef CHECK_TOKENS_H
#define CHECK_TOKENS_H

void check_token_size(std::vector<std::string> tokens);

#endif

#ifndef CHECK_VM_H
#define CHECK_VM_H

void check_vm_size(std::stack<int> vm);

#endif

#ifndef CHECK_DIGIT_H
#define CHECK_DIGIT_H

bool is_token_numeric(std::string token);

#endif