/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include "SHGame.h"
#include "SHPlayer.h"
#include "SHDealer.h"
#include <iostream>

using namespace std;


// only constructor
// Must be given a valid (initialized) game player and dealer
// Menu is constructed internally to provide basic text interface
// We must use an initialization list here.
SHGame::SHGame(SHPlayer& shp, SHDealer& shd)
  : menu(sizeof(menuItems)/sizeof(char*), menuItems),player(shp),dealer(shd)
{
  playerPoint = initCredit;
  dealerPoint = initCredit;
  dealer.start();
  player.start();
  player.openFirstCard();
}


// one run of the game
// take and process a user action
// show current hands for both players at the end of a run.
  bool
SHGame::oneRun()
{
  menu.print();
  switch( menu.getAnswer() ){
    case 1:
      if( gameEnd == true ){
        cout<<"GAME OVER!"<<endl;
        break;
      }
      moreCard();
      break;
    case 2:
      if( gameEnd == true ){
        cout<<"GAME OVER!"<<endl;
        break;
      }
      giveUp();
      break;
    case 3:
      if( gameEnd == false ){
        cout<<"Game is not over yet. Choose \'give up\' to end a game"<<endl;
        break;
      }
      restart();
      break;
    case 4:
      return false;
  }
  char const *p = "Player     ";
  player.showCards(p);
  dealer.showCards();
  return true;
}


// give the player and dealer one more card
// check if we can do that first.
// and judge who has win the round if the player have 5 cards
  void
SHGame::moreCard()
{
  dealer.giveCard(player);
  dealer.addCard();
  if( player.getNumCards() == 5 ){
    printResult(dealer.judge(player)) ; 
    gameEnd = true;
  }
}

void 
SHGame::printResult(Result res){
  if( res == WIN ){
    cout<<"You win. Good job.(You have ";
    playerPoint+=player.getNumCards();
    dealerPoint-=player.getNumCards();
    cout<<playerPoint<<" points, I Have "<<dealerPoint<<" points.)"<<endl;
  }
  else if( res == LOSE ){
    cout<<"I win. Try again.(You have ";   
    playerPoint-=player.getNumCards();
    dealerPoint+=player.getNumCards();
    cout<<playerPoint<<" points, I Have "<<dealerPoint<<" points.)"<<endl;
  }
  else
    cout<<"TIE!!(You have "<<playerPoint<<" points, I Have "<<dealerPoint<<" points.)"<<endl;

}


// give up this round,
// and you'll lose your credit
// the bet is equivalent to the number of card you keep
  void
SHGame::giveUp()
{
  printResult(dealer.judge(player)) ; 
  gameEnd = true;
}

// restart the game by giving each player two new cards
// need to check if any one broke (bankrupt).
  void
SHGame::restart()
{
  if( playerPoint < 1 || dealerPoint < 1 ){
    cout<<"Sorry. Game over. No loan here"<<endl;
    gameEnd = true;
    return;
  }
  gameEnd = false;
  dealer.start();
  player.start();
  player.openFirstCard();
  moreCard();
  moreCard();
}
