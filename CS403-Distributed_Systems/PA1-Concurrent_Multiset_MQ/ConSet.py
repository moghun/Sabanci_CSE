#Muhammed Orhun Gale - 26754
#Concurrent Multiset Data Structure

import sys
import threading

#Node structure:
#      item -> (node_id, vote_value)
#      next -> points to the next node of the list
#      lock -> fine-grained lock
#      guard -> a mutex to provide atomicity on a specific node if it is necessary
class Node:
    def __init__(self, item=None, next=None):
        self.item = item
        self.next = next
        self.guard = threading.Lock()
        self.lock = threading.Condition()


    #Overloading the "<" operator for node comparisons
    def __lt__(self, other):
        return self.item[1] < other.item[1]


#ConSet structure:
#      head -> Sentinel node with INT_MAX value for reverse sorting - node id is -1
#      tail -> Sentinel node with INT_MIN value for reverse sorting - node id is -2
#      non-sentinel nodes -> nodes that are added or removed via corresponding operations
class ConSet:
    #Constructor --> Initialize sentinel head and tail nodes
    def __init__(self):
        self.tail = Node((-2, -sys.maxsize - 1))
        self.head = Node((-1, sys.maxsize), self.tail)


    #Linked-list add operator --> Default return is none
    #Takes an item (id, vote) tuple as the input
    def add(self, item) -> None:
        vote = item[1]
        #To start iterating to find the location that the new node would insert
        #   first acquire lock
        self.head.lock.acquire()
        try:
            #If lock is acquired, get the next node's lock and start iterating
            pred = self.head
            curr = pred.next
            curr.lock.acquire()
            try:
                #If acquired the both lock, ready to iterate over the linked list
                #Another thread also can iterate over the linked after the thread that holds the lock give up
                while curr.item[1] >= vote:
                    pred.lock.release()
                    pred = curr
                    curr = curr.next
                    curr.lock.acquire() 

                #Found the place to insert, create the new item and change pointers
                newNode = Node(item)
                newNode.next = curr
                pred.next = newNode

                return None   

            finally:
                #Release the lock of the "next node" of the freshly inserted node
                curr.lock.release()
        
        finally:
            #Release the "pred node" of the freshly inserted node
            pred.lock.release()
            
            #Signal to any waiting remove function if there exist at least one NON-SENTINEL node
            if self.head.next.next != None: #If the head's next is tail
                self.head.lock.acquire()
                self.head.lock.notify()
                self.head.lock.release()


    #Linked-list remove operator --> Default return the removed item
    #Removes a node from the head -- Waits until there exist at least one non-sentinel node
    def remove(self) -> tuple:
        try:
            #Since the remove operation is performed only on the head and 
            #       remove operation threads that just wake up may encounter with race condition to remove
            #           just added node --> 
            # Therefore there need to be a guard lock to make sure that linked-list emptiness check is atomic

            self.head.guard.acquire() #First acquire the head's guard lock
            self.head.lock.acquire()  #Then acquire the head's operational lock
            try:
                if self.head.next.item[0] == -2: #If the linked-list is empty wait until something is added
                    self.head.lock.wait()

                curr = self.head.next 
                #Acquire next lock in case of any continuing operation
                self.head.next.lock.acquire() 
            
                #Check that the item that is subject to delete is tail or not
                if curr.item[0] != -2: #If not, delete it
                    self.head.next = curr.next
                    return curr.item

                return (None, None)

            finally:
                #Release the deleted item's lock
                curr.lock.release()
        finally:
            #First release the head's lock for continuation of add operations
            self.head.lock.release()
            #Then release guard lock for incoming remove operations
            self.head.guard.release()