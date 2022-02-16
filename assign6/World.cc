#include <iostream>
#include "RandomNum.h"
#include "World.h"

using namespace std;

void 
World::printWorld(){
  cout<<"  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4"<<endl;
  for( int i = 0 ; i < mapH ; ++i ){
    cout<<i%10<<" ";
    for( int j = 0 ; j < mapW ; ++j ){
      if( map[i][j] == NULL ){
        cout<<"  ";
        continue;
      } 
      cout<<map[i][j]->_creatureType<<" ";
    }
    cout<<endl;
  }
  cout<<"------------------------------------------------------------------------ "<<endl;
}
World::World(int numPasses,int seed) : _numPasses(numPasses){
  if( _numPasses < 1 ) _numPasses = 1;
  rand = new RandomNum (seed);
  _curNPass = 0;
  map = new Creature**[mapH];
  for( int i = 0 ; i < mapH ; ++i ){
    map[i] = new Creature*[mapW]; 
    for( int j = 0 ; j <mapW ; ++j ){
      map[i][j] = NULL;
    }
  }

  for( int i = 0 ; i < initGrass ;  ){
    int x = rand->getRandomNum(0,mapH-1) ,y = rand->getRandomNum(0,mapW-1);
    if( map[x][y] == NULL ){
      map[x][y] = new Grass;
      ++i;
    }
  }
  for( int i = 0 ; i < initGoat ;  ){
    int x = rand->getRandomNum(0,mapH-1) ,y = rand->getRandomNum(0,mapW-1);
    if( map[x][y] == NULL ){
      map[x][y] = new Goat;
      ++i;
    }
  }
}
void 
World::mainLoop(int displayInterval){
  if( displayInterval<0 ) displayInterval = 1;
  for( _curNPass = 0 ; _curNPass < _numPasses ; ++_curNPass ){

    for( int i = 0 ; i < mapH ; ++i )
      for( int j = 0 ; j < mapW ; ++j )
        if( map[i][j] != NULL )
          map[i][j]->moved = false;

    for( int pI = 0 ; pI < mapH ; ++pI ){
      for( int pJ = 0 ; pJ < mapW ; ++pJ ){
        int i = pI,j = pJ;
        if( map[i][j] == NULL || map[i][j]->moved) continue;
        if( map[i][j]->pregnant() )
         birth(i,j);
        else if( map[i][j]->_creatureType == 'X' )
          move(i,j);
        if( map[i][j]->dailyStatus() ){
          delete [] map[i][j];
          map[i][j] = NULL;  
        }
      }
    }
    if(_curNPass % displayInterval == 0)
      printWorld();
  }
}

void
World::move(int &target_x,int &target_y){
  int x = target_x,y = target_y;
  switch( rand->getRandomNum(0,3)){
    case 0:
      ++x;
      break;
    case 1:
      --x;
      break;
    case 2:
      ++y;
      break;
    case 3:
      --y;
      break;
  }
  if( x>=0 && x<mapH && y >=0 && y<mapW && map[target_x][target_y]->cellValid(map,x,y) ){
    map[x][y] = map[target_x][target_y];
    map[target_x][target_y] = NULL;
    target_x = x;
    target_y = y;
  }
}

void 
World::birth(int target_x,int target_y){
  int x = target_x,y = target_y;
  switch( rand->getRandomNum(0,3)){
    case 0:
      ++x;
      break;
    case 1:
      --x;
      break;
    case 2:
      ++y;
      break;
    case 3:
      --y;
      break;
  }
  if( x>=0 && x<mapH && y >=0 && y<mapW && map[target_x][target_y]->cellValid(map,x,y) ){
    if( map[target_x][target_y]->_creatureType == 'X' )
    map[x][y] = new Goat;
    else
      map[x][y] = new Grass;
  }
}


bool
Goat::cellValid(Creature ***map,int x,int y){
  if( map[x][y] == NULL )
    return true;
  else if( map[x][y]->_creatureType == 'I' ){
    foodP+=5;
    delete [] map[x][y];
    return true;
  }
  return false;
}

bool
Grass::cellValid(Creature ***map,int x,int y){
  return map[x][y] == NULL;
}

bool 
Goat::dailyStatus(){
  --foodP;
  ++age;
  moved = true;
  return age>70 || foodP<0;
}

bool 
Grass::dailyStatus(){
  ++age;
  moved = true;
  return age>6;
}


Creature::Creature():age(0),moved(true){}

Goat::Goat(): Creature(),foodP(20){ 
  Creature::_creatureType = 'X';
}

Grass::Grass(): Creature(){ 
  Creature::_creatureType = 'I';
}

