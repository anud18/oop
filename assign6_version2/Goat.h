#ifndef _GOAT_H_
#define _GOAT_H_

#include "Creature.h"
class Goat:public Creature{
    public:
        Goat();
        virtual ~Goat();
        virtual void Action(Creature** target, Creature** self);
        virtual bool live();
        virtual void grow();

    private:
        int foodPoints;
};
#endif
