//
// Created by DanMa on 10/02/2022.
//
#include "iostream"
using namespace std;

/**
 * Abstract class of size of ball - BallSize.
 */
class BallSize {
protected:
    int size{};
public:
    BallSize() = default;
    virtual string getSize() = 0;
    virtual string getPSI() = 0;
};

/**
 * A Class that represent 6 size general ball.
 */
class SixSizeBall : public  BallSize {
public:
    SixSizeBall(){
        this->size = 6;
    }
    string getPSI() override{
        return "15 PSI";
    }
    string getSize() override{ return to_string(this->size);}
};

/**
 * A Class that represent 5 size general ball.
 */
class FiveSizeBall : public  BallSize {
public:
    FiveSizeBall(){
        this->size = 5;
    }
    string getPSI() override{
        return "10 PSI";
    }
    string getSize() override{
        return to_string(this->size);
    }
};

/**
 * Abstract Ball Class.
 */
class Ball {
protected:
    string type;
public:
    virtual void blowUpBall(BallSize& size) = 0;
};

/**
 * Concrete class of type Ball - Basketball,
 */
class BasketBall : public Ball{
public:
    BasketBall(){
        this->type = "Basketball";
    }
    void blowUpBall(BallSize& bsize) override{
        cout << "This is a " + bsize.getSize() + " size " +  this->type + " so blowing up with " + bsize.getPSI() <<endl;
    }
};

/**
 * Concrete Class of type of Ball - FootBall.
 */
class FootBall : public Ball{
public:
    FootBall(){
        this->type = "football";
    }
    void blowUpBall(BallSize& bsize) override{
        cout << "This is a " + bsize.getSize() + " size " +  this->type + " so blowing up with " + bsize.getPSI() <<endl;
    }
};

/**
 * Main using the Bridge Design Pattern.
 *
 * Instead of having the classes :
 * SixSizeBasketBall, FiveSizeBasketBall, SixSizeFootBall, FiveSizeFootBall in addition
 * to the existing FootBall and BasketBall classes,
 * we decouple the abstraction (basketball/ football) from the implementation (size of the ball).
 * We do so by passing BallSize (which changes dynamically) to the blowUpBall function.
 */
int main() {

    Ball *bb = new BasketBall();
    Ball *fb = new FootBall();

    BallSize *six = new SixSizeBall();
    BallSize *five = new FiveSizeBall();

    bb->blowUpBall(*six);
    bb->blowUpBall(*five);

    fb->blowUpBall(*six);
    fb->blowUpBall(*five);


}
