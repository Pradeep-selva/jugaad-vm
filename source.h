#include <string>
#include<vector>
#include<functional>

struct Instruction {
    int op_code;
    std::string name;
    int num_args;
    std::function<int (std::vector<int> args)> execute;
};