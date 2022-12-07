#ifndef _GOAT_H_
#define _GOAT_H_

#include "Creature.h"
class Goat:public Creature{
    public:
        Goat();
        virtual ~Goat();
        virtual bool Move(Creature* target);//including eat
        virtual bool Bear(Creature* target);
        virtual void Pass();

    private:
        int foodPoints;
};
#endif
