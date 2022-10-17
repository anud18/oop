/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
}

#include <iostream>
#include <cassert>
#include "Card.h"
#include "SHPlayer.h"
#include "AnsiPrint.h"

using namespace std;


/**
 * Print my ID
 */
	void
PrintMyID(const char* studId)
{
	char *str = new char[sizeof(studId) + 5];
	sprintf(str, "ID: %s", studId);
	AnsiPrint(str, yellow, red, true, true);
	cout << endl << endl;
	delete [] str;
}


/**
 * print the usage
 */
	void
PrintUsage(const char* progName)
{
	assert(progName);
	cout << "Usage: " << progName << " [Seed] [ShowFirst(0/1)]" << endl;
}

bool take[52] = {false};

int getCard(){
	int p = rand() % 52;
	while(take[p]){
		p = rand() % 52;
		take[p] = true;
	}
	return p;
}
void showHandType(HandType handType){
	cout << "It's ";
	switch(handType){
		case STRAIGHT_FLUSH:
			cout << "Straight flush" << endl;
			break;
		case FOUR_OF_A_KIND:
			cout << "Four of a kind" << endl;
			break;
		case FULL_HOUSE:
			cout << "Full house" << endl;
			break;
		case FLUSH:
			cout << "Flush" << endl;
			break;
		case STRAIGHT:
			cout << "Straight" << endl;
			break;
		case THREE_OF_A_KIND:
			cout << "Three of a kind" << endl;
			break;
		case TWO_PAIR:
			cout << "Two pair" << endl;
			break;
		case ONE_PAIR:
			cout << "One pair" << endl;
			break;
		case OTHER:
			cout << "Other" << endl;
			break;
	}
}

	int
main(int argc, char** argv)
{
	bool showFirst = false;
	long seed = 0;

	if( argc > 3 ) {
		PrintUsage(argv[0]);
		exit(-1);
	}
	if( argc == 3 ) {
		showFirst = atoi(argv[2]);      // the third argument shows the first card
	}
	if( argc > 1 ) {
		seed = atoi(argv[1]);
	}
	srand(seed);


	SHPlayer shplayer("Player");
	shplayer.start();

	// put your code here
	for(int i = 0; i < 5; ++i){
		//int jj = getCard();
		Card tmp;
		tmp.setID(getCard());
		shplayer.addCard(tmp);
	}
	showHandType(shplayer.getHandPattern());

	shplayer.showCards();


	PrintMyID("110703060");

	return 0;
}

