#include "labels.h"

#include<bits/stdc++.h>
#include <stdexcept>

using namespace std;

string extract_operand(string raw_operand) {
    return raw_operand.substr(1, raw_operand.length()-1);
}

void check_label(std::map<std::string, int> labels, string key, bool is_unique) {
    if ((labels.find(key) != labels.end() && is_unique) || (labels.find(key) == labels.end() && !is_unique)) {
        throw invalid_argument("[PARSER] INVALID LABEL, (already in use or not found):" + key);
    }
}

int get_operand_from_label_if_exists(map<string, int> labels, string label) {
    check_label(labels, label, false);
    return labels.at(label);
}

void insert_label_if_unique(map<string, int>& labels, pair<string, int> data) {
    check_label(labels, data.first, true);
    labels.insert(data);
}