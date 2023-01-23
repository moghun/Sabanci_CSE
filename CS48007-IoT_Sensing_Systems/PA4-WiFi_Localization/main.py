#Muhammed Orhun Gale - 26754

import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from itertools import cycle
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import make_scorer, confusion_matrix, f1_score, precision_score, accuracy_score,mean_squared_error
from xgboost import XGBClassifier


#Read location data and label them with room_ids
def read_location_data(input_text):
  data = pd.read_csv(input_text, sep=", ", header=None, engine='python')

  #Set columns
  data.columns = ["SSID", "BSS", "RSSI", "Channel", "Time"]
  data.drop([0], axis=0, inplace=True)

  #Set column data types
  data['SSID'] = data['SSID'].str.strip("\"").astype(str)
  data['BSS'] = data['BSS'].str.strip("\"").astype(str)
  data['RSSI'] = data['RSSI'].str.strip("\"").astype(int)
  data['Channel'] = data['Channel'].str.strip("\"").astype(int)
  data['Time'] = data['Time'].str.strip("\"").astype(str)

  #Set location label for each data point
  x = (input_text.split("_")[1])
  data['Location']  = x.split("-1")[0]

  return data


#Create data frames
g015 = read_location_data("./Data/fens_g015-1.txt")
g029 = read_location_data("./Data/fens_g029-1.txt")
g032 = read_location_data("./Data/fens_g032-1.txt")
g035 = read_location_data("./Data/fens_g035-1.txt")
g048 = read_location_data("./Data/fens_g048-1.txt")
g070 = read_location_data("./Data/fens_g070-1.txt")
g077 = read_location_data("./Data/fens_g077-1.txt")
l045 = read_location_data("./Data/fens_l045-1.txt")
l_1068 = read_location_data("./Data/fens_1068-1.txt")
simit = read_location_data("./Data/fens_simit-sarayi-1.txt")

#Merge all data frames into one
location_data = pd.concat([g015, g029, g032, g035, g048, g070, g077, l045, l_1068, simit])

print("Unique Networks", "\n")
print(location_data["SSID"].value_counts(), "\n")

print("Unique MAC addresses", "\n")
print(location_data["BSS"].value_counts(), "\n")

print("Unique Locations", "\n")
print(location_data["Location"].value_counts())


#Enumerate unique locations and MAC addresses
location_mapping = {k: v for v, k in enumerate(location_data['Location'].unique())}
location_data['Location'] = location_data['Location'].map(location_mapping)

mac_mapping = {k: v for v, k in enumerate(location_data['BSS'].unique())}
location_data['BSS'] = location_data['BSS'].map(mac_mapping)

location_data = location_data.drop(columns=['Time'])
location_data = location_data.drop(columns=['SSID'])

#Create X and target variable y
X = location_data.drop(columns=['Location'])
y = location_data[['Location']]

print(" Shape of X and Y:", X.shape, y.shape)

#Split the data for testing phase
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

print(" Shape of training set:", X_train.shape, "\n", "Shape of test set: ", X_test.shape)

#Random Forest Classifier
print("\n*----------TRAINING-------------*")
print("Random Forest Classifier\n")
scorer = make_scorer(f1_score, average='macro')

rfc = RandomForestClassifier()

print("Training the model\n")

#Cross-validation for parameter selection

param_grid = { 
    'n_estimators': [10,20,50,100],
    'max_features': ['sqrt', 'log2'],
    'max_depth':[5, 10, 20, 50],
    'criterion' :['gini', 'entropy'],
}

grid = GridSearchCV(rfc,
                    param_grid, 
                    cv=8,
                    scoring=scorer,
                    n_jobs=4,
                    return_train_score=False, 
                    verbose=1, 
                    refit=True)

grid_search_rfc = grid.fit(X_train, y_train.values.ravel())

print("\nBest estimator:", grid_search_rfc.best_estimator_)
print("\n*----------TESTING-------------*")

#Conduct test with splitted test data
print("\nTesting with", X_test.shape[0], "data points")
predictions_rfc = grid_search_rfc.predict(X_test)
confusion_rfc = confusion_matrix(y_test, predictions_rfc)
print("\n","Confusion Matrix:", "\n", confusion_rfc, "\n\n")

def Average(lst):
    return sum(lst) / len(lst)

#Get True Positive, False Positive, False Positive, False Negative counts by using the confusion matrix
FP = confusion_rfc.sum(axis=0) - np.diag(confusion_rfc)  
FN = confusion_rfc.sum(axis=1) - np.diag(confusion_rfc)
TP = np.diag(confusion_rfc)
TN = confusion_rfc.sum() - (FP + FN + TP)

print("\n True Positive:", sum(TP), "\n", "False Positive:", sum(FP), "\n", "True Negative:", sum(TN), "\n", "False Negative:", sum(FN), "\n")

#Calculate Mean Squared Error, Accuracy, Recall, Specificity, Precision and f1_score
mse = mean_squared_error(y_test, predictions_rfc)
accuracy = accuracy_score(y_test, predictions_rfc)
recall = TP/(TP+FN)
specificity = TN/(TN+FP) 
precision = TP/(TP+FP)
f1s = (2*precision*recall)/(precision+recall)


print(      "\n Mean Squared Error:", mse, "\n\n", 
            "Accuracy:", accuracy, "\n\n", 
            "Precission:", Average(precision), "\n\n", 
            "Recall:", Average(recall), "\n\n", 
            "Specificity:", Average(specificity), "\n\n", 
            "F1 Score:", Average(f1s), "\n")

print("\n*-----------------------*")


