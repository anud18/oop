#include "Grass.h"
#include<iostream>

using namespace std;

Grass::Grass():Creature(3,5,5, 'I'){

}
Grass::~Grass(){
    
}
void Grass::Action(Creature** target, Creature** self){
    if(getActioned())
        return;
    setActioned(true);
    if(canBear()){
        if(*target == nullptr){
            *target = new Grass();
        }
    }
    //increaseAge();
    //setActioned(true);
}
bool Grass::live(){
    int _age = getAge();
    return _age >= 0 && _age <= 5;
}
void Grass::grow(){
    increaseAge();
}
