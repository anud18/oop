#include<iostream>
#include "Goat.h"

using  namespace std;

Goat::Goat():foodPoints(20){

}
Goat::~Goat(){

}

bool Goat::Move(Creature* target){
    if(target == nullptr)
        return true;
    else if(target->getName() == 'I'){
        foodPoints += 5;
        return true;
    }
    return false;
}
bool Goat::Bear(Creature* target){
    if(target == nullptr )
        return true;
    else if(target->getName() == 'I'){
        foodPoints += 5;
        return true;
    }
    return false;
}
void Goat::Pass(){
    increaseAge();
    foodPoints--;
}
