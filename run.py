import os
import json
import shutil
from colorama import Fore, Style

os.chdir('Saved Data')
os.system('python "clean.py"')
os.chdir('..')

# Pre-process the dataset
print(Fore.GREEN + 'Pre-processing the dataset... ' + Style.RESET_ALL)
os.system('python -m nbconvert --log-level CRITICAL --execute --to notebook --inplace "Code/2-pre-processing.ipynb"')
print('Pre-processing done!\n')

# Train the model
print(Fore.GREEN + 'Training the model...' + Style.RESET_ALL)
os.system('python -m nbconvert --log-level CRITICAL --execute --to notebook --inplace "Code/3-model.ipynb"')


# Evaluate the model
os.system('python -m nbconvert --log-level CRITICAL --execute --to notebook --inplace "Code/4-model_assessment.ipynb"')

json_file = open('Saved Data/Temp Data/python_model.json', 'r')
data = json.load(json_file)

accuracy = data['accuracy']
precision = data['precision']
recall = data['recall']
F1_score = data['f1']
AUC_score = data['auc']


json_file.close()
# os.remove('Saved Data/Temp Data/python_model.json')
print(f'Python model metrics:\nClassification Accuracy = {round(accuracy * 100, 2)}%\nPrecision = {round(precision * 100, 2)}%\nRecall = {round(recall * 100, 2)}%\nF1 Score = {round(F1_score, 2)}\nAUC Score = {round(AUC_score, 2)}\n')


# Convert the test set from .npy format to .dat format
os.system('python "Saved Data/Test Set/save_test_set.py"')


# Convert the Python model to C++ model
print(Fore.GREEN + 'Converting the Python model into C++ model...' + Style.RESET_ALL)
os.system('python "Code/C++ Model/keras_export/convert_model.py" "Saved Data/Model Architecture/model.h5" "Code/C++ Model/Code/data/model.json"')

# Compile the C++ model
print(Fore.GREEN + '\nCompiling the C++ model...' + Style.RESET_ALL)

os.chdir('Code/C++ Model/Code')
if os.path.exists('build'):
    # os.system('rd "build" -recurse -force')
    shutil.rmtree('build', ignore_errors=True)

os.system('mkdir build')
os.chdir('build')

os.system('cmake .. -G "MinGW Makefiles"')
os.system('cmake --build .')


# Run the C++ model
print(Fore.GREEN + '\nRunning the C++ model...' + Style.RESET_ALL)
os.chdir('../')
os.system('.\\build\\DNA_Sequence_Classifier_run.exe')


# Check if both models classifies the test dataset in the same way
os.chdir('../../../Saved Data/Predicted Labels')
os.system('python "compare.py"')