#include <iostream>
using namespace std;

class Food {
protected:
    int price;
public:
    Food(int p) : price(p){};
    virtual int getPrice() = 0;
    virtual ~Food(){};
};

class Hamburger : public Food {
public:
    Hamburger() : Food(50){};
    virtual ~Hamburger(){};
    virtual int getPrice() override{
        return this->price;
    }
};

class Pizza : public Food{
public:
    Pizza() : Food(40){};
    virtual int getPrice() override{
        return this->price;
    }
    virtual ~Pizza(){};
};

class FoodDecorator : public Food{
public:
    Food* food;
    FoodDecorator(Food *f) : Food(f->getPrice()) {
        this->food = f;
    }
    virtual int getPrice() override{
        food->getPrice();
    }
};

class Tomatoes : public FoodDecorator {
public:
    Tomatoes(Food *f) : FoodDecorator(f) {
        this->price = 15;
    };

    int getPrice() override {
        return this->price + FoodDecorator::getPrice();
    }
};

class Onions : public FoodDecorator {
public:
    Onions(Food *f) : FoodDecorator(f) {
        this->price = 10;
    }
    int getPrice() override{
        return this->price + FoodDecorator :: getPrice();
    }
};

class Mushrooms : public FoodDecorator {
public:
    Mushrooms(Food *f) : FoodDecorator(f) {
        this->price = 5;
    }
    int getPrice() override{
        return this->price + FoodDecorator :: getPrice();
    }
};

int main() {

    Food* p = new Pizza();
    cout << + "Pizza with no Toppings cost " +to_string(p->getPrice()) + " ILS" << endl;

    Food* tp = new Tomatoes(new Pizza());
    cout << + "Pizza with Tomatoes cost " +to_string(tp->getPrice()) + " ILS" << endl;

    Food* op = new Onions(new Pizza());
    cout << + "Pizza with Onions cost " +to_string(op->getPrice()) + " ILS" << endl;

    Food* mop = new Mushrooms(new Onions(new Pizza()));
    cout << + "Pizza with Onions and mushrooms cost " +to_string(mop->getPrice()) + " ILS" << endl;

    Food* motp = new Mushrooms(new Onions(new Tomatoes(new(Pizza))));
    cout << + "Pizza with Onions and mushrooms and Tomatoes cost " +to_string(motp->getPrice()) + " ILS" << endl;

    cout << "----------------------------------------------------------------------" << endl;

    Food* hb = new Hamburger();
    cout << + "Hamburger with no Toppings cost " +to_string(hb->getPrice()) + " ILS" << endl;

    Food* hbo = new Onions(new Hamburger());
    cout << + "Hamburger with onions cost " +to_string(hbo->getPrice()) + " ILS" << endl;

    Food* homt = new Onions(new Mushrooms(new Tomatoes(new Hamburger)));
    cout << + "Hamburger with Onions Mushroom Tomatoes and Toppings cost " +to_string(homt->getPrice()) + " ILS" << endl;
}
