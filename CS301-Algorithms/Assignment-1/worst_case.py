from timeit import default_timer as timer
import statistics


def lcs_naive(X,Y,i,j):
    if c[i][j] >= 0:
        return c[i][j]
    if (i == 0 or j == 0):
        c[i][j] = 0
    elif X[i-1] == Y[j-1]:
        c[i][j] = 1 + lcs_mem(X,Y,i-1,j-1)
    else:
        c[i][j] = max(lcs_mem(X,Y,i,j-1),lcs_mem(X,Y,i-1,j))
    return c[i][j]
    
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


worst_inputs = [["aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"],["aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"],["aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"],["aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"],["aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"]]

naive_output = {5:0, 10:0, 15:0, 18:0, 20:0}

mem_output = {5:0, 10:0, 15:0, 18:0, 20:0}


for i in range(10):
    if(i < 5):
        X = worst_inputs[i][0]
        Y = worst_inputs[i][1]

        start_time = timer()
        X_length = len(X)
        Y_length = len(Y)
        c = [[-1 for k in range(Y_length+1)] for l in range(X_length+1)]
        print(X_length, Y_length)
        print ("Length of LCS is ", lcs_mem(X,Y,X_length,Y_length))
        end_time: float = timer()
        print("--- %s seconds ---" % (end_time - start_time))
        mem_output[(5*i)+5] = (end_time - start_time)
    else:
        X = worst_inputs[i-5][0]
        Y = worst_inputs[i-5][1]

        start_time = timer()
        X_length = len(X)
        Y_length = len(Y)
        print(X_length, Y_length)
        print ("Length of LCS is ", lcs_naive(X,Y,X_length,Y_length))
        end_time: float = timer()
        print("--- %s seconds ---" % (end_time - start_time))
        naive_output[(5*(i-5))+5] = (end_time - start_time)




import csv

with open('naive.csv', 'w') as f:
    for key in naive_output.keys():
        f.write("%s,%s\n"%(key,naive_output[key]))


with open('mem.csv', 'w') as f:
    for key in mem_output.keys():
        f.write("%s,%s\n"%(key,mem_output[key]))





