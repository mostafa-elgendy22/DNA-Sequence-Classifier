import numpy as np

cpp_model_results = np.loadtxt('../../Code/C++ Model/Code/data/c++_model.txt')
python_model_results = np.loadtxt('python_model.txt')

different_classified_sequences = (cpp_model_results != python_model_results).sum()
if different_classified_sequences == 0:
    print('\nC++ and Python models classified the sequences in the same way.\n')
else:
    print(f'\nC++ and Python models classified {different_classified_sequences} sequences in differently.\n')