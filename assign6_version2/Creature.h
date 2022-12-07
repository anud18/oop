
#ifndef _CREATURE_H_
#define _CREATURE_H_
class Creature{
    public:
        Creature();
        Creature(int _lowerbound, int _upperbound, int _maxAge, char _name);
        virtual ~Creature();
        bool canBear();
        virtual void Action(Creature** target, Creature** self) = 0;
        char getName();
        void start();
        void show();
        int getAge();
        virtual bool live() = 0;
        void increaseAge();
        void setActioned(bool condition);
        bool getActioned();
        virtual void grow() = 0;
    private:
        int age;
        int lowerbound;
        int upperbound;
        int maxAge;
        bool actioned;
        char name;

};
#endif
