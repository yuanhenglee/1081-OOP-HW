extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
}

using namespace std;
#include <iostream>
#include "AnsiPrint.h"
#include"RandomNum.h"
#include"World.h"
/**
 * Print my id 
 */

void
PrintMyID(const char *studId) {
  char *str= new char[strlen(studId)+5];
  sprintf(str,"ID: %s",studId);
  AnsiPrint(str,yellow,red,true,true);
  cout << endl ;
  delete [] str;

}

/**
 * PrintUsage
 */

void
PrintUsage(const char *progName) {

  assert(progName);
  cout << "Usage: " << progName << " [passes [display [seed]]]" << endl;

}

int
main(int argc, char **argv) {

  int seed=0;
  int numPasses=1;
  int displayInterval=1;

  if (argc>4) {
    PrintUsage(argv[0]);
    return -1;
  } else if (argc==4) {
    seed = atoi(argv[3]);
  }
  if (argc>2) {
    displayInterval=atoi(argv[2]);
  }
  if (argc>1) {
    numPasses = atoi(argv[1]);
  }

  World fate(numPasses,seed);

  fate.mainLoop(displayInterval);

  PrintMyID("107703004");
  return 0;

}

