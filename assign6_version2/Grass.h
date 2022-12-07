#ifndef _GRASS_H_
#define _GRASS_H_

#include "Creature.h"
class Grass:public Creature{
    public:
        Grass();    
        virtual ~Grass();
        virtual void Action(Creature** target, Creature** self);
        virtual bool live();
        virtual void grow();


};
#endif
