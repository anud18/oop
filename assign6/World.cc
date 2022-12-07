#include "World.h"
#include "RandomNum.h"
#include "Goat.h"
#include "Grass.h"
#include <iostream>

using namespace std;

const int xDir[4] = {-1, 0, 0, 1};
const int yDir[4] = {0, 1, -1, 0};

World::World(){
    for(int i = 0; i < 35; ++i){
        for(int j = 0; j < 20; ++j){
            cell[i][j] = nullptr;
        }
    }
}
World::World(int _numPasses, int seed):numPasses(_numPasses), randomNum(seed){
    for(int i = 0; i < 35; ++i){
        for(int j = 0; j < 20; ++j){
            cell[i][j] = nullptr;
        }
    }
    for(int i = 0; i < 5; ++i){
        int r = rand();
        while(cell[r % 35][r % 20] != nullptr){
            r = rand();
        }
        cell[r % 35][r % 20] = new Goat();
    }
    for(int i = 0; i < 10; ++i){
        int r = rand();
        while(cell[r % 35][r % 20] != nullptr){
            r = rand();
        }
        cell[r % 35][r % 20] = new Grass();
    }

}
World::~World(){
    for(int i = 0;i < 35; ++i)
        for(int j = 0; j < 20; ++j)
            if(cell[i][j])
                delete cell[i][j];
}
void World::oneRound(){
    //unaction and delete died creature
    for(int i = 0; i < 35; ++i){
        for(int j = 0; j < 20; ++j){
            if(cell[i][j]){
                cell[i][j]->start(); 
                if(!cell[i][j]->live())
                    cell[i][j] = nullptr;
            }
        }
    }
    ////do action
    for(int i = 0; i < 35; ++i){
        for(int j = 0; j < 20; ++j){
            if(cell[i][j] == nullptr){
                continue;
            }
            int direction = randomNum.getRandomNum(0,3);
            //int x = xDir[direction];
            //int y = yDir[direction];
            int x = 1;
            int y = 1;
            x += i;
            y += j;
            if(x < 0 || x >= 35 || y < 0 || y >= 20 || cell[i][j] == nullptr)
                continue;
            if(cell[i][j]->mature()){//call bear
                if(cell[i][j]->Bear(cell[x][y])){
                    if(cell[x][y])
                        delete cell[x][y];
                    if(cell[x][y]->getName() == 'X')
                        cell[i][j] = new Goat();
                    else if(cell[x][y]->getName() == 'I')
                        cell[i][j] = new Grass();
                }
            }
            else{//call move
                if(cell[i][j]->Move(cell[x][y])){
                    if(cell[x][y])
                        delete cell[x][y];
                    cell[x][y] = cell[i][j];
                    cell[i][j] = nullptr;
                }
            }
        }
    }
    //increageAge
    for(int i = 0; i < 35; ++i){
        for(int j = 0; j < 20; ++j){
            if(cell[i][j] != nullptr)
                cell[i][j]->Pass();
        }
    }
}
void World::display(){
    cout << ' ';
    for(int i = 0; i < 35; ++i){
        cout << ' ' <<  i % 10;
    }
    cout << endl;
    for(int i = 0; i < 20; ++i){
        cout << i % 10;
        for(int j = 0; j < 35; ++j){
            cout << ' ';
            if(cell[i][j] == nullptr)
                cout << ' ';
            else
                cout << cell[i][j]->getName();
        }
        cout << endl;
    }

}
void World::mainLoop(int interval){
    for(int i = 0; i < numPasses; ++i){

        oneRound();
        if(i % 100 == 0){
            display();
        }
    }
}
