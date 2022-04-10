#include <iostream>
#include <utility>
#include "string"
#include "map"
#include "list"
using namespace std;

class Product{
private:
    string description;
    int price;
public:
    Product(string name, int price) : description(std::move(name)), price(price){};
    string getDescription() const {
        return this->description;
    }
    int getPrice(){
        return this->price;
    }
};

class FilesDepartment {
public:
    void printOrder(list<Product*> *costumersCart){
        cout << "Your Order:" << endl << "----------------------" << endl;
        for (auto& p :*costumersCart){
            cout << p->getDescription() << endl;
        }
        cout << "----------------------" << endl;
    }
    void sendReceipt(){
        cout << "Receipt sent" << endl;
    }
};

class ShippingDepartment{
public:
    void package(list<Product*> *cart){
        cout << "Product's Packaged" << endl;
    }
    void contactShippingCompamy(){
        cout << "Packed Packege delivered to Shipping Company" << endl;
    }
};

class StockDepartment {
private:
    map<Product*, int> stockDataBase;
public:
    StockDepartment(map<Product*, int> products){
        this->stockDataBase = products;
    }
    bool isInStock(Product* p){
        auto it = this->stockDataBase.begin();
        while (it != stockDataBase.end()){
            if (it->first->getDescription() == p->getDescription() &&
            it->second > 0){
                return true;
            }
            it++;
        }
        cout << "Product" + p->getDescription() + " is Out Of Stock." << endl;
        return false;
    }
    void reduceAmount(Product* p){
        int amount = stockDataBase.find(p)->second;
        stockDataBase[p] = (amount-1);
    }
};

class MyProteinOrderDepartment {
private:
    StockDepartment& stockDepartment;
    FilesDepartment& filesDepartment;
    ShippingDepartment& shippingDepartment;
public:
    MyProteinOrderDepartment(StockDepartment& sd, ShippingDepartment& ssd, FilesDepartment& fd) :
    stockDepartment(sd), filesDepartment(fd), shippingDepartment(ssd) {};

    void addToCart(Product* p, list<Product*> *costumersCart){
        if(stockDepartment.isInStock(p)){
            costumersCart->push_back(p);
            stockDepartment.reduceAmount(p);
        }
    };
    void order(list<Product*> *cart){
        filesDepartment.printOrder(cart);
        filesDepartment.sendReceipt();
        shippingDepartment.package(cart);
        shippingDepartment.contactShippingCompamy();
    }
};

int main() {
    // set up stock
    map<Product*, int> stock;
    Product* cl = new Product("CrispyLayerd", 10);
    Product* pr = new Product("PopRol", 2);
    Product* ck = new Product("Cookie", 15);
    Product* vpn = new Product("Vanilla Protein Powder", 100);

    stock[cl] = 15;
    stock[pr] = 10;
    stock[ck] = 5;
    stock[vpn] = 20;

    // set up order Department
    StockDepartment stockDepartment((stock));
    ShippingDepartment shippingDepartment;
    FilesDepartment filesDepartment;
    MyProteinOrderDepartment od (stockDepartment, shippingDepartment, filesDepartment);

    // set Up Costumer Cart
    list<Product*>* cart = new list<Product*>;
    od.addToCart(cl, cart);
    od.addToCart(ck, cart);
    od.addToCart(vpn, cart);

    // place Order
    od.order(cart);
    return 0;
}
