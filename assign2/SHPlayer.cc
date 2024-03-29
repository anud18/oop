/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include <iostream>
#include <cstring>
#include <cassert>
#include "AnsiPrint.h"
#include "Card.h"
#include "CardPattern.h"
#include "SHPlayer.h"


using namespace std;

const char* HandTypeName[9] = {
	"Straight flush",
	"Four of a kind",
	"Full house",
	"Flush",
	"Straight",
	"Three of a kind",
	"Two pair",
	"One pair",
	"Other"
};

// constructor
SHPlayer::SHPlayer(const char* playerName)
{
	this->name = playerName;

}

// initialize the number of cards to 0
	void
SHPlayer::start()
{
	numCards = 0;
}

// add a new card to the current hand
// need to protect the array from overflowing
void SHPlayer::addCard(Card newCard)
{		
	if(numCards < 5 && numCards >= 0)
		cards[numCards++] = newCard;	
}

// open the first card so it faces up
	void
SHPlayer::openFirstCard()
{
	showFirstCard = true;

}

// print the current hand to the screen graphically
void
SHPlayer::showCards() const
{
	char suit[4] = {'S', 'H', 'D', 'C'};
	//for(int i = 0; i < 5; ++i)
	for(int i = 0; i < kCardHeight; ++i){
		for(int j = 0; j < 5; j++, cout << ' '){
			if(j == 0 && !showFirstCard){
				AnsiPrint(card[13][i], white, white, false, false);
				continue;
			}
			string tmp1(card[cards[j].getPip()][i]);
			for(auto& it : tmp1)
				if(it == 'x')
					it = suit[cards[j].getSuit()];
			const char* tmp2 = tmp1.c_str();
			if(cards[j].getSuit() == 0 || cards[j].getSuit() == 3)
				AnsiPrint(tmp2, black, white, false, false);
			else 
				AnsiPrint(tmp2, red, white, false, false);

		}
		cout << endl;
	}
}

// get the total points of the current hand
int
SHPlayer::totalPips() const
{
	int sum = 0;
	for(int i = 0; i < kMaxCards; ++i)
		if(cards[i].getID() >= 0)
			sum += cards[i].getPip() + 1;
	return sum;
}

// judge what kind of hand type you own
// you need to have 5 cardsHandType
	HandType
SHPlayer::getHandPattern() 
{
	sortCards();
	if(isStraightFlush())
		return STRAIGHT_FLUSH;
	if(isFourOfAKind())
		return FOUR_OF_A_KIND;
	if(isFullHouse())
		return FULL_HOUSE;
	if(isFlush())
		return FLUSH;
	if(isStraight())
		return STRAIGHT;
	if(isThreeOfAKind())
		return THREE_OF_A_KIND;
	if(isTwoPair())
		return TWO_PAIR;
	if(isOnePair())
		return ONE_PAIR;
	return OTHER;

}

// return the number of cards at hand
int
SHPlayer::getNumCards() const
{
	int count = 0;
	for(int i = 0; i < kMaxCards; ++i)
		if(cards[i].getID() >= 0)
			count++;
	return count;
}

	void
SHPlayer::sortCards() 
{
	for(int i = 0; i < kMaxCards; ++i)
		sortedCards[i].setID(cards[i].getID());
	for(int i = 0; i < kMaxCards; ++i){
		for(int j = i + 1; j < kMaxCards; ++j){
			if(sortedCards[i].getID() > sortedCards[j].getID()){
				Card tmp = sortedCards[i];
				sortedCards[i] = sortedCards[j];
				sortedCards[j] = tmp;
			}
		}
	}
}

// any five card sequence of same suit
bool 
SHPlayer::isStraightFlush() const
{
	return isStraight() && isFlush();
}

// four cards of the same pip
bool 
SHPlayer::isFourOfAKind() const
{
	// O O O O X
	if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
			sortedCards[2].getPip() == sortedCards[3].getPip() &&
			sortedCards[0].getPip() == sortedCards[2].getPip() )
		return true;
	// X O O O O
	if( sortedCards[1].getPip() == sortedCards[2].getPip() &&
			sortedCards[3].getPip() == sortedCards[4].getPip() &&
			sortedCards[1].getPip() == sortedCards[3].getPip() )
		return true;

	return false;
}

// three of a kind combined with a pair
bool 
SHPlayer::isFullHouse() const
{
	// O O O X X
	if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
			sortedCards[1].getPip() == sortedCards[2].getPip() &&
			sortedCards[3].getPip() == sortedCards[4].getPip() )
		return true;
	// X X X O O
	if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
			sortedCards[2].getPip() == sortedCards[3].getPip() &&
			sortedCards[3].getPip() == sortedCards[4].getPip() )
		return true;

	return false;
}

// five cards of the same suit
bool
SHPlayer::isFlush() const
{
	for( int i = 0; i < kMaxCards - 1; i++ )
		if( sortedCards[i].getSuit() != sortedCards[i+1].getSuit() )
			return false;

	return true;
}

// five cards in sequence
bool 
SHPlayer::isStraight() const
{
	for( int i = 0; i < kMaxCards - 1; i++ )
		if( sortedCards[i].getPip() + 1 != sortedCards[i+1].getPip() )
			return false;

	return true;
}

// three cards of the same pip
bool 
SHPlayer::isThreeOfAKind() const
{
	for( int i = 0; i < kMaxCards - 2; i++ )
		if( sortedCards[i].getPip() == sortedCards[i+1].getPip() &&
				sortedCards[i].getPip() == sortedCards[i+2].getPip() )
			return true;

	return false;
}

// two cards of one pip, two cards of another pip
bool 
SHPlayer::isTwoPair() const
{
	// O O @ @ X
	if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
			sortedCards[2].getPip() == sortedCards[3].getPip() )
		return true;
	// O O X @ @
	if( sortedCards[0].getPip() == sortedCards[1].getPip() &&
			sortedCards[3].getPip() == sortedCards[4].getPip() )
		return true;
	// X O O @ @
	if( sortedCards[1].getPip() == sortedCards[2].getPip() &&
			sortedCards[3].getPip() == sortedCards[4].getPip() )
		return true;

	return false;
}

// two cards of one pip
bool 
SHPlayer::isOnePair() const
{
	for( int i = 0; i < kMaxCards - 1; i++ )
		if( sortedCards[i].getPip() == sortedCards[i+1].getPip() )
			return true;

	return false;
}


