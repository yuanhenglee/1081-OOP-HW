/* Copyright (c) 1999 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
  NAME
  Cards.cc
  NOTE
  You are asked to design this module.
  You need to draw the given number of cards and print them out.
  Assume that you are given a deck of 52 cards. The cards do not reappear.
  That is, you do not put a card back into the deck after it is drawn.
 ***************************************************************************/
#include"Cards.h"
#include<iostream>
#include"AnsiPrint.h"
#include <stdlib.h>

using namespace std;

bool CardUsed[52];

char NumToSuit( int num ){
	switch( num ){
		case 3:
			return 'S';
		case 2:
			return 'H';
		case 1:
			return 'D';
		case 0:
			return 'C';
	}
	return 'X';
}

void PrintCard( int rank[], int suit[] ,int CardsPerRow ){
	char str[kCardWidth+1];
	for( int i = 0; i < kCardHeight ; ++i ){
		for( int CardCount = 0; CardCount < CardsPerRow ; ++CardCount ){
			for( int j = 0; j <= kCardWidth ; ++j ){
				if( card[rank[CardCount]][i][j] == 'x' )
					str[j] = NumToSuit( suit[CardCount] );
				else
					str[j] = card[rank[CardCount]][i][j];
			}
			if( NumToSuit( suit[CardCount] ) == 'H' || NumToSuit ( suit[CardCount] ) == 'D' )
				AnsiPrint( str, red, white, false, false );
			else
				AnsiPrint( str, black, white, false, false );
			if( CardCount == CardsPerRow-1 )//last card in a row
				cout<<endl;
			else
				cout<<" ";
		}
	}
}

void GetCard( int ncards ){
	int rank[5];
	int suit[5];
	int i;
	for( i = 0 ; ncards > 0 ; i++ ){
		if( i == 5 ){
			PrintCard( rank,suit,i );
			i = 0;
		}
		int RandCard = rand()%52;
		while( CardUsed[RandCard] == true ){
			++RandCard;
			RandCard%=52;
		}
		rank[i] = RandCard%13;		
		suit[i] = RandCard/13;		
		CardUsed[RandCard] = true;
		--ncards;
	}	
	if( i != 0 ){
		PrintCard( rank,suit,i );
	}
}

