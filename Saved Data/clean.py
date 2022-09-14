import os
import shutil

shutil.rmtree('Model', ignore_errors=True)
os.mkdir('Model')

shutil.rmtree('Model Architecture', ignore_errors=True)
os.mkdir('Model Architecture')

if os.path.exists('Predicted Labels/c++_model.txt'):
    os.remove('Predicted Labels/c++_model.txt')

if os.path.exists('Predicted Labels/python_model.txt'):
    os.remove('Predicted Labels/python_model.txt')

if os.path.exists('Temp Data/python_model.json'):
    os.remove('Temp Data/python_model.json')

if os.path.exists('Test Set/X_test.dat'):
    os.remove('Test Set/X_test.dat')

if os.path.exists('Test Set/X_test.npy'):
    os.remove('Test Set/X_test.npy')

if os.path.exists('Test Set/y_test.dat'):
    os.remove('Test Set/y_test.dat')

if os.path.exists('Test Set/y_test.npy'):
    os.remove('Test Set/y_test.npy')