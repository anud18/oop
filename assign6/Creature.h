
#ifndef _CREATURE_H_
#define _CREATURE_H_
class Creature{
    public:
        Creature();
        virtual ~Creature();
        bool mature();
        virtual bool Move(Creature* target) = 0;//including eat
        virtual bool Bear(Creature* target) = 0;
        virtual void Pass() = 0;
        char getName();
        void start();
        void show();
        bool live();
        void increaseAge();
    private:
        int age;
        int lowerbound;
        char name;
        int upperbound;
        bool actioned;
        int maxAge;

};
#endif
