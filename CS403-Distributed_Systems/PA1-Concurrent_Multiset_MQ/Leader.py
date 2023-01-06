#Muhammed Orhun Gale - 26754
#Leader Election Algorithm

import sys
import threading
from random import randint

from ConSet import *

#Number of nodes
n = 13

#List of mailboxes
mailboxes = []

#Barrier to synchronize rounds
barrier = threading.Barrier(n)
barrier2 = threading.Barrier(n)


#Flag to check the election has ended or not
isLeaderElected = False

#To initilize mailboxes
def createAndStoreMailboxes(number_of_nodes):
    for i in range(0,number_of_nodes):
        
        #CAN CHANGE THE ""CONSET CONSTRUCTOR"" TO USE THE ALGORITHM WITH ANOTHER DATA STRUCTURE
        mailboxes.append(ConSet())
    return 0


#Starts reading and writing operations for a node
def nodeWorks(node_identifier, number_of_nodes):
    #Round count
    counter = 1

    #Check that if the election has ended or not
    while isLeaderElected == False:
        #To execute read from and write to mailbox/es, 
        #   start two threads to do these jobs simultaneously
        max_result = []

        #Writing operation for the node
        sendMessages(node_identifier, number_of_nodes, counter)
        barrier2.wait()
        barrier2.reset()

        #In fact I implemented a concurrent version of it but since PA requires to make read&write 
        #   operations sequential I do not submit that version but I think it could be the fastest :)

        #Reading operation for the node
        res = findMaxVote(node_identifier, number_of_nodes, max_result)

        #Nodes that completes read & write operations wait here until all other nodes complete too.
        #   After all of them complete reading and writing, a new round can start
        barrier.wait()
        
        if max_result[0] == (-1, -(sys.maxsize) - 1):
            print("Node " + str(node_identifier) + " could not decide on the leader and moves to the round " + str(counter+1) + ".")
            counter = counter + 1

        else:
            print("Node " + str(node_identifier) + " decided " + str(max_result[0][0]) + " as the leader.")
        
        barrier.reset()
    return None


#Reading functionality
#Remove messages from the mailbox of the specified thread
def findMaxVote(node_identifier, number_of_nodes, result):
    #Set max vote as the INT_MIN
    maxVote = (-1, - (sys.maxsize) - 1)

    #Control duplicates
    dup_ctr = 0

    #Get the mailbox of the specified node
    mailbox = mailboxes[node_identifier]

    #Reading thread expects "n" messages on each
    for i in range(0, number_of_nodes):
        #Remove operation is blocking, so it will get exactly "n" messages from its mailbox
        vote = mailbox.remove()

        #If incoming vote is bigger than or equal to the old maxVote
        if vote[1] >= maxVote[1]:
            
            #Mark as duplicate if it is equal
            if vote[1] == maxVote[1]:
                dup_ctr = dup_ctr+1
            
            #Set as the new maxVote if it is different
            else:
                maxVote = vote
                dup_ctr = 0

    #If the current maxVote is not duplicated
    if dup_ctr == 0:
        #Send it as the maxVote answer
        result.append(maxVote)

        #Also set the election continuation flag as completed
        global isLeaderElected
        isLeaderElected = True

        return maxVote

    #If it is duplicated, start to a new round
    else:
        result.append((-1, -(sys.maxsize) - 1))
        return (-1, -(sys.maxsize) - 1)


#Writing functionality
#Send messages to all of mailboxes with the decided vote and the sender node's id
def sendMessages(node_identifier, number_of_nodes, round):
    #Generate the vote value
    value = randint(0, (number_of_nodes*number_of_nodes))

    #Create the message tupple
    message = (node_identifier, value)

    print("Node " + str(node_identifier) + " proposes value " + str(value) + " for round " + str(round) + ".")

    #Add to all mailboxes
    for i in range(0, number_of_nodes):
        mailboxes[i].add(message)

    return None


#Start leader election algorithm with "n" different nodes (threads in this case)
def simulate(number_of_nodes) -> None:

    threads = []
    for i in range(0, number_of_nodes):

        #Make them run nodeWorks
        thread = threading.Thread(target= nodeWorks, args=(i, number_of_nodes))
        threads.append(thread)
        thread.start()

    return None

if __name__ == "__main__":
    createAndStoreMailboxes(n)
    simulate(n)