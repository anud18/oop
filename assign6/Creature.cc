#include<iostream>
#include "Creature.h"

using namespace std;

Creature::Creature(){
   age = 0; 
}

Creature::~Creature(){
    age = -1;
}
bool Creature::mature(){
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

bool Creature::live(){
    return age <= maxAge;
}

void Creature::increaseAge(){
    age++;
}
