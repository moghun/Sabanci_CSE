#Muhammed Orhun Gale - 26754
#FindCitations subclass implementations

from multiprocessing import Process, Value, Array, Barrier, Semaphore
import os
import math
import time
import zmq
from abc import ABC, abstractmethod

from MapReduce import MapReduce

#A subclass of the MapReduce class
#Finds number of citations of each paper
class FindCitations(MapReduce):
    #Implementetion of the abstract Map method
    def Map(self, parts):

        #Create a dictionary of "cited" papers for a fragment
        citation_counts = {}
        #Initialize the dictionary for all cited papers
        for paper in parts:
            citation_counts[paper[1]] = 0
        
        #Increment the number of citations if it is encountered
        for paper in parts:
            citation_counts[paper[1]] +=1

        return citation_counts
    
    #Implementetion of the abstract Reduce method
    def Reduce(self, kvs):

        #Collect all results from a list of dictionaries to an inclusive dictionary
        final_result = {}
        #Initilize the inclusive dictionary with every single element of the dictionaries that are in the kvs
        for mapped in kvs:
            for key, value in mapped.items():
                final_result[key] = 0

        #Add number of citations from each individual dictionary to get collective number of citations
        for mapped in kvs:
            for key, value in mapped.items():
                final_result[key] += value
        
        #Sort the dictionary in descending order for ease of use --> Probably will decrease the speed :)
        #return dict(sorted(final_result.items(), key=lambda x: x[1], reverse=True))

        #Dedicated to take that extra 5 points!
        return final_result