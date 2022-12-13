#include "World.h"
#include "RandomNum.h"
#include "Goat.h"
#include "Grass.h"
#include <iostream>

using namespace std;

const int xDir[4] = {-1, 0,  0, 1};
const int yDir[4] = { 0, 1, -1, 0};

World::World(){
    for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 35; ++j){
            cell[i][j] = nullptr;
        }
    }
}
World::World(int _numPasses, int seed):numPasses(_numPasses), randomNum(seed){
    for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 35; ++j){
            cell[i][j] = nullptr;
        }
    }
    for(int i = 0; i < 5; ++i){
        int r = randomNum.getRandomNum(0,699);
        while(cell[r % 20][r % 35] != nullptr){
            r = randomNum.getRandomNum(0,699);
        }
        cell[r % 20][r % 35] = new Goat();
        //cout << i << ' '<<"X: " << r%35 << ' ' << r%20 <<endl;
    }
    for(int i = 0; i < 10; ++i){
        int r = randomNum.getRandomNum(0,699);
        while(cell[r % 20][r % 35] != nullptr){
            r = randomNum.getRandomNum(0,699);
        }
        cell[r % 20][r % 35] = new Grass();
        //cout << i << ' ' << "I: " << r%35 << ' ' << r%20 <<endl;
    }
    for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 35; ++j){
            if(cell[i][j] != nullptr)
                cell[i][j]->grow();
        }
    }
    //cout << endl;
    //cout << endl;
    //cout << endl;
    //display();

}
World::~World(){
    for(int i = 0;i < 20; ++i)
        for(int j = 0; j < 35; ++j)
            if(cell[i][j])
                delete cell[i][j];
}
void World::oneRound(){
    //unaction and delete died creature
    for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 35; ++j){
            if(cell[i][j]){
                cell[i][j]->start(); 
                if(!cell[i][j]->live())
                    cell[i][j] = nullptr;
            }
        }
    }
    for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 35; ++j){
            if(cell[i][j] == nullptr)
                continue;
            int x = j + xDir[randomNum.getRandomNum(0,3)];
            int y = i + yDir[randomNum.getRandomNum(0,3)];
            //cout << "j:" << j << " i:" << i << endl;
            //cout << "x:" << x << " y:" << y << endl;
            if(!cell[i][j]->getActioned()){
                if(x < 0 || x > 34 || y < 0 || y > 19)
                    continue;
                cell[i][j]->Action(&cell[y][x], &cell[i][j]);
            }
        }
    }
    for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 35; ++j){
            if(cell[i][j] != nullptr)
                cell[i][j]->grow();
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
    //「初始回合視為第一回合，第一個參數為總共有多少回合(包含初始回合)；
    //第二個參數則不包含初始回合，指的是除初始回合外每經過多少回合後打印結果，如果出現負數或第一個參數為 0 時也要印出初始回合」
    display();
    cout << "------------------------------------------------------------------------" << endl;
    for(int i = 1; i < numPasses; ++i){

        oneRound();
        if(i % interval == 0){
            //cout << "round: " << i << endl;
            display();
            cout <<"------------------------------------------------------------------------" << endl;
        }
    }
}
