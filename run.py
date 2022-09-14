import os
import json
import shutil
from colorama import Fore, Style

if not os.path.exists('Saved Data/dna_spectral_representation.npy'):
    print(Fore.GREEN + 'Pre-precessing the dataset...\n')
    print(Style.RESET_ALL)
    os.system('jupyter nbconvert --execute --to notebook --inplace "Code/2-pre-processing.ipynb"')

print(Fore.GREEN + 'Training the model...')
print(Style.RESET_ALL)
os.system('jupyter nbconvert --log-level CRITICAL --execute --to notebook --inplace "Code/3-model.ipynb"')


os.system('jupyter nbconvert --log-level CRITICAL --execute --to notebook --inplace "Code/4-model_assessment.ipynb"')
json_file = open('Saved Data/Temp Data/python_model.json', 'r')
data = json.load(json_file)
accuracy = data['accuracy']
precision = data['precision']
recall = data['recall']
F1_score = data['f1']

print(f'Python model metrics:\nClassification Accuracy = {round(accuracy * 100, 2)}%\nPrecision = {round(precision * 100, 2)}%\nRecall = {round(recall * 100, 2)}%\nF1 Score = {round(F1_score * 100, 2)}%\n')
json_file.close()
os.remove('Saved Data/Temp Data/python_model.json')

os.system('python "Saved Data/Test Set/save_test_set.py"')

print(Fore.GREEN + 'Converting the Python model into C++ model...')
print(Style.RESET_ALL)
os.system('python "Code/C++ Model/keras_export/convert_model.py" "Saved Data/Model Architecture/model.h5" "Saved Data/Model Architecture/model.json"')

os.chdir('Code/C++ Model/Code')

if os.path.exists('build'):
    # os.system('rd "build" -recurse -force')
    # os.rmdir('build')
    shutil.rmtree('build', ignore_errors=True)

os.system('mkdir build')
os.chdir('build')

print(Fore.GREEN + '\nCompiling the C++ model...')
print(Style.RESET_ALL)
os.system('cmake .. -G "MinGW Makefiles"')
os.system('cmake --build .')
os.chdir('../')
print(Fore.GREEN + '\nRunning C++ model...')
print(Style.RESET_ALL)
os.system('.\\build\\DNA_Sequence_Classifier_run.exe')
os.chdir('../../../Saved Data/Predicted Labels')
os.system('python "compare.py"')