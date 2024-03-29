/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include "Card.h"
#include <cassert>

using namespace std;

// constructor
Card::Card(int newId)
{
    setID(newId);
}

// Accessor: card id is an integer between 0 and 51.
// Cards of the same pips are together.
// In other words, cards are in the following order:
//    1S 1H 1D 1C 2S 2H ...

int
Card::getID() const 
{
    if((ID / 4) == 0)
        return ID + 52;
    else
        return ID;
}

// get the pip of the card (0-12)
int
Card::getPip() const
{
    if((ID / 4) == 0)
        return ((ID / 4) + 13);
    else
        return ID / 4;
}

// get the suit of the card (0-3)
int
Card::getSuit() const
{
    return ID % 4;
}

// set id directly
    void
Card::setID(int newId)
{
    ID = newId;
}


