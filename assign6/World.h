#include <iostream>

using namespace std;

class Creature;

class World{
  private:
    const int mapW = 35,mapH = 20,initGoat = 5, initGrass = 10;
    int _numPasses,_curNPass;
    Creature ***map;
    RandomNum *rand;
    void printWorld();

    void move(int&,int&);
    void birth(int,int);
    friend Creature;
  public:
    World(int numPasses,int seed);
    void mainLoop(int displayInterval);
};

class Creature{
  private:
  public:
    int age;
    bool moved;  
    Creature();
    char _creatureType; 
    virtual bool cellValid(Creature***,int,int) = 0;
    virtual bool pregnant() = 0 ;
    virtual bool dailyStatus() = 0;
};

class Goat: public Creature{
  private:
    int foodP;
  public:
    Goat();
    bool cellValid(Creature***,int,int);
    bool pregnant(){return age>=50 && age<=55;}
    bool dailyStatus();
};

class Grass: public Creature{
  private:

  public:
    Grass();
    bool cellValid(Creature***,int,int);
    bool pregnant(){return age>=3 && age<=5;}
    bool dailyStatus();
};
