#include<iostream>
#include "Goat.h"

using  namespace std;

Goat::Goat():Creature(50,55,69,'X'),foodPoints(20){

}
Goat::~Goat(){

}
void Goat::Action(Creature** target, Creature** self){
    if(getActioned())
        return;
    setActioned(true);
    if(canBear()){
        if(*target == nullptr){
            *target = new Goat();
        }
        else if((*target)->getName() == 'I'){
            delete *target;
            foodPoints += 5;
            *target = new Goat();
        }
    }
    else{
        if(*target == nullptr){
            *target = *self;
            *self = nullptr;
        }
        else if((*target)->getName() == 'I'){
            delete *target;
            foodPoints += 5;
            *target = *self;
            *self = nullptr;
        }
    }
    //increaseAge();
    //foodPoints--;
    //setActioned(true);
}
bool Goat::live(){
    int _age = getAge();
    return _age >= 0 && _age <= 69 && foodPoints > 0;
}
void Goat::grow(){
    foodPoints--;
    increaseAge();
}
