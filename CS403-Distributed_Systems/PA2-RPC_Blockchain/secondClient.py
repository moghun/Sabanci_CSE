import Pyro4


BTC = Pyro4.Proxy("PYRONAME:BTC")
acc1 = BTC.createAccount(100)
print(acc1)
bal = BTC.calculateBalance(acc1)
if bal > 20:
    BTC.transfer(acc1, 1, -60)
BTC.printChain()

ETH = Pyro4.Proxy("PYRONAME:ETH")
e1 = ETH.createAccount(30)
print(e1)
bal = ETH.calculateBalance(e1)
if bal > 20:
    ETH.transfer(e1, 1, -20)
ETH.printChain()

BTC.exchange(acc1, e1, ETH, 50)
BTC.printChain()
ETH.printChain()