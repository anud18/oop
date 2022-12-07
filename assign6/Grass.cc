#include "Grass.h"
#include<iostream>

using namespace std;

Grass::Grass(){

}
Grass::~Grass(){
    
}
bool Grass::Move(Creature* target){
    return false;
}
bool Grass::Bear(Creature* target){
    if(target == nullptr)
        return true;
    return false;
}
void Grass::Pass(){
    increaseAge();
}
