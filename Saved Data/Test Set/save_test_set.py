# This script converts the test set from .npy format to .txt format with a specific format

import numpy as np

def save_np_array(x, filename):
    file = open(filename, 'w')
    file.write(f"{x.shape[0]}\n")
    for i in range(x.shape[0]):
        file.write(f"{x[i]}\n")

X_test = np.load('Saved Data/Test Set/X_test.npy')
save_np_array(X_test, 'Code/C++ Model/Code/data/X_test.dat')

y_test = np.load('Saved Data/Test Set/y_test.npy')
np.savetxt('Code/C++ Model/Code/data/y_test.dat', y_test, fmt='%d')