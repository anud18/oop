#include "Creature.h"
#include "Goat.h"
#include "Grass.h"
#include "RandomNum.h"
class World{
    public:
       World();
       World(int _numPasses, int seed);
       ~World();
       void oneRound(); 
       void display();
       void mainLoop(int interval);
    private:
        Creature *cell[20][35];
        int numPasses;
        RandomNum randomNum;
};
