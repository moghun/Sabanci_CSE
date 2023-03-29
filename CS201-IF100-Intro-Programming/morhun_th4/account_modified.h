#include <string>
using namespace std;

class Account {
    public :
    
    Account();
    Account(string ibanCode, string paramOwner); // Constructor of Account Class.
    Account(string ibanCode, string paramOwner, double amount); // Constructor of Account Class.
    Account(const Account &acc);
    
    bool deposit(double amount);            // deposit some money to this account
    bool withdraw(double amount);           // withdraw some money from this account
    void displayBalance();                  // show how much money is in this account.
    void displayOwner();                    // show owner of this account.
    void displayAll();
    string getIBAN() const;
    double getBalance() const;
    void transfer(Account& a, double amount); // transfer money from this account to another one.
    
    
private:
    string owner;       // name of the owner of the class
    double balance;     // how much is present in the account
    
    //THE-4 New private member IBAN
    string iban;
};
