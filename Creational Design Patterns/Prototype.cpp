#include <iostream>
#include "list"
using namespace std;
/*
 * Util Class
 */
class Point{
private:
    int x_axis;
    int y_axis;
public:
    Point(int x, int y) : x_axis(x), y_axis(y){};
    Point(Point &p) : x_axis(p.x_axis), y_axis(p.y_axis){};
    ~Point() = default;
    void setPoint(int x, int y){
        this->x_axis = x;
        this->y_axis = y;
    }
    int get_x_axis(){
        return this->x_axis;
    }
    int get_y_axis(){
        return this->y_axis;
    }
};

/**
 * Abstract Shape Class with Virtual Clone Method.
 */
class Shape{
public:
    ~Shape() = default;
    Shape() = default;
    virtual Shape* clone() = 0;
    virtual string myType() = 0;
    virtual void setShape(Point p) = 0; // defined to support the option that the copy will have different location.
};

/**
 * Concrete Classes which Override Clone.
 */
class Rectangle : public Shape {
private:
    Point upperLeft;
    int width;
    int length;
public:
    ~Rectangle() = default;
    Rectangle(Point p, int w, int l) : upperLeft(p), width(w), length(l) {};
    void setShape(Point np) override{
        this->upperLeft = np;
    }
    Shape * clone() override{
         return new Rectangle(this->upperLeft, this->width, this->length);
    }
    string myType() override{
        return "Rectangle Positioned at " + to_string(this->upperLeft.get_x_axis()) + " " +
                to_string(this->upperLeft.get_y_axis());
    }
};

class Circle : public Shape{
private:
    Point center;
    int radius;
public:
    ~Circle() = default;
    Circle(Point p, int r) : center(p), radius(r){};
    void setShape(Point np) override{
        this->center = np;
    }
    Shape * clone() override{
        return new Circle(this->center, this->radius);
    }
    string myType() override{
        return "Rectangle Positioned at " + to_string(this->center.get_x_axis()) + " " +
               to_string(this->center.get_y_axis());
    }
};

class ShapeHolder {
private:
    list<Shape*> shapes;
public:
    ShapeHolder() = default;
    list<Shape*> getShapes(){return this->shapes;}

    /**
     * If user want exact copy.
     * @param s is the Shape to add it's copy.
     */
    void addShapeCopy(Shape* s){
        Shape* newShape = s->clone();
        this->shapes.push_back(newShape);
        cout << "Add new Copy Of " + newShape->myType() << endl;
    }
    /**
     * Overloading Copy in case user want copy in different location than original shape.
     * @param s is the shape to add it's copy.
     * @param p is the new point representing shape's new location.
     */
    void addShapeCopy(Shape* s, Point p){
        Shape* newShape = s->clone();
        newShape->setShape(p);
        this->shapes.push_back(newShape);
        cout << "Add new Copy Of " + newShape->myType() << endl;
    }
};
int main() {

    // set up
    Point p(1,2);
    Point np(100,100);
    Shape* rect = new Rectangle(p,5,10);
    Shape* circ = new Circle(p, 10);

    //using addShapeCopy.
    ShapeHolder shapeHolder;
    shapeHolder.addShapeCopy(rect);
    shapeHolder.addShapeCopy(rect, np); // supporting shapes copy with relocation.
    shapeHolder.addShapeCopy(circ);
    shapeHolder.addShapeCopy(circ,np);
    return 0;
}
