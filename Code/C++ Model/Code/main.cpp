#include <iostream>
#include <fstream>
#include <fdeep/fdeep.hpp>


// Load the saved model
const auto model = fdeep::load_model("data/model.json");

// Calculate a^b
int power(int a, int b) {
    int result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}


// Find the argmax of a vector
template <typename T, typename A>
int argmax(std::vector<T, A> const &vec)
{
    return static_cast<int>(std::distance(vec.begin(), max_element(vec.begin(), vec.end())));
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

int predict(std::vector<float>& dna_sequence) {
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
    // Read the test set (X_test)
    std::ifstream X_test_file("data/X_test.dat");
    int num_test_sequences, input_vector_size;
    X_test_file >> num_test_sequences >> input_vector_size;
    std::vector<std::vector<float>> X_test(num_test_sequences);
    float temp;
    for (int i = 0; i < num_test_sequences; i++)
    {
        for (int j = 0; j < input_vector_size; j++)
        {
            X_test_file >> temp;
            X_test[i].push_back(temp);
        }
    }

    // Read the labels of the test set (y_test)
    std::ifstream y_train_file("data/y_test.dat");
    std::vector<int> y_test(num_test_sequences);
    for (int i = 0; i < num_test_sequences; i++)
    {
        y_train_file >> y_test[i];
    }


    // Find the class of each pattern in the test set
    std::vector<int> y_pred(num_test_sequences);
    for (int i = 0; i < num_test_sequences; i++)
    {
        y_pred[i] = predict(X_test[i]);
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