#include <iostream>
using namespace std;

/**
 * Abstract Expression Interface define calculate functionality of all Expressions.
 */
class AbstractExpression{
public:
    virtual int calculate() = 0;
};

/**
 * Abstract Class define Functionality for Terminal Expressions.
 */
class TerminalExpression : public AbstractExpression {
protected:
    int value;
public:
    TerminalExpression(int x) : value(x){};
    virtual int calculate() {
        return this->value;
    };
};

/**
 * Terminal Expressions inherit Classes.
 */
class Constant : public TerminalExpression {
public:
    Constant(int x) : TerminalExpression(x){};
};

class Variable : public TerminalExpression{
public:
    Variable(int x) : TerminalExpression(x){};
    void Set(int x){
        this->value = x;
    }

};

/**
 * Abstract Class defining the functionality of Binary Expression.
 */
class BinaryExpression : public AbstractExpression{
protected:
    AbstractExpression* l;
    AbstractExpression* r;
public:
    BinaryExpression(AbstractExpression* left, AbstractExpression* right) : l(left), r(right){};
    /*
     * All Binary Expression contain the same code except the operator.
     * To avoid duplicate code - calculate was made non-virtual, and it is using
     * the newly added virtual function which each Concrete Binary Expression will override.
     */
    int calculate() {
        return OP(l->calculate(), r->calculate());
    }
    virtual int OP(int l, int r) = 0;
};

/**
 * Binary Expression inherit Classes.
 */
class Add : public BinaryExpression{
public:
    Add(AbstractExpression*l, AbstractExpression*r) : BinaryExpression(l,r){};
    int OP(int l, int r) override{
        return l+r;
    }
};

class Sub : public BinaryExpression{
public:
    Sub(AbstractExpression*l, AbstractExpression*r) : BinaryExpression(l,r){};
    int OP(int l, int r) override{
        return l-r;
    }
};

class Div : public BinaryExpression{
public:
    Div(AbstractExpression*l, AbstractExpression*r) : BinaryExpression(l,r){};
    int OP(int l, int r) override{
        return l/r;
    }
};

class Mul : public BinaryExpression{
public:
    Mul(AbstractExpression*l, AbstractExpression*r) : BinaryExpression(l,r){};
    int OP(int l, int r) override{
        return l*r;
    }
};

int main() {
    AbstractExpression* four = new Constant(4);
    AbstractExpression* five = new Constant(5);
    Variable* a = new Variable(10);

    // Calculate (4*5)+(a-5)
    // When a = 10
    AbstractExpression* e = new Add((new Mul(four,five)),new Sub(a,five));
    // (4*5)+(10-5) =25
    cout << "Expression Equals: "<<to_string(e->calculate()) << endl;
    e = new Add((new Mul(four,five)),new Div(a,five));
    //  (4*5)+(10/5) =22
    cout << "Expression Equals: "<<to_string(e->calculate()) << endl;

    // When a = 1
    a->Set(1);
    e = new Add((new Mul(four,five)),new Sub(a,five));
    // (4*5)+(1-5) =16
    cout << "Expression Equals: "<<to_string(e->calculate()) << endl;

    e = new Add((new Mul(four,five)),new Mul(a,five));
    // (4*5)+(1*5) =25
    cout << "Expression Equals: "<<to_string(e->calculate()) << endl;
    return 0;
}
