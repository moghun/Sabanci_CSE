#Muhammed Orhun Gale - 26754
#Abstract MapReduce class implementation

from multiprocessing import Process, Value, Array, Barrier, Semaphore
import os
import math
import time
import zmq
from abc import ABC, abstractmethod

#Abstract MapReduce class
class MapReduce(ABC):
    #Constructor -> Specifies number of workers
    def __init__(self, num_worker):
        self.num_worker = num_worker

    #Abstract Map method
    @abstractmethod
    def Map(self, map_input) -> dict:
        pass

    #Abstract Reduce method
    @abstractmethod
    def Reduce(self, reduce_input) -> list:
        pass

    #Fragment input list to messages and push to them to Producer-Consumer pipeline
    def _Producer(self, producer_input) -> None:
        print ('Producer ID:', os.getpid())

        #Create first 0MQ pipeline to push fragmented messages
        context = zmq.Context()
        production_pipe = context.socket(zmq.PUSH)
        production_pipe.bind("tcp://127.0.0.1:5558")

        #Calculate number of "element" in one fragment
        ceil = math.ceil(len(producer_input)/self.num_worker)
        floor = math.floor(len(producer_input)/self.num_worker)

        #Producer input = (Ceil * (Number of workers - x)) +  (Floor * x) --> Solve for x
        number_of_floor_worker = (ceil * self.num_worker) - len(producer_input)
        number_of_ceil_worker = self.num_worker - number_of_floor_worker
        
        #Verbose
        #print("Initial Data:", producer_input)

        #Sleep for a while to make sure that all of the consumers listens the pipe
        time.sleep(0.2)

        #Create fragmented messages and send them
        latest = 0
        curr = 0
        for i in range(0, number_of_ceil_worker):
            #Fragment
            consumer_input_fragment = []
            dummy = 0
            for j in range(curr, curr + ceil):
                #Add messages
                consumer_input_fragment.append(producer_input[j])
                dummy = j
            curr += ceil
            #For marshaling, json format is used
            #Send to the pipe
            production_pipe.send_json({"producer_output":consumer_input_fragment})
            latest = dummy

        curr = latest+1
        for i in range(0, number_of_floor_worker):
            #Fragment
            consumer_input_fragment = []
            for j in range(curr, curr + floor):
                consumer_input_fragment.append(producer_input[j])
            curr += floor
            #For marshaling, json format is used
            #Send to the pipe
            production_pipe.send_json({"producer_output":consumer_input_fragment})

        #Unbind and close the port
        production_pipe.unbind("tcp://127.0.0.1:5558")
        production_pipe.close()

        return None
        
    #Pull fragmented messages from Producer-Consumer pipeline and employ Map method to get partial results
    #Push Map results to the Consumer-Collector pipeline
    def _Consumer(self) -> None:
        print ('Consumer ID:', os.getpid())
        #Connect to the first 0MQ pipeline to pull a fragmented messages
        context = zmq.Context()
        consumer_receiver = context.socket(zmq.PULL)
        consumer_receiver.connect("tcp://127.0.0.1:5558")

        #Pull one message and continue execution --> All consumers gets only one message
        result = consumer_receiver.recv_json()

        #Disconnect and close the port
        consumer_receiver.disconnect("tcp://127.0.0.1:5558")
        consumer_receiver.close()

        #Verbose
        # if result["producer_output"] != []:
        #     print("Map", os.getpid(), "Input:", result["producer_output"])

        #To get Map output
        mapping_result = dict()

        #Avoid passing empty messages to Map function
        #It can be the case if the number of elements is smaller than the number of Consumers
        if result["producer_output"] != []:
            #Call Map function
            mapping_result = self.Map(result["producer_output"])

        #print("Map", os.getpid(), "Result:", mapping_result)
        
        #Create SECOND 0MQ pipeline to push fragmented messages
        context = zmq.Context()
        consumer_sender = context.socket(zmq.PUSH)
        consumer_sender.connect("tcp://127.0.0.1:5559")

        #For marshaling, json format is used
        #Push the Map output to the pipe
        consumer_sender.send_json({"consumer_output":mapping_result})

        #Disconnect and close the port
        consumer_sender.disconnect("tcp://127.0.0.1:5559")
        consumer_sender.close()

        return None

    #Collect Map results from the Consumer-Collector pipeline and pass the Map results to the Reduce method
    def _ResultCollector(self) -> None:
        print ('ResultCollector ID:', os.getpid())
        #Bind to the second 0MQ pipeline to pull a fragmented messages
        context = zmq.Context()
        resultCollector_receiver = context.socket(zmq.PULL)
        resultCollector_receiver.bind("tcp://127.0.0.1:5559")

        #Listen until getting all of the consumer messages
        #List of Map outputs
        dict_list = list()
        num = 0
        flag = True
        while flag == True:
            #If all messages are pulled from the pipe stop listening
            if num == self.num_worker -1:
                flag = False
            #Get a Map output from a consumer
            mapped = resultCollector_receiver.recv_json()

            #Avoid any empty Map outputs
            if mapped["consumer_output"] != {}:
                dict_list.append(mapped["consumer_output"])
            num += 1

        #Verbose
        #print("Reducer Data:",dict_list)
        
        #Unbind and close the port
        resultCollector_receiver.unbind("tcp://127.0.0.1:5559")
        resultCollector_receiver.close()
        
        #Call Reduce method to create merged dictionary
        final_result = self.Reduce(dict_list)

        #Write the result dictionary into a txt file
        f = open("results.txt", "w")
        f.write(str(final_result))
        f.close()

        #Verbose
        #print("Result:", final_result)

        return None


    #Starts the Producer, Consumer and ResultCollector processes
    def start(self, filename) -> None:

        #Read the input into a list
        with open(filename) as f:
            lines = f.readlines()
        producer_input = list()
        for line in lines:
            node_list = line.strip('\n').split('\t')
            node_list = [int(i) for i in node_list]
            producer_input.append(node_list)

        #Create Producer, Consumers and ResultCollector processes
        consumers = []
        #Pass the input list to the producer
        Producer = Process(target=self._Producer, args=(producer_input,))
        for i in range(0, self.num_worker):
            Consumer = Process(target=self._Consumer, args=())
            consumers.append(Consumer)

        ResultCollector = Process(target=self._ResultCollector, args=())

        #Start the processes
        ResultCollector.start()

        for process in consumers:
            process.start()

        Producer.start()

        #Make the start void wait untill all of the child processes are returned
        Producer.join()

        for process in consumers:
            process.join()

        ResultCollector.join()

        return None

