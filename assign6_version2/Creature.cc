#include<iostream>
#include "Creature.h"

using namespace std;

Creature::Creature(){
   age = 0; 
}
Creature::Creature(int _lowerbound, int _upperbound, int _maxAge, char _name):age(0),lowerbound(_lowerbound), upperbound(_upperbound), maxAge(_maxAge), actioned(true), name(_name){

}

Creature::~Creature(){
    age = -1;
}
bool Creature::canBear(){
    return age >= lowerbound && age <= upperbound;
}

char Creature::getName(){
    return name;
}

void Creature::start(){
    actioned = false;
}

void Creature::show(){
    cout << ' ' << name;
}
int Creature::getAge(){
    return age;
}
//bool Creature::live(){
    //return age <= maxAge;
//}

void Creature::increaseAge(){
    age++;
}
void Creature::setActioned(bool condition){
    actioned = condition;
}
bool Creature::getActioned(){
    return actioned;
}
