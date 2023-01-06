#Muhammed Orhun Gale - 26754
#MyBlock and MyBlockChain class implementations

from __future__ import print_function
import sys
import threading
import Pyro4
import Pyro4.util

#Block class to represent transactions that are performed on the Blockchain
class MyBlock(object):
    #Contructor
    def __init__(self, txAttributes=(), next=None):
        self.__txType = txAttributes[0]
        self.__args = txAttributes[1]
        self.__next = next
    #Getter for private transaction type variable
    def get_txType(self):
        return self.__txType
    #Getter for private arguments variable
    def get_args(self):
        return self.__args
    #Getter for the next pointer of the block
    def get_next(self):
        return self.__next

#Expose the blockchain class as a remote object for Pyro4 daemon
@Pyro4.expose
#Blockchain class
class MyBlockChain:
    #API methods
    #Constructor
    def __init__(self,  chainName, head=None):
        self.head = head
        self.chainName = chainName
        self.guard = threading.Lock()

        #Initialize Pyro4 daemon and name server, 
        #           register the Blockchain created blockchain object as the remote object to the nameserver
        daemon = Pyro4.Daemon()
        nameserver = Pyro4.locateNS()
        uri = daemon.register(self)
        nameserver.register(self.chainName, uri)
        print(self.chainName+" server serving...")
        daemon.requestLoop()

    #Create an account on the blockchain
    def createAccount(self, amount):
        #Ensure that the account transaction is atomic
        self.guard.acquire()
        #Get account id
        max = self.__findMax()
        self.head = MyBlock(("CREATEACCOUNT", (max+1, amount)), self.head)
        self.guard.release()
        return max+1

    #Money transfer operation for accounts on the same blockchain
    def transfer(self, _from, _to, amount):
        #While an exchange takes place, 
        #   transfer operations on both blockchains must be halted to ensure atomicity of transactions
        self.guard.acquire()
        
        #Check if from and to accounts exist or not
        if self.__searchAccount(_from) == False or self.__searchAccount(_to) == False:
            #If one of them does not exist, release the lock and return -1
            self.guard.release()
            return -1
        
        #Decide who will sends the money
        sendingAccount = self.__decideSender(_from, _to, amount)
        
        #Check if the sender has adequate balance to send the money or not
        if self.__checkSufficientBalance(sendingAccount, amount) == False:
            self.guard.release()
            return -1

        #If all conditions are satisfied, save the transfer transaction to the blockchain
        else:
            newBlock = MyBlock(("TRANSFER", (_from, _to, amount)), self.head)
            self.head = newBlock
            self.guard.release()
            return 1

    #Money transfer from one blockchain to another
    def exchange(self, _from, _to, toChain, amount):
        #While an exchange takes place, 
        #   transfer operations on the both blockchains must be halted to ensure atomicity of transactions
        self.guard.acquire()
        #Acquire the remote blockchain's lock
        toChain.acquireRemoteLock()
        #Check if from and to accounts exist or not
        if self.__searchAccount(_from) == False or toChain.validateAccount(_to) == False:
            self.guard.release()
            toChain.releaseRemoteLock()
            return -1

        #Decide who will sends the money
        if amount < 0:
            #Check if remote sender has adequate balance to send the money or not
            if toChain.validateBalance(_to, amount) == False:
                self.guard.release()
                toChain.releaseRemoteLock()
                return -1

            #If all conditions are satisfied, save the exchange transaction to both blockchains
            else:
                self.guard.release()
                self.head  = MyBlock(("EXCHANGE", (_from, _to, str(toChain.getChainName()), amount)), self.head)
                toChain.addExchangeTransaction((_to, _from, self.chainName, -amount))
                toChain.releaseRemoteLock()
                return 1

        else:
            #Check if the sender has adequate balance to send the money or not
            if self.__checkSufficientBalance(_from, amount) == False:
                self.guard.release()
                toChain.releaseRemoteLock()
                return -1

            #If all conditions are satisfied, save the exchange transaction to both blockchains
            else:
                self.head  = MyBlock(("EXCHANGE", (_from, _to, str(toChain.getChainName()), amount)), self.head)
                toChain.addExchangeTransaction((_to, _from, self.chainName, -amount))
                self.guard.release()
                toChain.releaseRemoteLock()
                return 1
    
    #Calculate the total balance of a given account
    def calculateBalance(self, id):
        ptr = self.head
        balance = 0

        #Iterate all blockchain to sum the balance in accordance with the transaction type
        while ptr != None:
            if ptr.get_txType() == "CREATEACCOUNT":
                if ptr.get_args()[0] == id:
                    initAmount = ptr.get_args()[1]
                    balance = balance + initAmount

            elif ptr.get_txType() == "TRANSFER":
                fromAccount = ptr.get_args()[0]
                toAccount = ptr.get_args()[1]
                txAmount = ptr.get_args()[2]

                if fromAccount == id or toAccount == id:

                    if fromAccount == id and toAccount != id:
                        balance = balance - txAmount
                    
                    if fromAccount != id and toAccount == id:
                        balance = balance + txAmount

            elif ptr.get_txType() == "EXCHANGE":
                fromAccount = ptr.get_args()[0]
                toAccount = ptr.get_args()[1]
                txAmount = ptr.get_args()[3]

                if fromAccount == id or toAccount == id:

                    if fromAccount == id and toAccount != id:
                        balance = balance - txAmount
                    
                    if fromAccount != id and toAccount == id:
                        balance = balance + txAmount     

            ptr = ptr.get_next()       
        
        return balance

    #Print the current status of the blockchain
    def printChain(self):
        ptr = self.head
        print("\n----------------------------------------")
        print("\nChain status:\n")
        while ptr != None:
            print(ptr.get_txType(), ptr.get_args())
            ptr = ptr.get_next()
        print("\n----------------------------------------")


    #RPC methods
    #Validate existince of an account on a remote blockchain
    def validateAccount(self, id):
        return self.__searchAccount(id)

    #Validate adequacy of the balance of an account on a remote blockchain
    def validateBalance(self, id, amount):
        return self.__checkSufficientBalance(id, amount)

    #Create an exchange entry on a remote blockchain
    def addExchangeTransaction(self, args):
        self.head = MyBlock(("EXCHANGE", (args[0], args[1], args[2], args[3])), self.head)

    #Acquire the lock of a remote blockchain
    def acquireRemoteLock(self):
        self.guard.acquire()

    #Release the lock of a remote blockchain
    def releaseRemoteLock(self):
        self.guard.release()

    def getChainName(self):
        return self.chainName

    #Private helper methods

    #Find the next account number for incoming create account requests
    def __findMax(self):
        ptr = self.head
        max = 0

        if ptr == None:
            return max

        while ptr != None:
            if ptr.get_txType() == "CREATEACCOUNT":
                if ptr.get_args()[0] > max:
                    max = ptr.get_args()[0]
            ptr = ptr.get_next()

        return max

    #Checks that whether an account exist or not in the blockchain
    def __searchAccount(self, id):
        ptr = self.head

        while ptr != None:
            if ptr.get_txType() == "CREATEACCOUNT":
                if ptr.get_args()[0] == id:
                    return True
            ptr = ptr.get_next()

        return False

    #Decide who sends the money
    def __decideSender(self, _from, _to, amount):
        if amount < 0:
            return _to

        else:
            return _from

    #Check that an account has adequate balance or not
    def __checkSufficientBalance(self, id, amount):
        balance = self.calculateBalance(id)
        if amount < 0:
            return (balance + amount) >= 0
        else:
            return (balance - amount) >= 0
















# chain = MyBlockChain("BTC")

# chain.createAccount(100)


# chain.createAccount(31)
# chain.createAccount(150)


# chain.transfer(3,1,50)
# chain.transfer(2,1,10)
# chain.transfer(2,3,-100)
# chain.transfer(4,3, 5)
# chain.createAccount(2000)
# chain.transfer(3,4, -300)
# chain.transfer(3,4, -30000)


# chain.printChain()

# print(chain.head, chain.head.get_txType(), chain.head.get_args(), chain.head.get_next())
# print(chain.calculateBalance(3))

# print(chain.head, chain.head.get_txType(), chain.head.get_args(), chain.head.get_next())


