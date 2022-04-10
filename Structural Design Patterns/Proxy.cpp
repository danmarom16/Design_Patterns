#include <iostream>
#include "string"
using namespace std;
class NegativeException{};
class AccessDeniedException{};


class BankAccount{
private:
    int current_account;
    string name;
public:
    BankAccount(int amount, string& clientName) : current_account(amount), name(clientName){};
    virtual int getCurrentAmount(){ return this->current_account;}
    virtual string getClientName(){return this->name;}
    virtual void deposite(int amount, string& name_as_identifier){
        this->current_account += amount;
    }

    virtual int withdrawal (int amount, string& name_as_identifier){
        if(this->current_account - amount < 0) {
            throw NegativeException();
        }
        else{
            this->current_account -= amount;
            return amount;
        }
    }
};


class BankAccountAccessManager : public BankAccount{
public:
    BankAccountAccessManager(int amount, string& name) : BankAccount(amount, name){};

    virtual void deposite(int amount, string& name_as_identifier){
        if(name_as_identifier != this->getClientName()){
            throw AccessDeniedException();
        }
        BankAccount ::deposite(amount, name_as_identifier);
    }

    virtual int withdrawal (int amount, string& name_as_identifier){
        if(name_as_identifier != this->getClientName()){
            throw AccessDeniedException();
        }
        return BankAccount ::withdrawal(amount, name_as_identifier);
    }
};



int main() {
    string c = "Dan";
    string i = "Itzhak";
    BankAccount *clienta = new BankAccountAccessManager(1233, c);
    try{
        clienta->deposite(100, c);
        cout << "Deposit Succeeded" << endl << "Current Amount: " + to_string(clienta->getCurrentAmount()) << endl;
    } catch (const AccessDeniedException& a){
        cout << "Access Denied" << endl;
    }

    try{
        clienta->deposite(100, i);
        cout << "Deposit Succeeded" << endl << "Current Amount: " + to_string(clienta->getCurrentAmount()) << endl;
    } catch (const AccessDeniedException& a){
        cout << "Access Denied" << endl;
    }

    try{
        clienta->withdrawal(100, c);
        cout << "Withdrawal Succeeded" << endl << "Current Amount: " + to_string(clienta->getCurrentAmount()) << endl;
    } catch (const AccessDeniedException& a){
        cout << "Access Denied" << endl;
    }

    try{
        clienta->withdrawal(100, i);
        cout << "Deposit Succeeded" << endl << "Current Amount: " + to_string(clienta->getCurrentAmount()) << endl;
    } catch (const AccessDeniedException& a){
        cout << "Access Denied" << endl;
    }

    return 0;
}
