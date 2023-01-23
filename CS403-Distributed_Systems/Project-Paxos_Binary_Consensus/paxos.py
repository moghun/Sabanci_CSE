#Muhammed Orhun Gale - 26754
#Paxos Algorithm Implementation for Binary Consensus Problem

import sys
import time
import random
from multiprocessing import Process, Barrier
import zmq

#Push a message to given node's pipeline, message is always delivered correctly
def send(msg, proposer, target) -> None:
    reliableMSG = {"sender": proposer, "receiver": target, "msg": msg}
    nodeSocket["PUSH"][target].send_json(reliableMSG)

#Push a message to given node's pipeline with a given probability, otherwise push a CRASH message
def sendFailure(msg, proposer, target, prob) -> None:
    rand = random.random()
    #Sending the correct msg probability -> 1 - prob
    if(rand > prob):
        successfulMSG = {"sender": proposer, "receiver": target, "msg": msg}
        nodeSocket["PUSH"][target].send_json(successfulMSG)
    #CRASH msg probability -> prob
    else:
        failedMSG = {"sender": proposer, "receiver": target, "msg": {"type": "CRASH"}}
        nodeSocket["PUSH"][target].send_json(failedMSG)

#Broadcast a message by using send function, message is always delivered correctly
def broadcast(msg, proposer, numProc) -> None:
    #To all other nodes
    for proc in range(numProc):
        if(proc != proposer):
            send(msg, proposer, proc)

#Broadcast a message by using sendFailure function, message is delivered as CRASH msg with given probability
def broadcastFailure(msg, proposer, numProc, prob) -> None:
    #To all nodes, including the sender
    for proc in range(numProc):
        sendFailure(msg, proposer, proc, prob)

#Check given node is the leader of the given round or not
def checkLeader(ID, round, numProc) -> bool:
    leader =  round % numProc

    if leader == ID:
        return True

    else:
        return False

#Find the joinMSG with maxVotedRound value, return round number and vote's value
def findMaxRoundAndVal(receivedMessages):
    maxRound = -9
    proposedVal = -9
    #For all joinMSGs
    for i in range(len(receivedMessages)):
        currMSG = receivedMessages[i]

        round = currMSG["msg"]["maxVotedRound"]
        val = currMSG["msg"]["maxVotedValue"]   

        #Get the latest proposed
        if round > maxRound:
            proposedVal = val
            maxRound = round

    return maxRound, proposedVal

#Simulate a Paxos node
#Main for loop simulates the rounds
def PaxosNode(ID, prob, numProc, val, numRounds, barrier) -> None:

    #Set fundamental local variables for Paxos algorithm
    maxVotedRound = -1
    maxVotedValue = None
    proposeVal = None
    decision = None

    #Store all PULL and PUSH sockets for send and broadcast methods
    global nodeSocket
    nodeSocket = {"PULL": [], "PUSH": []}

    context = zmq.Context()

    #Create node's pipeline
    pull = context.socket(zmq.PULL)
    nodeSocket["PULL"].append(pull)
    port = 5550 + ID
    pull.bind("tcp://127.0.0.1:"+ str(port))

    #Create PUSH sockets for pipelines of all other nodes
    for i in range(numProc):
        push = context.socket(zmq.PUSH)
        nodeSocket["PUSH"].append(push)
        port = 5550 + i
        push.connect("tcp://127.0.0.1:"+str(port))

    #Wait a little to make sure that all processes started listening each other
    time.sleep(2)

    #Simulate rounds
    for r in range(numRounds):

        #Check whether the node is proposer or acceptor in this round
        isLeader = checkLeader(ID, r, numProc)


####### PROPOSER

        #If it is the leader this round, then it is the proposer
        if isLeader == True:

########### PROPOSER PHASE 1

            proposedSent = False

            #Count number of received Join messages
            joinPhaseMessages = []
            numJoinMSG = 0
            isLeaderAcceptorAlive = False

            #Broadcast START msg for this round
            print("ROUND " + str(ID) + " STARTED WITH INITIAL VALUE: " + str(val), flush=True)
            broadcastFailure({"type": "START"}, ID, numProc, prob)

            #Receive messages from all processes including itself
            for i in range(numProc):
                joinPhaseMSG = nodeSocket["PULL"][0].recv_json()   

                #If it is a START msg, it should receive it from itself
                #This message is counted as a JOIN msg
                if joinPhaseMSG["msg"]["type"] == "START" and joinPhaseMSG["sender"] == ID:
                    #Then proposer node is alive as an acceptor node
                    isLeaderAcceptorAlive = True
                    numJoinMSG += 1
                    print("LEADER OF "+ str(r) + " RECEIVED IN JOIN PHASE: START", flush=True)

                #If it is a JOIN msg, increment number of join messages
                elif joinPhaseMSG["msg"]["type"] == "JOIN":
                    numJoinMSG += 1
                    joinPhaseMessages.append(joinPhaseMSG)
                    print("LEADER OF "+ str(r) + " RECEIVED IN JOIN PHASE: JOIN " + str(joinPhaseMSG["msg"]["maxVotedRound"]) + " " + str(joinPhaseMSG["msg"]["maxVotedValue"]), flush=True)

                #If it is a CRASH msg, just print
                elif joinPhaseMSG["msg"]["type"] == "CRASH":
                    print("LEADER OF "+ str(r) + " RECEIVED IN JOIN PHASE: CRASH " + str(r%numProc), flush=True)

            #If the JOIN quorum is established
            if numJoinMSG > (numProc/2):
                #Find the latest proposed value among all received JOIN messages
                propRound, propValue = findMaxRoundAndVal(joinPhaseMessages)

                #If the proposer's acceptor is alive, then consider its vote value too
                if isLeaderAcceptorAlive == True and propRound < maxVotedRound:
                    propRound = maxVotedRound
                    propValue = maxVotedValue

                #If all join messages send their maxVotedRound as -1, then none of them voted before
                if propRound == -1:
                    propValue = val

                #Set proposeVal as the decided propValue
                proposeVal = propValue
                #Set start flag for phase 2
                proposedSent = True
                #Broadcast PROPOSE msg
                broadcastFailure({"type": "PROPOSE", "proposedValue": proposeVal}, ID, numProc, prob)           

            #If quorum cannot be established, then broadcast ROUNDCHANGE msg
            else:
                print("LEADER OF ROUND "+ str(r) +" CHANGED ROUND", flush=True)
                broadcast({"type":"ROUNDCHANGE"}, ID, numProc)

                #Wait acceptors to get the ROUNDCHANGE msg and move to the next round
                barrier.wait()

########### PROPOSER PHASE 2

            #If the PROPOSE msg is broadcasted
            if proposedSent == True:
                #Count number of vote messages
                numVoteMSG = 0
                #Receive messages from all nodes
                for i in range(numProc):
                    votePhaseMSG = nodeSocket["PULL"][0].recv_json()                    
                    
                    #If it is a PROPOSE msg, it should receive it from itself
                    #This message is counted as a VOTE msg
                    if votePhaseMSG["msg"]["type"] == "PROPOSE" and votePhaseMSG["sender"] == ID:
                        #Since the proposer node's itself is joined to the vote quorum, update its values
                        maxVotedRound = r
                        maxVotedValue = proposeVal
                        numVoteMSG += 1
                        print("LEADER OF "+ str(r) + " RECEIVED IN VOTE PHASE: PROPOSE " + str(votePhaseMSG["msg"]["proposedValue"]), flush=True)

                    #If it is a VOTE msg, increment number of join messages
                    elif votePhaseMSG["msg"]["type"] == "VOTE":
                        numVoteMSG += 1
                        print("LEADER OF "+ str(r) + " RECEIVED IN VOTE PHASE: VOTE", flush=True)

                    #If it is a CRASH msg, just print
                    elif votePhaseMSG["msg"]["type"] == "CRASH":
                        print("LEADER OF "+ str(r) + " RECEIVED IN VOTE PHASE: CRASH " + str(r%numProc), flush=True)

                #If vote quorum is established, notice that the value is decided
                if numVoteMSG > (numProc/2):
                    decision = proposeVal
                    print("LEADER OF " + str(r) + " DECIDED ON VALUE: " + str(decision), flush=True)

                #Wait acceptors to move the next round
                barrier.wait()


####### ACCEPTOR

        #If it is not leader this round, then it is an acceptor
        else:

########### ACCEPTOR PHASE 1

            #Wait for a START or CRASH msg
            #Since the recv_json method is blocking, acceptors will synchronize with the proposer
            joinPhaseMSG = nodeSocket["PULL"][0].recv_json()
            
            #If it is a START msg, reply the proposer with a JOIN msg
            #JOIN msg can be sent as a CRASH msg since it is sent with sendFailure msg
            if joinPhaseMSG["msg"]["type"] == "START":
                print("ACCEPTOR " + str(ID) + " RECEIVED IN JOIN PHASE: START", flush=True)

                #Send latest voted value and voting round
                sendFailure({"type": "JOIN","maxVotedRound": maxVotedRound, "maxVotedValue": maxVotedValue}, ID, joinPhaseMSG["sender"], prob)

            #If it is a CRASH msg, reply the proposer with a CRASH msg directly by using send method
            elif joinPhaseMSG["msg"]["type"] == "CRASH":
                print("ACCEPTOR " + str(ID) + " RECEIVED IN JOIN PHASE: CRASH " + str(r%numProc), flush=True)
                send({"type": "CRASH"}, ID, joinPhaseMSG["sender"])

########### ACCEPTOR PHASE 2

            #After replying the proposer, wait until receiving PROPOSE, CRASH or ROUNDCHANGE msg
            #Since the recv_json method is blocking, acceptors will synchronize with the proposer
            votePhaseMSG = nodeSocket["PULL"][0].recv_json()

            #If it is a PROPOSE msg, reply the proposer with a VOTE msg
            #VOTE msg can be sent as a CRASH msg since it is sent with sendFailure msg
            if votePhaseMSG["msg"]["type"] == "PROPOSE":
                print("ACCEPTOR " + str(ID) + " RECEIVED IN VOTE PHASE: PROPOSE " + str(votePhaseMSG["msg"]["proposedValue"]), flush=True)
                
                #Since node is voted at this round, update values
                maxVotedRound = r
                maxVotedValue = votePhaseMSG["msg"]["proposedValue"]
                sendFailure({"type": "VOTE"}, ID, votePhaseMSG["sender"], prob)

            #If it is a CRASH msg, reply the proposer with a CRASH msg directly by using send method
            elif votePhaseMSG["msg"]["type"] == "CRASH":
                print("ACCEPTOR " + str(ID) + " RECEIVED IN VOTE PHASE: CRASH " + str(r%numProc), flush=True)
                send({"type": "CRASH"}, ID, votePhaseMSG["sender"])

            #If it is a ROUNDCHANGE msg, just print and move to next round
            elif votePhaseMSG["msg"]["type"] == "ROUNDCHANGE":
                print("ACCEPTOR " + str(ID) + " RECEIVED IN VOTE PHASE: ROUNDCHANGE", flush=True)

            #Wait proposer and other acceptors to move the next round
            barrier.wait()

if __name__ == '__main__':
    if(len(sys.argv) == 4):
        
        #Get user inputs
        numProc = int(sys.argv[1])
        prob = float(sys.argv[2])
        numRounds = int(sys.argv[3])
        barrier = Barrier(numProc)

        print("NUM_NODES:", numProc , "CRASH_PROB:" , prob, "NUM_ROUNDS:", numRounds, flush=True)

        #Create Paxos processes
        pax_processes = []
        for proc in range(numProc):
            #Give a random init value to propose at the leader round
            pax_proc = Process(target=PaxosNode, args=(proc, prob, numProc, random.randint(0,1), numRounds, barrier,)) 
            pax_processes.append(pax_proc)

        #Start Paxos processes
        for proc in pax_processes:
            proc.start()

        #Wait until all of them joins to the main process
        for proc in pax_processes:
            proc.join()