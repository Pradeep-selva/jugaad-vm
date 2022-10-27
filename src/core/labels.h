#include<string>
#include<map>

#ifndef EXTRACT_OPERAND_H
#define EXTRACT_OPERAND_H

std::string extract_operand(std::string raw_operand);

#endif

#ifndef GET_LABEL_VALUE_H
#define GET_LABEL_VALUE_H

int get_operand_from_label_if_exists(std::map<std::string, int> labels, std::string label);

#endif

#ifndef INSERT_LABEL_H
#define INSERT_LABEL_H

void insert_label_if_unique(std::map<std::string, int>& labels, std::pair<std::string, int> data);

#endif



