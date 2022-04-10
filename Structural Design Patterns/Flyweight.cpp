#include <iostream>
#include "map"
#include "string"
using namespace std;
enum objectType {soldier = 0, tank = 1, plane = 2};

/*
 * FlyWeightClass
 */
class GameObject{
    int health;
    string des;
public:
    GameObject(int health, string des) : health(health), des(des){};
    virtual void print(int i, int j) = 0;
    int getHealth(){
        return this->health;
    }
    void setHealth(int newHealth){
        this->health = newHealth;
    }
    string getDes(){
        return this->des;
    }
};

class Plane : public GameObject{
public:
    Plane(int health, string des) : GameObject(health, des){};
    void print(int i, int j) override{
        cout << "Plane Object at coordinates:" + to_string(i) +", " + to_string(j) << endl;
    }
};

class Soldier : public GameObject{
public:
    Soldier(int health, string des) : GameObject(health, des){};
    void print(int i, int j) override{
        cout << "Soldier Object at coordinates:" + to_string(i) +", " + to_string(j) << endl;
    }
};

class Tank : public GameObject{
public:
    Tank(int health, string des) : GameObject(health, des){};
    void print(int i, int j) override{
        cout << "Tank Object at coordinates:" + to_string(i) +", " + to_string(j) << endl;
    }
};


class GameObjectsFactory{
private:
    map<objectType, GameObject*> cachedObjects;
public:
    GameObjectsFactory() = default;
    GameObject* getObject(objectType key, int health){
        // if cached
        if(cachedObjects.find(key) != cachedObjects.end() &&
        cachedObjects.find(key)->second->getHealth() == health){
            cout << "Returned Cached Obj type:" + cachedObjects.find(key)->second->getDes() << endl;
            return cachedObjects.find(key)->second;
        }
        // if not cached
        GameObject* obj;
        switch (key) {
            case soldier:
                obj =  new Soldier(health, "soldier");
                break;
            case tank:
                obj = new Tank(health, "tank");
                break;
            case plane:
                obj =  new Plane(health, "plane");
                break;
            default:
                break;
        }
        this->cachedObjects[key] = obj;
        cout << "Created new object from type " + obj->getDes() + " and return it" << endl;
        return obj;
    }
};

int main() {
GameObjectsFactory gof;
GameObject* gameObject[5][5];

for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
        gameObject[i][j] = nullptr;
    }
}

gameObject[0][0] = gof.getObject(tank, 100);
gameObject[0][1] = gof.getObject(tank, 100);
gameObject[0][2] = gof.getObject(tank, 80);

gameObject[1][0] = gof.getObject(soldier, 100);
gameObject[1][1] = gof.getObject(soldier, 100);
gameObject[1][2] = gof.getObject(soldier, 70);

gameObject[2][0] = gof.getObject(plane, 100);
gameObject[2][1] = gof.getObject(plane, 100);
gameObject[2][2] = gof.getObject(plane, 50);

for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
        if(gameObject[i][j]){
            gameObject[i][j]->print(i, j);
        }
    }
}

}
