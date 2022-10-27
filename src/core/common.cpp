#include "common.h"

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