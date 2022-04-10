#include <iostream>
#include "string"
using namespace std;
class WrongInputException{};

/**
 * Abstract Class client know representing Game Bottoms Uniform.
 */
class GameBottoms{
public:
    GameBottoms() = default;
};

/**
 * Abstract Class client know representing Game Shirt Uniform.
 */
class GameShirt{
public:
    GameShirt() = default;
};

/**
 * Concrete Classes
 */
class HomeShirt : public GameShirt{
public:
    HomeShirt() : GameShirt(){};
};

class AwayShirt : public GameShirt{
public:
    AwayShirt() : GameShirt(){};
};

class HomeBottoms : public GameBottoms{
public:
    HomeBottoms() : GameBottoms(){};
};

class AwayBottoms : public GameBottoms{
public:
    AwayBottoms() : GameBottoms(){};
};

/**
 * Abstract Class Representing Uniform Factory Functionality.
 */
class AbstractUniformFactory{
public:
    AbstractUniformFactory() = default;
    virtual GameShirt* createShirt() = 0;
    virtual GameBottoms* createBottoms() = 0;
};

/**
 * Concrete Factories -> enforce preventing combinations between Home and Away By Design!
 */
class HomeUniformFactory : public AbstractUniformFactory{
    GameShirt * createShirt() override{
        cout << "Home Shirt Created!" << endl;
        return new HomeShirt();
    }
    GameBottoms * createBottoms() override{
        cout << "Home Bottoms Created!" << endl;
        return new HomeBottoms();
    }
};

class AwayUniformFactory : public AbstractUniformFactory{
    GameShirt * createShirt() override{
        cout << "Away Shirt Created!" << endl;
        return new AwayShirt();
    }
    GameBottoms * createBottoms() override{
        cout << "Away Bottoms Created!" << endl;
        return new AwayBottoms();
    }
};

/**
 * Creating Home/ Away Uniforms matching user request.
 */
int main() {
    char input;
    AbstractUniformFactory* abs;
    cout << "Welcome to Game Day Babyee!" << endl << "Let's Pick a Uniform" << endl;
    cout << "Enter A - for Away Uniform Creation, H - for Home Uniform Creation:" << endl;
    cin >> input;
    try{
        switch (input) {
            case 'A':
            case 'a':
                abs = new AwayUniformFactory();break;
            case 'H':
            case 'h':
                abs = new HomeUniformFactory();break;
            default:
                throw WrongInputException();

    }
    } catch (WrongInputException e) {
        cout << "Not A Valid Option" << endl;
        return -1;
    }
    abs->createShirt();
    abs->createBottoms();
    return 0;
}
