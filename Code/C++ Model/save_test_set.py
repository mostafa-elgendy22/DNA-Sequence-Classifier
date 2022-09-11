import numpy as np

def save_np_array(x, filename):
    file = open(filename, 'w')
    if len(x.shape) == 1:
        rows = 1
        cols = x.shape[0]
        x = x.reshape(rows, cols)
    else:
        rows = x.shape[0]
        cols = x.shape[1]
    file.write(f"{rows} {cols}\n")
    for i in range(rows):
        for j in range(cols):
            file.write(f"{x[i][j]} ")
        file.write("\n")

X_test = np.load('../../Saved Data/Test Set/X_test.npy')
save_np_array(X_test, '../../Saved Data/Test Set/X_test.dat')

y_test = np.load('../../Saved Data/Test Set/y_test.npy')
np.savetxt('../../Saved Data/Test Set/y_test.dat', y_test, fmt='%d')