#Muhammed Orhun Gale - 26754
#FindCyclicCitations subclass implementations

from multiprocessing import Process, Value, Array, Barrier, Semaphore
import os
import math
import time
import zmq
from abc import ABC, abstractmethod

from MapReduce import MapReduce

#A subclass of the MapReduce class
#Finds cyclic citations (cycles of length 2)
class FindCyclicReferences(MapReduce):
    #Implementetion of the abstract Map method
    def Map(self, parts):

        #Create a dictionary for each citation and initilize it with another dictionary
        citations = {}
        for paper in parts:
            citations[paper[0]] = dict()

        #If paper0 cites paper1, indicate it via making the "cited" flag 1 (logically, True)
        for paper in parts:
            citations[paper[0]][paper[1]] = 1

        return citations
        
    #Implementetion of the abstract Reduce method
    def Reduce(self, kvs):

        #Collect all results from a list of dictionaries to an inclusive dictionary
        final_result = {}
        #An intermedaite dictionary for collecting and checking items
        intermediate_result = {}

        #Initialize the intermediate dictionary for all citations with dictionaries as values
        for mapped in kvs:
            for key, value in mapped.items():
                intermediate_result[key] = dict()

        #Collect all citation information into the intermediate dictionary
        for mapped in kvs:
            for key, value in mapped.items():
                for n_key, n_value in value.items():
                    intermediate_result[key][n_key] = n_value
        
        #Check that whether a "paper0" cites a "paper1" and "paper1" cites "paper0" 
        #       via looking up to intermediate dictionary records
        for key, value in intermediate_result.items():
            for sub_key, sub_value in value.items():
                if sub_key in intermediate_result.keys():
                    if key in intermediate_result[sub_key].keys():
                        #If both cites each other, add to the final results as a sorted tuple
                        final_result[str((min(int(key), int(sub_key)), max(int(key), int(sub_key))))] = 1

        return final_result