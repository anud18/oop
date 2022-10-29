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
	}
		take[p] = true;
    cout << p << ' ';
	return p;
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

	// put your code here
	shplayer.start();
	for(int i = 0; i < 5; ++i){
		Card tmp;
		tmp.setID(getCard());
		shplayer.addCard(tmp);
	}
	if(showFirst)
		shplayer.openFirstCard();

	shplayer.showCards();
	cout << "It's " << HandTypeName[shplayer.getHandPattern()] << endl; 
	cout << "Total points: " << shplayer.totalPips() << endl;


	PrintMyID("110703060");

	return 0;
}

