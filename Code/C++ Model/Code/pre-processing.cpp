#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int k = 5;
vector<char> dna_sequence_char_set = {'A', 'C', 'G', 'T'};


void find_all_dna_subsequences_recursive(vector<char>* set, string prefix, int n, vector<string>* vec) {
    if (k == 0) {
        vec->push_back(prefix);
        return;
    }

    for (int i = 0; i < n; i++) {
        string newPrefix = prefix + set->at(i);
        find_all_dna_subsequences_recursive(set, newPrefix, n, vec);
    }
}

vector<string> find_all_dna_subsequences(vector<char>* set) {
    int n = set->size();
    vector<string> vec;
    find_all_dna_subsequences_recursive(set, "", n, &vec);
    return vec;
}


vector<string> k_mers(string dna_sequence) {
    int n = dna_sequence.length();
    vector<string> k_mers;
    for (int i = 0; i < n - k + 1; i++) {
        k_mers.push_back(dna_sequence.substr(i, k));
    }
    return k_mers;
}

vector<string> remove_undefined_k_mers(vector<string> k_mers) {
    vector<string> filtered_k_mers;

    for (int i = 0; i < k_mers.size(); i++) {
        bool is_valid = true;
        for (int j = 0; j < k_mers[i].length(); j++) {
            for (int m = 0; m < dna_sequence_char_set.size(); m++) {
                if (find(dna_sequence_char_set.begin(), dna_sequence_char_set.end(), k_mers[i][j]) == dna_sequence_char_set.end()) {
                    is_valid = false;
                    break;
                }
            }
        }
        if (is_valid) {
            filtered_k_mers.push_back(k_mers[i]);
        }
    }
    return filtered_k_mers;
}

int main() {
    // vector<string> vec = find_all_dna_subsequences(&dna_sequence_char_set);
    vector<string>v1 = {"AATA", "GGGG", "CCCC", "ATCG"};
    vector<string> vec = remove_undefined_k_mers(v1);
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << endl;
    }
    return 0;
}