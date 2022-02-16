/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cassert>
#include "AnsiPrint.h"
#include "Card.h"
#include "CardPattern.h"
#include "SHPlayer.h"
#include "memory.h"


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
  start();
}

// initialize the number of cards to 0
  void
SHPlayer::start()
{
  numOfCard = 0;
  for( int i = 0 ; i < 52 ; ++i )cardPool[i] = false;
  showFirst = false;

  for( int i = 0 ; i < kMaxCards ; ++i ){
    int RandCard = rand()%52;
	  while( cardPool[RandCard] == true ){
	  	++RandCard;
	  	RandCard%=52;
		}
    Card newCard( RandCard ); 
    addCard( newCard );
  }
}

// add a new card to the current hand
// need to protect the array from overflowing
void SHPlayer::addCard(Card newCard)
{
  cards[numOfCard] = newCard;
  ++numOfCard;
}

// open the first card so it faces up
  void
SHPlayer::openFirstCard()
{
  showFirst = true;
}

char 
SHPlayer::NumToSuit( int num ) const
{
  switch( num ){
    case 0:
      return 'S';
    case 1:
      return 'H';
    case 2:
      return 'D';
    case 3:
      return 'C';
  }
  return 'X';
}

// print the current hand to the screen graphically
void
SHPlayer::showCards() const
{
	char str[kCardWidth+1];
  for( int i = 0; i < kCardHeight ; ++i ){
    for( int CardCount = 0; CardCount < kMaxCards ; ++CardCount ){
      for( int j = 0; j < kCardWidth ; ++j ){
        if( CardCount == 0 && !showFirst )
          str[j] = ' ';
        else if( card[cards[CardCount].getPip()-1][i][j] == 'x' )
          str[j] = NumToSuit( cards[CardCount].getSuit() );
        else
          str[j] = card[cards[CardCount].getPip()-1][i][j];
      }
      str[kCardWidth] = '\0';
      if( cards[CardCount].getSuit() == 1 || cards[CardCount].getSuit() == 2 )
        AnsiPrint( str, red, white, false, false );
      else
        AnsiPrint( str, black, white, false, false );
      if( CardCount == kMaxCards-1 )//last card in a row
        cout<<endl;
      else
        cout<<" ";
    }

  }
}

// get the total points of the current hand
int
SHPlayer::totalPips() const
{
  int sum = 0;
  for( int i = 0 ; i < numOfCard ; ++i ){
    sum += cards[i].getPip();
  }
  return sum;
}

// judge what kind of hand type you own
// you need to have 5 cards
HandType
SHPlayer::getHandPattern() 
{
  sortCards();
  if( isStraightFlush() )
    return STRAIGHT_FLUSH;
  if( isFourOfAKind() )
    return FOUR_OF_A_KIND;
  if( isFullHouse() )
    return FULL_HOUSE;
  if( isFlush() )
    return FLUSH;
  if( isStraight() )
    return STRAIGHT;
  if( isThreeOfAKind() )
    return THREE_OF_A_KIND;
  if( isTwoPair() )
    return TWO_PAIR;
  if( isOnePair() )
    return ONE_PAIR;
  return OTHER;
}

// return the number of cards at hand
int
SHPlayer::getNumCards() const
{
  return numOfCard;
}

  void
SHPlayer::sortCards() 
{
  for( int i = 0 ; i < numOfCard ; ++i )sortedCards[i] = cards[i];
  for( int i = 0 ; i < numOfCard - 1 ; ++i ){
    for( int j = 0 ; j < numOfCard - i  - 1 ; ++j ){
      if( ( sortedCards[j].getPip()+11 )%13 > ( sortedCards[j+1].getPip()+11 )%13 || ( ( sortedCards[j].getPip()+11 )%13 == ( sortedCards[j+1].getPip()+11 )%13 && sortedCards[j].getSuit() < sortedCards[j+1].getSuit())){
        Card temp = sortedCards[j];
        sortedCards[j] = sortedCards[j+1];
        sortedCards[j+1] = temp;
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


