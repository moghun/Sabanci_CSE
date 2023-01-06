#Muhammed Orhun Gale - 26754
#Terminal functionality to call MapReduce and subclass implementations with arguments

import sys
from MapReduce import MapReduce
from FindCitations import FindCitations
from FindCyclicReferences import FindCyclicReferences

if __name__ == '__main__':
    mode = sys.argv[1]
    num_workers = sys.argv[2]
    filename = sys.argv[3]

    if mode == "COUNT":
        map_reduce = FindCitations(int(num_workers))
        print("FindCitations is called!")
        map_reduce.start(filename)

    elif mode == "CYCLE":
        map_reduce = FindCyclicReferences(int(num_workers))
        print("FindCyclicReferences is called!")
        map_reduce.start(filename)