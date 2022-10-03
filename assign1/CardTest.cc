/* Copyright (c) 1999 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
  NAME
  CardTest.cc
  PURPOSE
  Testing card displaying
  NOTES

  AUTHOR
  Tsai-Yen Li (li@cs.nccu.edu.tw)
  HISTORY
  Tsai-Yen Li - Oct 7, 1999: Created.
 ***************************************************************************/

/* $Log:$ */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
}

#include <iostream>
#include "AnsiPrint.h"
#include "Cards.h"

using namespace std;

//enum Suit{
//spade,
//heart,
//diamond,
//club;
//}
/**
 * Print my id 
 */
void
PrintMyID(const char *studId) {

	char *str= new char[sizeof(studId)+5];
	// we put string in a buffer first 
	sprintf(str,"ID: %s",studId);
	// print the buffer out with color
	AnsiPrint(str,yellow,red, true, true);
	cout << endl << endl;
	delete [] str;

}


/**
 * PrintUsage
 */
void
PrintUsage(const char *progName) {

	assert(progName);
	cout << "Usage: " << progName << " NCards [Seed]" << endl;

}

void
PrintCard(int cardNo, int line) {
	char suit;
	int pip = cardNo / 4;
	switch(cardNo % 4){
		case 0:
			suit = 'S';
			break;
		case 1:
			suit = 'H';
			break;
		case 2:
			suit = 'D';
			break;
		case 3:
			suit = 'C';
			break;
	}
	char *str= new char[1000];
	char *str1= new char[1000];
	line %= 11;
	pip %= 13;
	for(int width = 0; width < kCardWidth; ++width){
		if(card[pip][line][width] == 'x')
			str[width] = suit;
		else
			str[width] = card[pip][line][width];

	}
	// we put string in a buffer first 
	sprintf(str1,"%s",str);
	// print the buffer out with color
	if(suit == 'H' || suit == 'D')
		AnsiPrint(str1,red,white, false, false);
	else
		AnsiPrint(str1,black,white, false, false);
	cout << ' ';
	delete [] str;
	delete [] str1;

}
bool take[52] = {false};
int* getCard(int cardNumber, long seed){
	srand(seed);
	int *p = new int[cardNumber + 1];
	int i = 0;
	while(i < cardNumber){
		int r = rand() % 52;
		while(take[r]){
			r = rand() % 52;
		}
		p[i++] = r;
		take[r] = true;
	}	
	return p;
}
int* getCard(int cardNumber){
	srand(time(NULL));
	int *p = new int[cardNumber + 1];
	for(int i = 0; i < cardNumber;){
		int r = rand() % 52;
		if(!take[r]){
			take[r] = true;
			p[i++] = r;
		}	
	}	
	return p;
}


/**
 * Main Function Call
 */
int
main(int argc, char **argv) {

	int ncards=0;  // number of cards to draw 
	if (argc==3) {
		long seed=atoi(argv[2]); // the third argument is the seed
		srand(seed);
		ncards=atoi(argv[1]); // the second argument is the number of cards
		if(ncards > 52){
			cout << "Sorry, number of cards can not exceed 52." <<endl;
			return 0;
		}
		
		int* cards = getCard(ncards, seed);

		int count = 0;
		int group = 0;
		int groupNumber = ncards / 5;
		int k;
		while(count < ncards * kCardHeight){
			if(groupNumber == group)
				k = (ncards - 5 * group) % 5;
			else
				k = 5;
			int i = ((count - 5 * group * kCardHeight) % k) + 5 * group;
			i %= ncards;
			PrintCard(cards[i], ((count - 5 * group * kCardHeight)/ k ) % 11);
			count++;
			if((count - 5 * group * kCardHeight)% k == 0 && count)
				cout << endl;
			if(count % 55 == 0)
				group++;
		}

	} else if (argc==2) {
		ncards=atoi(argv[1]);
		if(ncards > 52){
			cout << "Sorry, number of cards can not exceed 52." <<endl;
			return 0;
		}

		int* cards = new int[ncards];
		cards = getCard(ncards);

		int count = 0;
		int group = 0;
		int groupNumber = ncards / 5;
		int k;
		while(count < ncards * kCardHeight){
			if(groupNumber == group)
				k = (ncards - 5 * group) % 5;
			else
				k = 5;
			int i = ((count - 5 * group * kCardHeight) % k) + 5 * group;
			i %= ncards;
			PrintCard(cards[i], ((count - 5 * group * kCardHeight)/ k ) % 11);
			count++;
			if((count - 5 * group * kCardHeight)% k == 0 && count)
				cout << endl;
			if(count % 55 == 0)
				group++;
		}
	} else {
		PrintUsage(argv[0]);
		exit(-1);
	}

	// You are asked to fill in a few missing statements here


	// Print my id at the end of the program

	PrintMyID("110703060");

	return 0;

}
