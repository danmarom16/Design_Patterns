#include <iostream>
#include "list"
#include "algorithm"
using namespace std;

class CycleException{};

/**
 * Interface Representing General Soldier.
 */
class Soldier {
public:
    virtual void getArmed() = 0;
    virtual ~Soldier(){};
};

/**
 *  A Class Representing Soldier with no commandeers. (leaf)
 */
class regSoldier : public Soldier {
    int num;
public:
    regSoldier(int j){
        this->num = j;
    }
    void getArmed() override{
            cout << "Soldier number " + to_string(this->num) +  " is armed!"<< endl;
    }
};

list<Soldier*> hasCommander;
/**
 * A Class Representing Officer (Composite).
 */
class Officer : public Soldier {
private:
    list<Soldier*> mySoldiers;
    int number;
private:
    /*
     * Going through global list of soldiers with commanders and search for e.
     */
    bool find(Soldier* e){
        list<Soldier*>::iterator it=hasCommander.begin();
        while(it!=hasCommander.end()){
            if(e==*it)
                return true;
            it++;
        }
        return false;
    }
    /*
     * Checks if e is one of his own soldiers - which is not possible in real world.
     */
    bool findMe(Soldier* e){
        if(this==e)
            return true;
        Officer* m=dynamic_cast<Officer*>(e);
        if(m){
            list<Soldier*>::iterator it=m->mySoldiers.begin();
            while(it!=m->mySoldiers.end()){
                if(findMe(*it))
                    return true;
                it++;
            }
        }
        return false;
    }
public:
    Officer(int num) : number(num){};
    string getNum(){
        return to_string(this->number);
    }
    void getArmed() override{
        for(auto& soldier :mySoldiers){
            soldier->getArmed();
        }
        cout << "Officer number " + this->getNum() + " and his team are armed!" << endl;
    }

    void addSoldier(Soldier *soldier){
        if(findMe(soldier) || find(soldier)){
            throw CycleException();
        }
        this->mySoldiers.push_back(soldier);
        hasCommander.push_back(soldier);

    }

    virtual ~Officer(){
        for_each(this->mySoldiers.begin(),this->mySoldiers.end(),[](Soldier* e){delete e;});
    }
};

/**
 * A Class representing Chief Officer, in our case he is the "client".
 * He knows only his direct comandee and tell him to get the army ready.
 * The directComandee is the highest in hirarcy.
 */
class ChiefOfficer {
    Soldier* directComendee;
public:
    ChiefOfficer(Soldier* dc) {
        this->directComendee = dc;
    }
    void getReadyForWar() {
        this->directComendee->getArmed();
        cout << "All the army is armed!" << endl;
        cout << "Talking To The Press" << endl;
        cout << "Good Luck to us" << endl;
    }
};

/**
 * Not part of the Composite, made only because Chief Officer only fill out
 * comands and does not operate on his own.
 */
class PrimeMinister {
public:
    void getReadyForWar(ChiefOfficer co){
        co.getReadyForWar();
    }
};


int main() {
        int i = 0;
        int j = 0;
        // officer 0 - 5 reg soldiers.
        Officer *officer0 = new Officer(i++);
        for (j; j < 5; j++){
            officer0->addSoldier(new regSoldier(j));
        }

    // officer 1 - 4 reg soldiers, 1 officer (officer0)
    Officer *officer1 = new Officer(i++);
    for (j; j < 9; j++){
        officer1->addSoldier(new regSoldier(j));
    }
    officer1->addSoldier(officer0);

    // officer 2 - 5 reg soldiers.
    Officer *officer2 = new Officer(i++);
    for (j; j < 14; j++){
        officer2->addSoldier(new regSoldier(j));
    }

    // officer 3 - 3 reg soldiers, 2 officers (officer 1, officer 2)
    Officer *officer3 = new Officer(i++);
    for (j; j < 17; j++){
        officer3->addSoldier(new regSoldier(j));
    }
    officer3->addSoldier(officer1);
    officer3 ->addSoldier(officer2);

    try {
        officer1->addSoldier(officer3);
    }catch (CycleException e){
        cout << "Cycle avoided" << endl;
    }

    ChiefOfficer Cohavi(officer3);
    PrimeMinister Bibi;
    Bibi.getReadyForWar(Cohavi);
    return 0;
}
