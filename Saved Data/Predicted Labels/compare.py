import numpy as np

cpp_model_results = np.loadtxt('c++_model.txt')
python_model_results = np.loadtxt('python_model.txt')

print(f"Number of diffrently classified sequences in the two models is {(cpp_model_results != python_model_results).sum()}")