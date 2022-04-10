#include <iostream>
#include "string"
#include "map"
#include "typeinfo"
using namespace std;
// This is a combination of Factory Design Pattern And O(1) Access using user input
// to the matching object using it's creator

/**
 * This is the Product interface.
 */
class GymDumbbell {
private:
    int kg;
    int price;
public:
    GymDumbbell(int kg, int p) : kg(kg), price(p){};
    int getPrice(){return this->price;};
    int getDes(){return this->kg;};
};

/**
 * Product Inherit Classes.
 */
class FiveKgDumbbell : public GymDumbbell {
public:
    FiveKgDumbbell() : GymDumbbell(5, 100){};
};

class TenKgDumbbell : public GymDumbbell {
public:
    TenKgDumbbell() : GymDumbbell(10, 120){};
};

class TwentyKgDumbbell : public GymDumbbell {
public:
    TwentyKgDumbbell() : GymDumbbell(20, 200){};
};

/**
 * The Creator Factory Class
 */
class GymDumbbellCreatorFactory{

private:
    /**
     * This is the Creator interface.
     */
    class GymDumbbellCreator {
    public:
        GymDumbbellCreator() = default;
        virtual GymDumbbell* create() = 0;
    };

    /**
    * Creator inherit Classes.
    */
    class FiveKgDumbbellCreator : public GymDumbbellCreator {
    public:
        FiveKgDumbbellCreator() = default;
        ~FiveKgDumbbellCreator() = default;
        GymDumbbell* create() override{
            cout << "Five Kg Dumbbell Was Created!"<< endl;
            return new FiveKgDumbbell();
        }
    };

    class TenKgDumbbellCreator : public GymDumbbellCreator {
    public:
        TenKgDumbbellCreator() = default;
        ~TenKgDumbbellCreator() = default;
        GymDumbbell* create() override{
            cout << "Ten Kg Dumbbell Was Created!"<< endl;
            return new TenKgDumbbell();
        }
    };

    class TwentyKgDumbbellCreator : public GymDumbbellCreator {
    public:
        TwentyKgDumbbellCreator() = default;
        ~TwentyKgDumbbellCreator() = default;
        GymDumbbell* create() override{
            cout << "Twenty Kg Dumbbell Was Created!"<< endl;
            return new TwentyKgDumbbell();
        }
    };

    map <string, GymDumbbellCreator*> dumbbellsCreator;
public:
    /**
     * @param type is the string representing the user object to create.
     * @return new GymDumbbell.
     *
     * This is the most important function in this complex structure.
     * It takes the user string, checks map for exsistance of the string.
     * If exist - gets a matching run time dumbbell Creator, and invokes
     * it's create function -> which returns new GymDumbbell injected Dynamically.
     */
    GymDumbbell* createDumbbell(string type){
        // if not found - return iterator to end element.
        GymDumbbellCreator* dumbbellCreator = this->dumbbellsCreator.find(type)->second;
        if(dumbbellCreator != dumbbellsCreator.end()->second ||
                ((dumbbellCreator == dumbbellsCreator.end()->second) &&
                        (type == dumbbellsCreator.end()->first))){
            return dumbbellCreator->create();
        }
        return nullptr;
    }
    GymDumbbellCreatorFactory(){
        this->dumbbellsCreator["Five"] = new FiveKgDumbbellCreator();
        this->dumbbellsCreator["Ten"] = new TenKgDumbbellCreator();
        this->dumbbellsCreator["Twenty"] = new TwentyKgDumbbellCreator();
    };
    ~GymDumbbellCreatorFactory() = default;
};


int main() {
    GymDumbbellCreatorFactory creatorFactory;
    string dumbbellType;
    cin >> dumbbellType;

    /*
     * The most amazing thing in this design pattern is this line.
     * Instead of ugly SOLID breaker switch case which check dynamic type,
     * We just pass the input to the GymDumbbellCreatorFactory which creates
     * the matching dumbbell in a SOLID way.
     */
    GymDumbbell* dumbbell = creatorFactory.createDumbbell(dumbbellType);
    return 0;
}
