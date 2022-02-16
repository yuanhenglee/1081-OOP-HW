#include<iostream>

using namespace std;


static char card[13][11][12]={{
    "***********",
        "*1x       *",
        "*         *",
        "*         *",
        "*         *",
        "*    x    *",
        "*         *",
        "*         *",
        "*         *",
        "*        1*",
        "***********"

}, {
    "***********",
        "*2x       *",
        "*         *",
        "*    x    *",
        "*         *",
        "*         *",
        "*         *",
        "*    x    *",
        "*         *",
        "*        2*",
        "***********"

}, {
    "***********",
        "*3x       *",
        "*         *",
        "*    x    *",
        "*         *",
        "*    x    *",
        "*         *",
        "*    x    *",
        "*         *",
        "*        3*",
        "***********"

}, {
    "***********",
        "*4x       *",
        "*         *",
        "*  x   x  *",
        "*         *",
        "*         *",
        "*         *",
        "*  x   x  *",
        "*         *",
        "*        4*",
        "***********"

}, {
    "***********",
        "*5x       *",
        "*         *",
        "*  x   x  *",
        "*         *",
        "*    x    *",
        "*         *",
        "*  x   x  *",
        "*         *",
        "*        5*",
        "***********"

}, {
    "***********",
        "*6x       *",
        "*         *",
        "*  x   x  *",
        "*         *",
        "*  x   x  *",
        "*         *",
        "*  x   x  *",
        "*         *",
        "*        6*",
        "***********"

}, {
    "***********",
        "*7x       *",
        "*         *",
        "*  x   x  *",
        "*         *",
        "*  x x x  *",
        "*         *",
        "*  x   x  *",
        "*         *",
        "*        7*",
        "***********"

}, {
    "***********",
        "*8x       *",
        "*         *",
        "*  x   x  *",
        "*    x    *",
        "*  x   x  *",
        "*    x    *",
        "*  x   x  *",
        "*         *",
        "*        8*",
        "***********"

}, {
    "***********",
        "*9x       *",
        "*  x   x  *",
        "*         *",
        "*  x   x  *",
        "*    x    *",
        "*  x   x  *",
        "*         *",
        "*  x   x  *",
        "*        9*",
        "***********"

}, {
    "***********",
        "*10x      *",
        "*  x   x  *",
        "*    x    *",
        "*  x   x  *",
        "*         *",
        "*  x   x  *",
        "*    x    *",
        "*  x   x  *",
        "*       10*",
        "***********"

}, {
    "***********",
        "*Jx       *",
        "*  xxxxx  *",
        "*     x   *",
        "*     x   *",
        "*     x   *",
        "*     x   *",
        "*  x  x   *",
        "*   xxx   *",
        "*        J*",
        "***********"

}, {
    "***********",
        "*Qx       *",
        "*   xxx   *",
        "*  x   x  *",
        "*  x   x  *",
        "*  x   x  *",
        "*  x  xx  *",
        "*   xxxx  *",
        "*       x *",
        "*        Q*",
        "***********"

}, {
    "***********",
        "*Kx       *",
        "*  x   xx *",
        "*  x  x   *",
        "*  x x    *",
        "*  xx     *",
        "*  x x    *",
        "*  x  x   *",
        "*  x   xx *",
        "*        K*",
        "***********"

}};

void PrintCard( int rank, char suit){
    for( int i = 0; i < 11 ; ++i ){
        for( int j = 0 ;j < 11 ; ++j ){
            if( card[rank-1][i][j] == 'x' )
                cout<<suit;
            else
                cout<<card[rank-1][i][j];

        }
        cout<<endl;
    }
}

int suitcmp( char s ){
    switch(s){
        case 'S':
            return 3;
            break;
        case 'H':
            return 2;
            break;
        case 'D':
            return 1;
            break;
        case 'C':
            return 0;
            break;
    }
    return -1;
}

void cardcmp( int r1,int r2,char s1,char s2 ){
    if( r1<0 || r1>13 || r2<0 || r2>13 || suitcmp(s1)<0 || suitcmp(s2)<0 )
        cout<<"can not compare"<<endl;
    else if( (r1+10)%13 > (r2+10)%13 )
        PrintCard(r2,s2);
    else if( (r1+10)%13 < (r2+10)%13 )
        PrintCard(r1,s1);
    else if( suitcmp(s1) > suitcmp(s2) )
        PrintCard(r2,s2);
    else
        PrintCard(r1,s1);
}

int main(){
    int r1,r2;
    char s1,s2;
    //while( scanf("%d%c%d%c",&r1,&s1,&r2,&s2) == 4 ){
    while( (cin>>r1>>s1>>r2>>s2) > 0 ){
        cardcmp(r1,r2,s1,s2);		
    }	

}
