#include "labels.h"

#include<bits/stdc++.h>
#include <stdexcept>

using namespace std;

string extract_operand(string raw_operand) {
    return raw_operand.substr(1, raw_operand.length()-1);
}

int get_operand_from_label_if_exists(map<string, int> labels, string label) {
    if (labels.find(label) == labels.end()) {
        throw invalid_argument("[PARSER] LABEL NOT FOUND:" + label);
    }
    
    return labels.at(label);
}

void insert_label_if_unique(map<string, int>& labels, pair<string, int> data) {
    if (labels.find(data.first) != labels.end()) {
        throw invalid_argument("[PARSER] LABEL NOT UNIQUE:" + data.first);
    }

    labels.insert(data);
}