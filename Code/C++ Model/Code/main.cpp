#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <fdeep/fdeep.hpp>

// Program parameters
const int k = 5;
std::vector<char> dna_sequence_char_set = {'A', 'C', 'G', 'T'};


// ======================================================================================================================================================
// Pre-processing module

void find_all_dna_subsequences_recursive(std::vector<char>* set, std::string prefix, int n, int size, std::vector<std::string>* vec) {
    if (size == 0) {
        vec->push_back(prefix);
        return;
    }

    for (int i = 0; i < n; i++) {
        std::string newPrefix = prefix + set->at(i);
        find_all_dna_subsequences_recursive(set, newPrefix, n, size - 1, vec);
    }
}

std::vector<std::string> find_all_dna_subsequences(std::vector<char>* set, int size) {
    int n = set->size();
    std::vector<std::string> vec;
    find_all_dna_subsequences_recursive(set, "", n, size, &vec);
    return vec;
}


std::vector<std::string> k_mers(std::string& dna_sequence) {
    int n = dna_sequence.length();
    std::vector<std::string> k_mers;
    for (int i = 0; i < n - k + 1; i++) {
        k_mers.push_back(dna_sequence.substr(i, k));
    }
    return k_mers;
}

std::vector<std::string> remove_undefined_k_mers(std::vector<std::string>& k_mers) {
    std::vector<std::string> filtered_k_mers;

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

std::vector<float> spectral_representation(std::vector<std::string>& k_mers, std::vector<std::string>& dna_subsequences) {
    std::map<std::string, float> spectral_representation;
    for (int i = 0; i < dna_subsequences.size(); i++) {
        spectral_representation[dna_subsequences[i]] = 0;
    }
    for (int i = 0; i < k_mers.size(); i++) {
        spectral_representation[k_mers[i]]++;
    }
    std::vector<float> spectral_representation_vector;
    for (auto i : spectral_representation) {
        spectral_representation_vector.push_back(i.second);
    }
    return spectral_representation_vector;
}

// ======================================================================================================================================================

// Find the argmax of a vector
int argmax(std::vector<float> const &vec)
{
    float max = vec[0];
    int max_index = 0;
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] > max)
        {
            max = vec[i];
            max_index = i;
        }
    }
    return max_index;
}


// Calculate the accuracy of the model
float calculate_accuracy(std::vector<int>& y_pred, std::vector<int>& y_test) {
    int correctly_classified_patterns = 0;
    for (int i = 0; i < y_pred.size(); i++) {
        if (y_pred[i] == y_test[i]) {
            correctly_classified_patterns++;
        }
    }
    return ((float)correctly_classified_patterns / y_pred.size()) * 100;
}

// Predict the label of a single element from the test set
int predict(std::vector<float>& dna_sequence, fdeep::model& model) {
    auto result = model.predict({fdeep::tensor(fdeep::tensor_shape(static_cast<std::size_t>(dna_sequence.size()), 1), dna_sequence)});
    
    std::vector<float> class_probabilities;
    for (auto j : result)
    {
        class_probabilities = j.to_vector();
    }

    return argmax(class_probabilities);
}

int main()
{
    // Load the saved model
    fdeep::model model = fdeep::load_model("data/model.json");

    // Read the test set (X_test)
    std::ifstream X_test_file("data/X_test.dat");
    int num_test_sequences;
    X_test_file >> num_test_sequences;
    std::vector<std::string> X_test(num_test_sequences);
    for (int i = 0; i < num_test_sequences; i++) {
        X_test_file >> X_test[i];
    }

    // Read the labels of the test set (y_test)
    std::ifstream y_train_file("data/y_test.dat");
    std::vector<int> y_test(num_test_sequences);
    for (int i = 0; i < num_test_sequences; i++)
    {
        y_train_file >> y_test[i];
    }
    

    // Pre-process the test set
    std::vector<std::string> dna_subsequences = find_all_dna_subsequences(&dna_sequence_char_set, k);
    std::vector<std::vector<float>> X_test_preprocessed(num_test_sequences);
    for (int i = 0; i < num_test_sequences; i++) {
        std::vector<std::string> temp = k_mers(X_test[i]);
        std::vector<std::string> k_mers = remove_undefined_k_mers(temp);
        X_test_preprocessed[i] = spectral_representation(k_mers, dna_subsequences);
    }   
   


    // Predict the class of each pattern in the test set
    std::vector<int> y_pred(num_test_sequences);
    for (int i = 0; i < num_test_sequences; i++)
    {
        y_pred[i] = predict(X_test_preprocessed[i], model);
    }


    // Print the predicted labels in a file for comparison withe the Python model
    std::ofstream predicted_labels_file("data/c++_model.txt");
    for (int i = 0; i < num_test_sequences; i++)
    {
        predicted_labels_file << y_pred[i] << "\n";
    }

    std::cout << "Classification Accuracy = " << calculate_accuracy(y_pred, y_test) << "%\n";

    return 0;
}