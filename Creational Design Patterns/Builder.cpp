#include <iostream>
#include "vector"
using namespace std;


class Platform{
private:
    int x;
    int y;
    int l;
public:
    Platform(int x, int y, int l) : x(x), y(y), l(l){};
    int getX(){return this->x;}
    int getY(){return this->y;}
    int getLength(){return this->l;}
};

class Enemy{
private:
    int x;
    int y;
public:
    Enemy(int x, int y) : x(x), y(y){};
    int getX(){return this->x;}
    int getY(){return this->y;}
};

class Character{
private:
    int x;
    int y;
public:
    Character(int x, int y) : x(x), y(x){};
    int getX(){return this->x;}
    int getY(){return this->y;}
};


class LevelGraphics{
public:
    virtual void paintPlatform(Platform* p) = 0;
    virtual void paintCharacter(Character* e) = 0;
    virtual void paintEnemy(Enemy* p) = 0;
};

class AladdinGraphics : public LevelGraphics{
    void paintPlatform(Platform* p) override{
        cout << "Platform at position x:" + to_string(p->getX()) + " y:" + to_string(p->getY()) +
        " with length:" + to_string(p->getLength()) + " Painted Aladdin Style!" << endl;
    }
    void paintCharacter(Character* c) override {
        cout << "Character at position x:" + to_string(c->getX()) + " y:" + to_string(c->getY()) + " Painted Aladdin Style!" << endl;
    }
    void paintEnemy(Enemy* e) override {
        cout << "Enemy at position x:" + to_string(e->getX()) + " y:" + to_string(e->getY()) + " Painted Aladdin Style!" << endl;
    }
};

class MarioGraphics : public LevelGraphics{

    void paintPlatform(Platform* p) override{
        cout << "Platform at position x:" + to_string(p->getX()) + " y:" + to_string(p->getY()) +
                " with length:" + to_string(p->getLength()) + " Painted Mario Style!" << endl;
    }
    void paintCharacter(Character* c) override {
        cout << "Character at position x:" + to_string(c->getX()) + " y:" + to_string(c->getY()) + " Painted Mario Style!" << endl;
    }
    void paintEnemy(Enemy* e) override {
        cout << "Enemy at position x:" + to_string(e->getX()) + " y:" + to_string(e->getY()) + " Painted Mario Style!" << endl;
    }
};

class LevelDirector{
protected:
    vector<Platform*> platforms;
    vector<Enemy*> enemies;
    Character* character;
public:
    LevelDirector() = default;
    void createPlatform(int x_pos, int y_pos, int length) {
        platforms.push_back(new Platform(x_pos, y_pos, length));
    }
    void createCharacter(int x_pos, int y_pos){
        character = new Character(x_pos, y_pos);
    }

    void createEnemy(int x_pos, int y_pos) {
        enemies.push_back(new Enemy(x_pos,y_pos));
    }
    /**
     * This Method Constructs a level and paints it using dynamically given LevelGraphics.
     * @param lg
     */
    virtual void constructLevel(LevelGraphics* lg) = 0;
};

class BeginnerLevel : public LevelDirector{

    void constructLevel(LevelGraphics *lg) override{

        // Object Creation.
        int i = 0;
        for(i; i < 5; i++){
            createPlatform(i,i,i);
        }
        for(i = 0; i < 5; i++){
            createEnemy(i,i);
        }
        createCharacter(i,i);


        // Object Painting
        for(i = 0; i < 5; i++){
            lg->paintPlatform(this->platforms[i]);
        }
        for(i = 0; i < 5; i++){
            lg->paintEnemy(this->enemies[i]);
        }
        lg->paintCharacter(character);
    }
};

class AdvancedLevel : public LevelDirector{

    void constructLevel(LevelGraphics *lg) override{

        // Object Creation.
        int i = 0;
        for(i; i < 10; i++){
            createPlatform(i,i,i);
        }
        for(i = 0; i < 10; i++){
            createEnemy(i,i);
        }
        createCharacter(i,i);


        // Object Painting
        for(i = 0; i < 10; i++){
            lg->paintPlatform(this->platforms[i]);
        }
        for(i = 0; i < 10; i++){
            lg->paintEnemy(this->enemies[i]);
        }
        lg->paintCharacter(character);
    }
};

/**
 * Main using Builder Design Pattern and in runtime inject all possible Combinations.
 */
int main() {
    LevelGraphics* aladdin = new AladdinGraphics();
    LevelGraphics* mario = new MarioGraphics();

    LevelDirector* beginner = new BeginnerLevel();
    LevelDirector* advanced = new AdvancedLevel();

    cout << "Beginner Levels:" << endl;
    beginner->constructLevel(aladdin);
    beginner->constructLevel(mario);
    cout << "---------------------------------------------------" << endl;
    cout << "Advanced Levels:" << endl;
    advanced->constructLevel(aladdin);
    advanced->constructLevel(mario);
    return 0;
}
