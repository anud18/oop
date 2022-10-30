/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include "SHPlayer.h"
#include "SHDealer.h"
#include<algorithm>
#include <iostream>
using namespace std;

// constructor
SHDealer::SHDealer()
:dealer("Dealer")
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
    return deck[index++];
}


// give the dealer a card
void
SHDealer::addCard()
{
    Card tmp(deck[index++]);
    dealer.addCard(tmp);
}


// determind who has win the game.
// if both of them have the same pattern,
// the one has more total pips wins the game.
Result
SHDealer::judge(SHPlayer& player)
{
    if(player.getHandPattern() < dealer.getHandPattern())
        return WIN;
    else if(player.getHandPattern() > dealer.getHandPattern())
        return LOSE;
    else{
        if(player.totalPips() < dealer.totalPips())
            return LOSE;
        else if(player.totalPips() > dealer.totalPips())
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
        deck[j] = i % 52;
        i++;
    }
    dealer.start();
    this->shuffle();
    index = 0;
}


// shuffle the deck of cards
void
SHDealer::shuffle()
{
    std::random_shuffle(deck, deck + sizeof(deck) / sizeof(deck[0]));
}


// open the dealer's first card
void
SHDealer::openFirstCard()
{
    dealer.openFirstCard();
}


// show the dealer's hand to the screen
void
SHDealer::showCards() const
{
    dealer.showCards();
}

