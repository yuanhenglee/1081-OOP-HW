extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
}

#include <iostream>
#include <fstream>
#include "AnsiPrint.h"
#include "Queue.h"
#include "Queue.cc"

using namespace std;

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

	istream *is1=&cin,*is2=&cin;

	if (argc>3) {
		PrintUsage(argv[0]);
		exit(-1);
	} else if (argc>2) {
		is2 = new ifstream(argv[2]);
		if (is2==NULL) {
			cerr << "Can't open file " << argv[2] << endl;
			exit(1);
		}
	} 
	if (argc>1) {
		is1 = new ifstream(argv[1]);
		if (is1==NULL) {
			cerr << "Can't open file " << argv[1] << endl;
			exit(2);
		}
	}

	Queue<int> *myIntQPtr=new Queue<int>;
	Queue<char> myCharQ, myCharQ1;

	// test integer queue
	AnsiPrint("Integer Queue:",yellow,nochange,true,false);
	cout<<endl;

	// enqueue exercises on myIntQPtr

	int IntTmp;
	while(*is1 >> IntTmp)
		myIntQPtr->enqueue(IntTmp);


	// test copy constructor
	Queue<int> myIntQ = *myIntQPtr;

	// test destructor
	delete myIntQPtr;

	// dequeue exercises on myIntQ

	while(!myIntQ.IsEmpty()){
		cout<<myIntQ.gethead()<<endl;
		myIntQ.dequeue();
	}

	// test character queue
	AnsiPrint("Character Queue:",yellow,nochange,true,false);
	cout<<endl;

	// enqueue exercises on myCharQ

	char CharTmp;
	while(*is2 >> CharTmp)
		myCharQ.enqueue(CharTmp);

	//// test assignment operator

	myCharQ1=myCharQ;

	//// dequeue exercise on myCharQ1
	while(!myCharQ1.IsEmpty()){
		cout<<myCharQ1.gethead()<<endl;
		myCharQ1.dequeue();
	}
	myCharQ1.dequeue();

	PrintMyID("107703004");
	return 0;

}
