#Muhammed Orhun Gale - 26754
#Bully Leader Election Algorithm Implementation and Simulation

import sys
import random
import os
from multiprocessing import Process
import threading
import time
import zmq

#Leader method that impelements the Bully Leader Election algorithm 
def leader(id, numProc, isStarter):
    pid = os.getpid()

    #A hash table to reach flags that are required to implement the algorithm in the Responder thread
    sharedMap = {"TERMINATE": False, "LEADER_MULTICASTING": isStarter, "RESP_RECEIVED": False, 
                   "CONDITION_VARIABLE": threading.Condition(), "PRINT_LOCK": threading.Lock(), "SEND_LOCK": threading.Lock()}

    #Use flush flag to make sure all "processes" print correctly
    print("PROCESS STARTS:", pid, id, isStarter, flush=True)

    #Calculate timeout
    wait_time = 0
    if numProc < 15:
        wait_time = (10 + 5*numProc + 1)
    else:
        wait_time = (10 + 3*numProc + 1)

    #Share it with the Responder to set socket timeout
    sharedMap["WAIT_TIME"] = wait_time

    #Start Responder thread of the
    listener = threading.Thread(target=responder,args=(id, numProc, sharedMap,))
    listener.start()
    
    #Set PUB socket for the Leader thread
    context = zmq.Context()
    socket = context.socket(zmq.PUB)
    port = 5550 + id
    socket.bind("tcp://127.0.0.1:" + str(port))
    sharedMap["PUB_SOCKET"] = socket
    
    #Wait for Responder thread to connect
    time.sleep(5)

    #Check whether the node is a starting node or not
    sharedMap["CONDITION_VARIABLE"].acquire()
    if sharedMap["LEADER_MULTICASTING"] == False:
        #If not a starting node, put it to sleep until it receives a "LEADER" or "TERMINATE" message
        sharedMap["CONDITION_VARIABLE"].wait()

        #CASE-I --> There exists a smaller starter node
        #If it receives a "LEADER" msg, it will be waken up by the Responder's "LEADER" check part
        # then it will be sleep again at the "TERMINAL" check of the Leader and will be waken up by the Responder's "TERMINATE" check

        #CASE-II --> There does not exist a smaller starter node
        #If it receives a "TERMINATE" msg, it will be waken up by the Responder's "TERMINATE" check part
        #  then it won't go to sleep again at the "TERMINAL" check of the Leader and joins directly
    sharedMap["CONDITION_VARIABLE"].release()

    #If it is a starter node or received a "LEADER" message
    if sharedMap["LEADER_MULTICASTING"] == True:
        sharedMap["PRINT_LOCK"].acquire()
        print("PROCESS MULTICASTS LEADER MSG:", id, flush=True)
        sharedMap["PRINT_LOCK"].release()
        
        #Multicast "LEADER" message to nodes with larger IDs
        for rcv in range(numProc):
            if(rcv > id):
                sharedMap["SEND_LOCK"].acquire()
                socket.send_string("LEADER", flags=zmq.SNDMORE)
                socket.send_json({"SRCID": id, "RCVID": rcv})
                sharedMap["SEND_LOCK"].release()

        #Sleep until the receive a response from a node wiwth higher ID
        ctr = 0
        while sharedMap["RESP_RECEIVED"] == False:
            time.sleep(1) 
            
            if ctr == sharedMap["WAIT_TIME"]:
                break
            ctr = ctr + 1
        #If did not receive --> it should be the alive node with highest id, broadcast "TERMINATE" message
        #Else, wait for the "TERMINATE" message --> Becomes passive listener
        if sharedMap["RESP_RECEIVED"] == False:
            sharedMap["PRINT_LOCK"].acquire()
            print("PROCESS BROADCASTS TERMINATE MSG", id, flush=True)
            sharedMap["PRINT_LOCK"].release()
            for rcv in range(numProc):
                sharedMap["SEND_LOCK"].acquire()
                socket.send_string("TERMINATE", flags=zmq.SNDMORE)
                socket.send_json({"SRCID": id, "RCVID": rcv})
                sharedMap["SEND_LOCK"].release()

    #If "TERMINATE" messsage is not received yet, wait until receiving a "TERMINATE" message
    sharedMap["CONDITION_VARIABLE"].acquire()
    if sharedMap["TERMINATE"] == False:
        sharedMap["CONDITION_VARIABLE"].wait()
    sharedMap["CONDITION_VARIABLE"].release()

    #Wait until Responder thread returns
    listener.join()
    return 0

def responder(id, numProc, sharedMap):
    sharedMap["PRINT_LOCK"].acquire()
    print("RESPONDER STARTS:", id, flush=True)
    sharedMap["PRINT_LOCK"].release()

    #Subscribe to all PUB sockets
    context = zmq.Context()
    subscriptions = {}
    for node in range(numProc):
        socket = context.socket(zmq.SUB)
        port = 5550 + node

        socket.connect("tcp://127.0.0.1:" + str(port))
        socket.subscribe("LEADER")
        socket.subscribe("RESP")
        socket.subscribe("TERMINATE")

        #Set timeout for socket
        socket.RCVTIMEO = 150
        subscriptions[node] = socket

    #While "TERMINATE" message is not received yet
    while sharedMap["TERMINATE"] == False:
        #Listen all sockets
        for node in range(numProc):
            try:
                socket = subscriptions[node]
                topic = socket.recv_string()
                msg = socket.recv_json()
                
                #If the published message is for the current node, take it
                if msg["RCVID"] == id:

                    #If a "TERMINATE" message is received
                    if topic == "TERMINATE":
                        #Set terminate flag true and wake up the Leader thread

                        sharedMap["CONDITION_VARIABLE"].acquire()
                        sharedMap["TERMINATE"] = True
                        sharedMap["CONDITION_VARIABLE"].notify()
                        sharedMap["CONDITION_VARIABLE"].release()

                    #If a "LEADER" message is received
                    elif topic == "LEADER":    
                        
                        #If the sender has a lower id
                        if msg["SRCID"] < id:
                            #Send "RESP" message to it
                            sharedMap["PRINT_LOCK"].acquire()
                            print("RESPONDER RESPONDS", id, msg["SRCID"], flush=True)
                            sharedMap["PRINT_LOCK"].release()
                            sharedMap["SEND_LOCK"].acquire()
                            sharedMap["PUB_SOCKET"].send_string("RESP", flags=zmq.SNDMORE)
                            sharedMap["PUB_SOCKET"].send_json({"SRCID": id, "RCVID": msg['SRCID']})
                            sharedMap["SEND_LOCK"].release()
                        
                        #If not multicasted a "LEADER" message yet 
                        if sharedMap["LEADER_MULTICASTING"] == False:
                            #Set multicasting flag as true and wake up the Leader thread

                            sharedMap["CONDITION_VARIABLE"].acquire()
                            sharedMap["LEADER_MULTICASTING"] = True
                            sharedMap["CONDITION_VARIABLE"].notify()
                            sharedMap["CONDITION_VARIABLE"].release()
                    #If "RESP" message is received
                    elif topic == "RESP":
                        #Set response flag true

                        sharedMap["RESP_RECEIVED"] = True
            #If did not receive anything, continue listening
            except:
                pass
    return 0

if __name__ == '__main__':
    #Get arguments from the terminal
    if len(sys.argv) >= 4:
        numProc = int(sys.argv[1])
        numAlive = int(sys.argv[2])
        numStarters = int(sys.argv[3])

        #Randomly choose nodes as alive and starter nodes
        aliveNodes = random.sample(range(0, numProc), numAlive)
        starterNodes = random.sample(aliveNodes, numStarters)

        print("Alives: \n",aliveNodes, flush=True)
        print("Starters: \n",starterNodes, flush=True)
        processes = []
        
        #Set Leader processes
        for node in aliveNodes:
            if node in starterNodes:
                proc = Process(target=leader, args=(node, numProc, True,))
            else: 
                proc = Process(target=leader, args=(node, numProc, False,))

            processes.append(proc)

        #Start Leader processes
        for pr in processes:
            pr.start()

        #Wait until Leader processes return
        for pr in processes:
            pr.join()