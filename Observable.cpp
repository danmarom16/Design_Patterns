#include "iostream"
#include "string"
#include "list"
#include "typeinfo"
using namespace std;
class Student
/**
 * Abstract Grade Class.
 */
class Grades {
protected:
    list<Student*> registered;
public:
    Grades() = default;
    void notify(){
        list<Student*>::iterator it = registered.begin();
        while(it != registered.end()){
            (*it)->update(*this);
        }
    }
    void addStudent(Student* s) {
        this->registered.push_back(s);
    }
    virtual string type() = 0;
};
/**
 * Abstract Student Class
 */
class Student{
public:
    Student() = default;
    virtual void update(Grades* g) = 0;
};

class AlgoStudent : public Student{
private:
    Grades* g;
public:
    AlgoStudent(Grades* g) : g(g){};
    void update(Grades *g) override{
        if(g->type() == "algo"){
            g
        }
    }

};



class AlgoGrades : public Grades{
public:
    AlgoGrades() = default;
    list<Student*> getState(){
        return this->registered;
    }
    string type() override{
        return "algo";
    }
};

int main(){
    Grades* g = new AlgoGrades();
}


