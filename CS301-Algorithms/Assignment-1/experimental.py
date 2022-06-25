from timeit import default_timer as timer
import statistics


def lcs_naive(X,Y,i,j):
    if (i == 0 or j == 0):
        return 0
    elif X[i-1] == Y[j-1]:
        return 1 + lcs_naive(X,Y,i-1,j-1)
    else:
        return max(lcs_naive(X,Y,i,j-1),lcs_naive(X,Y,i-1,j))
    
def lcs_mem(X,Y,i,j):
    if c[i][j] >= 0:
        return c[i][j]
    if (i == 0 or j == 0):
        c[i][j] = 0
    elif X[i-1] == Y[j-1]:
        c[i][j] = 1 + lcs_mem(X,Y,i-1,j-1)
    else:
        c[i][j] = max(lcs_mem(X,Y,i,j-1),lcs_mem(X,Y,i-1,j))
    return c[i][j]

from timeit import default_timer as timer

arr1 = []
with open('input.txt') as f:
  lines = f.readlines()
  i = 2
  j = 5

print("\nnaive")
for num in range(30):
    X = lines[i].strip()
    Y = lines[j].strip()
    print(num, X, Y)

    start_time = timer()
    X_length = len(X)
    Y_length = len(Y)
    
    print("Length: ", X_length, Y_length)
    print ("LCS length: ", lcs_naive(X,Y,X_length,Y_length))
    end_time: float = timer()
    arr1.append(end_time - start_time)

    i += 3
    j += 3

print("----------------------------")

arr2 = []
with open('input.txt') as f:
  lines = f.readlines()
  i = 2
  j = 5
print("\nmem")
for num in range(30):
    X = lines[i].strip()
    Y = lines[j].strip()
    print(num, X, Y)

    start_time = timer()
    X_length = len(X)
    Y_length = len(Y)
    c = [[-1 for k in range(Y_length+1)] for l in range(X_length+1)]


    print("Length: ", X_length, Y_length)
    print ("LCS length: ", lcs_mem(X,Y,X_length,Y_length))
    end_time: float = timer()
    arr2.append(end_time - start_time)

    i += 3
    j += 3

print("----------------------------")

print("Experimemtal Results")

print("\nnaive")
print(len(arr1))
print("Mean:", sum(arr1)/30)
print("std:", statistics.stdev(arr1))

print("\nmem")
print(len(arr2))
print("Mean:", sum(arr2)/30)
print("std:", statistics.stdev(arr2))

import csv
from csv import writer

#with open('rand.csv', 'w') as f:
#    f.write("%s,%s,%s,%s\n"%("Algorithm","Length", "Mean", "std"))
#    f.write("%s,%s,%s,%s\n"%("Naive",5,sum(arr1)/30, statistics.stdev(arr1)))
#    f.write("%s,%s,%s,%s\n"%("Memoization",5,sum(arr2)/30, statistics.stdev(arr2)))


with open('rand.csv', 'a', newline='') as f_object:  
    writer_object = writer(f_object)
    writer_object.writerow(["Naive", 20, sum(arr1)/30, statistics.stdev(arr1)])  
    f_object.close()

with open('rand.csv', 'a', newline='') as f_object:  
    writer_object = writer(f_object)
    writer_object.writerow(["Memoization", 20, sum(arr2)/30, statistics.stdev(arr2)])  
    f_object.close()
