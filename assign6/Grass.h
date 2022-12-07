#ifndef _GRASS_H_
#define _GRASS_H_

#include "Creature.h"
class Grass:public Creature{
    public:
        Grass();    
        virtual ~Grass();
        virtual bool Move(Creature* target);//including eat
        virtual bool Bear(Creature* target);
        virtual void Pass();


};
#endif
