/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include "SHPlayer.h"
#include "SHDealer.h"
#include<algorithm>
#include <iostream>
using namespace std;

// constructor
SHDealer::SHDealer()
:SHPlayer("Dealer")
{
}


// destructor
SHDealer::~SHDealer()
{
}


// distribute a card to the player
int
SHDealer::giveCard()
{
    while(1){
        int RNumber = rand() % 24;
        if(!flag[RNumber]){
            flag[RNumber] = true;
            return deck[RNumber];
        }
    }
    //return test[index];
}


// give the SHPlayer::a card
void
SHDealer::addCard()
{
    int RNumber = rand() % 24;
    while(flag[RNumber]){
        RNumber = rand() % 24;
    }
    flag[RNumber] = true;
    Card tmp(deck[RNumber]);
    SHPlayer::addCard(tmp);
}


// determind who has win the game.
// if both of them have the same pattern,
// the one has more total pips wins the game.
Result
SHDealer::judge(SHPlayer& player)
{
    //cout << "I " << SHPlayer::getHandPattern() << " you " << player.getHandPattern() << endl;
    if(player.getHandPattern() < SHPlayer::getHandPattern())
        return WIN;
    else if(player.getHandPattern() > SHPlayer::getHandPattern())
        return LOSE;
    else{
        if(player.totalPips() < SHPlayer::totalPips())
            return LOSE;
        else if(player.totalPips() > SHPlayer::totalPips())
            return WIN;
        else 
            return TIE;
    }

}


// start a new game(round)
// before starting a new game(round), you should have
// a new deck, and then shuffle it.
// The deck only has pips A, 8, 9, 10, J, Q, K.
void
SHDealer::start()
{
    
    int i = 32;
    for(int j = 0; j < 24; j++){
        flag[j] = false;
        deck[j] = i % 52;
        i++;
    }
    SHPlayer::start();
}


// shuffle the deck of cards
void
SHDealer::shuffle()
{
    std::random_shuffle(deck, deck + sizeof(deck) / sizeof(deck[0]));
}


// open the SHPlayer::s first card
void
SHDealer::openFirstCard()
{
    SHPlayer::openFirstCard();
}


// show the SHPlayer::s hand to the screen
void
SHDealer::showCards() const
{
    SHPlayer::showCards();
}

