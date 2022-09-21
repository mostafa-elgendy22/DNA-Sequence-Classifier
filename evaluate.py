import os
import json
import sys

if os.path.exists('Saved Data/dna_spectral_representation.npy'):
    os.remove('Saved Data/dna_spectral_representation.npy')

os.system('jupyter nbconvert --log-level CRITICAL --execute --to notebook --inplace "Code/2-pre-processing.ipynb"')

iterations = int(sys.argv[2])

accuracy = []
precision = []
recall = []
F1_score = []
AUC_score = []


for i in range(iterations):

    os.chdir('Saved Data')
    os.system('python "clean.py"')
    os.chdir('..')

    # Train the model
    os.system('jupyter nbconvert --execute --to notebook --inplace "Code/3-model.ipynb"')


    # Evaluate the model
    os.system('jupyter nbconvert --execute --to notebook --inplace "Code/4-model_assessment.ipynb"')

    json_file = open('Saved Data/Temp Data/python_model.json', 'r')
    data = json.load(json_file)

    accuracy.append(data['accuracy'])
    precision.append(data['precision'])
    recall.append(data['recall'])
    F1_score.append(data['f1'])
    AUC_score.append(data['auc'])


    json_file.close()


print(f'\nAverage Classification Accuracy = {round((sum(accuracy) / iterations) * 100, 2)}%\nAverage Precision = {round((sum(precision) / iterations) * 100, 2)}%\nAverage Recall = {round((sum(recall) / iterations) * 100, 2)}%\nAverage F1 Score = {round((sum(F1_score) / iterations), 2)}%\nAverage AUC Score = {round((sum(AUC_score) / iterations), 2)}\n')
print(f'\nMaximum Classification Accuracy = {round(max(accuracy) * 100, 2)}%\nMaximum Precision = {round(max(precision) * 100, 2)}%\nMaximum Recall = {round(max(recall) * 100, 2)}%\nMaximum F1 Score = {round(max(F1_score), 2)}%\nMaximum AUC Score = {round(max(AUC_score), 2)}\n')
print(f'\nMinimum Classification Accuracy = {round(min(accuracy) * 100, 2)}%\nMinimum Precision = {round(min(precision) * 100, 2)}%\nMinimum Recall = {round(min(recall) * 100, 2)}%\nMinimum F1 Score = {round(min(F1_score), 2)}%\nMinimum AUC Score = {round(min(AUC_score), 2)}\n')