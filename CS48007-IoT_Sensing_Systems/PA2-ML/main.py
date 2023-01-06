#Muhammed Orhun Gale - 26754
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import LinearSVC
from itertools import cycle
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import confusion_matrix, f1_score, make_scorer, precision_score, recall_score

"""##Read Data into DataFrame

Features
"""
#Read features to create columns
activity_types = {1: 'WALKING', 2:'WALKING_UPSTAIRS',3:'WALKING_DOWNSTAIRS',4:'SITTING', 5:'STANDING',6:'LAYING'}
features = []
with open('UCI_HAR_Dataset/features.txt') as f:
    features = [line.split()[1] for line in f.readlines()]

"""Training Data"""
#Read X and y values of train data
X_train = pd.read_csv('UCI_HAR_Dataset/train/X_train.txt', header=None, delim_whitespace=True)
X_train.columns = [features]

y_train_num = pd.read_csv('UCI_HAR_Dataset/train/y_train.txt', names=['Activity']).squeeze(1)

#Map activities to their labels
y_train = y_train_num.map(activity_types)

"""Test Data"""
#Read X and y values of test data
X_test = pd.read_csv('UCI_HAR_Dataset/test/X_test.txt', header=None, delim_whitespace=True)
X_test.columns = [features]

y_test_num = pd.read_csv('UCI_HAR_Dataset/test/y_test.txt', names=['Activity']).squeeze(1)

#Map activities to their labels
y_test = y_test_num.map(activity_types)

"""##Implementing Classifiers"""
#Since this is a multi-classification task, change the average parameter from binary to macro
scorer = make_scorer(f1_score, average='macro')
print("*---------------------------------------------------------------------*")
print("Part 1 - Classification Performance")

"""###k-NN Classifier"""
#Declare classifier
knn = KNeighborsClassifier()
param_grid = {'n_neighbors':[3,5,7,9,11]} 
# loop over values of k for the k-Nearest Neighbor classifier
grid = GridSearchCV(knn,
                    param_grid, 
                    cv=5,
                    scoring= scorer,
                    return_train_score=False, 
                    verbose=0, 
                    refit=True)

print("*-----------------------*")
print("k-Nearest Neighbors Classifier\n")

print("Training the model")
#Train model
grid_search_knn = grid.fit(X_train.values, y_train)

print("Predicting\n")
#Make predictions
predictions_knn = grid_search_knn.predict(X_test.values)

#Calculate performance metrics
precision_score_knn = precision_score(y_test, predictions_knn, average='macro')
recall_score_knn = recall_score(y_test, predictions_knn, average='macro')
f1Score_knn = f1_score(y_test, predictions_knn, average='macro')
confusion_matrix_knn = confusion_matrix(y_test, predictions_knn)


print("Results:\n")
print("Precision Score:", precision_score_knn,"\nRecall Score:", recall_score_knn, "\nf1 Score:", f1Score_knn,"\n")
print("Confusion Matrix:\n",  confusion_matrix_knn, "\n",)
print("*-----------------------*\n")

"""###Support Vector Machine Classifier"""
#Train model
lsvc = LinearSVC(dual=False)
param_grid = {'C':[0.5, 1, 2]}
# loop over values of k for the Linear Support Vector Machine classifier
grid = GridSearchCV(lsvc,
                    param_grid, 
                    cv=5,
                    scoring= scorer,
                    return_train_score=False, 
                    verbose=0, 
                    refit=True)

print("*-----------------------*")
print("Linear Support Vector Machine Classifier\n")

print("Training the model")
#Train model
grid_search_LSVC = grid.fit(X_train.values, y_train)

print("Predicting\n")
#Make predictions
predictions_LSVC = grid_search_LSVC.predict(X_test.values)

#Calculate performance metrics
precision_score_lscv = precision_score(y_test, predictions_LSVC, average='macro')
recall_score_lsvc = recall_score(y_test, predictions_LSVC, average='macro')
f1Score_lsvc = f1_score(y_test, predictions_LSVC, average='macro')
confusion_matrix_lsvc = confusion_matrix(y_test, predictions_LSVC)


print("Results:\n")
print("Precision Score:", precision_score_lscv,"\nRecall Score:", recall_score_lsvc, "\nf1 Score:", f1Score_lsvc,"\n")
print("Confusion Matrix:\n",  confusion_matrix_lsvc, "\n",)
print("*-----------------------*\n")

#Pick the better model
better_model = None

if f1Score_lsvc > f1Score_knn:
  print("Linear SVM classifier is performed better with f1 score:", f1Score_lsvc)
  better_model = grid_search_LSVC

elif f1Score_lsvc < f1Score_knn:
  print("k-NN classifier is performed better with f1 score:", f1Score_knn)
  better_model = grid_search_knn

else:
  print("Both k-NN and Linear SVM classifiers get f1 score:", f1Score_lsvc)
  #Favor SVC :)
  better_model = grid_search_LSVC

print("*---------------------------------------------------------------------*\n")

"""#Part 2"""

print("*---------------------------------------------------------------------*")
print("Part 2 - Perceptron Implementation\n")

"""##Perceptron"""
#Perceptron class
class Perceptron:
  #Constructor -> training data, aiming function table, learning rates and number of inputs
  def __init__(self, table, resulting_table, learning_rate=0.01, inputs=2):
    self.table = table
    self.resulting_table = resulting_table
    self.inputs = inputs
    self.learning_rate = learning_rate

    #Initialize weights with random numbers
    self.weight = np.random.uniform(size=self.inputs)
    self.bias = -1
    self.value_map = np.zeros(self.inputs)

  #Calculate gradient
  def gradient(self, node, normal, output):
    return node * (normal - output)

  #Update weight and bias in accordance with the gradient
  def update(self, normal, output):
    #If gradient is 0, no change
    for i in range(self.inputs):
      self.weight[i] = self.weight[i] + self.learning_rate * self.gradient(self.value_map[i], normal, output)
    
    self.bias = self.bias + self.learning_rate * self.gradient(1, normal, output)

  #Pass the data to the next node --> calculate the value for new node --> activate
  def activate(self, point):
    #Take dot product of the data and add bias
    return  np.dot(self.weight, point) + self.bias

  #Itterate until reach to the aiming result table
  def train(self):
    ctr = 0
    for point, resulting_table in cycle(zip(self.table, self.resulting_table)):
      #If cannot converge, break
      if ctr == len(self.table):
        break
      
      #Evaluate the most recent version of the perceptron
      output = self.evaluate(point)
      self.value_map = point

      #If found, increment the ctr
      if output == resulting_table:
        ctr = ctr + 1
      #If did not find, update the perceptron with the error
      else:
        self.update(resulting_table, output)
        ctr = 0

  #Evaluate a point with a trained perceptron via simply calculating the activation 
  def evaluate(self, point):
    if self.activate(point) >= 0:
      return 1

    return 0


  #Get a trained Perceptron object
  def getClassifier(truth_table, resulting_table):
    operator = Perceptron(truth_table, resulting_table)
    operator.train()
    return operator

"""##Operators

Truth tables
"""
#Truth tables and outputs
truth_table = np.array([[0, 0], [0, 1], [1, 0],[1, 1]])
or_result = np.array([[0], [1], [1], [1]])
and_result = np.array([[0], [0], [0], [1]])
nand_result = np.array([[1], [1], [1], [0]])
xor_result = np.array([[0], [1], [1], [0]])

def print_basic_operator_results(name, truth_table, resulting_table):
  print(name, "result table")
  operator = Perceptron.getClassifier(truth_table, resulting_table)
  for input in truth_table:
    output = operator.evaluate(input)
    print("("+str(input[0])+"," + str(input[1]) + ") -> " + str(output))
  print("\n")

"""###OR"""

print_basic_operator_results("or_operator", truth_table, or_result)

"""###AND"""

print_basic_operator_results("and_operator", truth_table, and_result)

"""###NAND"""

print_basic_operator_results("nand_operator", truth_table, nand_result)

"""###XOR"""
#Create the XOR via combining nand, or, and operators
def xor_operator(a, b):
  #Get trained operator perceptrons
  and_operator = Perceptron.getClassifier(truth_table, and_result)
  or_operator = Perceptron.getClassifier(truth_table, or_result)
  nand_operator = Perceptron.getClassifier(truth_table, nand_result)

  #Evaluate a, b point via combining nand, or, and operators
  return and_operator.evaluate([nand_operator.evaluate((a,b)), or_operator.evaluate((a,b))])

print("xor_operator", "result table")
for input in truth_table:
  output = xor_operator(input[0], input[1])
  print("("+str(input[0])+"," + str(input[1]) + ") -> " + str(output))

print("*---------------------------------------------------------------------*\n")

"""#Part 3"""

print("*---------------------------------------------------------------------*")
print("Part 3 - XOR Operator Neural Network Implementation\n")

"""##Neural Network"""
#Neural Network class
#It has three layers -> 
      #Input Layer - 1-Hidden Layer - Output Layers
#Therefore -> gradient, weight and bias calculations are done explicitly!
class NeuralNetwork:
  #Constructor -> training data, aiming function table, learning rate, number of epochs, size of input, hidden and output
  def __init__(self, table, resulting_table, learning_rate=0.1, epochs=100, input_layer=2, hidden_layer=2, output_layer=1):
    self.table = table
    self.resulting_table = resulting_table
    self.learning_rate = learning_rate
    self.epochs = epochs

    #Initialize NN with random weights and biases
    self.input_hidden_edge_weights = np.random.uniform(size=(input_layer, hidden_layer))
    self.hidden_output_edge_weights = np.random.uniform(size=(hidden_layer, output_layer))
    self.input_hidden_bias = np.random.uniform(size=(1,hidden_layer))
    self.hidden_output_bias = np.random.uniform(size=(1,output_layer))

  #Sigmoid function
  def sigmoid(self, val):
    return (1 / (1 + np.exp(-val)))

  #Derivative of sigmoid function
  def derivatedSigmoid(self, val):
    return (val * (1 - val))

  #Pass the data to the next node --> calculate the value for new node --> activate
  def activate(self, batch):
    #First activate the hidden layer nodes
    self.hidden = np.dot(batch, self.input_hidden_edge_weights) + self.input_hidden_bias
    #Check the activation intensity --> Nearly binarized
    self.hidden_out = self.sigmoid(self.hidden)

    #Activate the output layer node
    self.output = np.dot(self.hidden_out, self.hidden_output_edge_weights) + self.hidden_output_bias
    #Decide that it is one or not --> If not the backpropagation will be used to update weights and biases
    self.final = self.sigmoid(self.output)

    return self.final

  #Update all weights and biases starting from output layer to input layer
  def backpropagate(self):
    #Calculate the error for all nodes -- Matrix subtraction
    dif_to_change = self.resulting_table - self.final

    #Calculate gradient for output layer to hidden layer
    hidden_output_gradient = self.hidden_out.T @ (self.derivatedSigmoid(self.final) * dif_to_change)

    #Calculate gradient for hidden layer to input layer
    input_hidden_gradient = self.table.T @ (((self.derivatedSigmoid(self.final)) * self.hidden_output_edge_weights.T) * self.derivatedSigmoid(self.hidden_out) * dif_to_change)

    #Update weights via using gradient
    self.input_hidden_edge_weights = self.input_hidden_edge_weights + self.learning_rate * input_hidden_gradient
    self.hidden_output_edge_weights = self.hidden_output_edge_weights + self.learning_rate * hidden_output_gradient

    #Update biases via using gradient
    self.input_hidden_bias = self.input_hidden_bias + np.sum(self.learning_rate * ((dif_to_change * self.derivatedSigmoid(self.final)) * self.hidden_output_edge_weights.T) * self.derivatedSigmoid(self.hidden_out), axis=0)
    self.hidden_output_bias = self.hidden_output_bias + np.sum(self.learning_rate * dif_to_change * self.derivatedSigmoid(self.final), axis=0)

  #Train the NN
  def train(self):
    for i in range(self.epochs):
      #Evaluate the point with the current weights and biases 
      self.activate(self.table)
      #Use backpropagation to update weights and biases via using the error
      self.backpropagate()

  #Evaluate a point with a trained NN, check the output activation value
  def evaluate(self, point):
    point = np.transpose(point)
    if self.activate(point) >= 0.5:
        return 1
    return 0

  #Get a trained NN object
  def getClassifier(truth_table, resulting_table, learning_rate, ep):
    nn = NeuralNetwork(truth_table, resulting_table, learning_rate, ep)
    nn.train()
    return nn

print("Neural Network is training for XOR operator...\n")
nn_xor_operator = NeuralNetwork.getClassifier(truth_table, xor_result, 0.01, 100000)

print("neural network taught xor_operator", "result table")
for input in truth_table:
  output = nn_xor_operator.evaluate((input[0], input[1]))
  print("("+str(input[0])+"," + str(input[1]) + ") -> " + str(output))

print("*---------------------------------------------------------------------*\n")