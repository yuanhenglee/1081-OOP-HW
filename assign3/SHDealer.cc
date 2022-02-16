#include "Card.h"
#include "SHPlayer.h"
#include "SHDealer.h"
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

// constructor
SHDealer::SHDealer()
{
  start();
}


// destructor
SHDealer::~SHDealer()
{
  
}


// distribute a card to the player
void
SHDealer::giveCard(SHPlayer& player)
{
    Card newCard( cardDeck[usedCount++] ); 
    player.addCard( newCard );
}


// give the dealer a card
void
SHDealer::addCard()
{
    Card newCard( cardDeck[usedCount++] ); 
    dealer.addCard( newCard );
}


// determind who has win the game.
// if both of them have the same pattern,
// the one has more total pips wins the game.
Result
SHDealer::judge(SHPlayer& player)
{
  dealer.openFirstCard();
  if( player.getNumCards() < 5 ){
      return LOSE;
  }
  if( player.getHandPattern() < dealer.getHandPattern() ){
    return WIN;
  }
  if( player.getHandPattern() > dealer.getHandPattern() ){
    return LOSE;
  }
  if( player.getHandPattern() == dealer.getHandPattern() ){
    if( player.totalPips() > dealer.totalPips()){
      return WIN;
    }
    if( player.totalPips() == dealer.totalPips() ){
      return TIE;
    }
    else{
    return LOSE;
    }
  }
  return TIE;
}


// start a new game(round)
// before starting a new game(round), you should have
// a new deck, and then shuffle it.
// The deck only has pips A, 8, 9, 10, J, Q, K.
  void
SHDealer::start()
{
  for( int i = 0 ; i < 24 ; ++i ){
    if( i < 4 )
      cardDeck[i] = i;
    else
      cardDeck[i] = i+28;
  }
  shuffle();
  dealer.start();
  usedCount = 0;
}


// shuffle the deck of cards
  void
SHDealer::shuffle()
{
  for( int i = 0 ; i < 28 ; ++i )
    swap( cardDeck[i], cardDeck[rand()%28] );
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
  char const *d = "Dealer     ";
  dealer.showCards(d);
}
