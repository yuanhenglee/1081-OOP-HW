#include "Vector.h"
#include <iostream>
#include <math.h>

using namespace std;

Vector operator* (double scale, Vector v){
  return v*scale;
}

// default constrcutor
Vector::Vector(){
  initialize(2);
  setDimension(2);
}
// construct a vector of the give dimension
Vector::Vector(int dimension){
  initialize( dimension );
  setDimension( dimension );
}

// constructor for easier initialization
Vector::Vector(int size, const double elements[]){
  initialize( size );
  setDimension( size );
  for( int i = 0 ; i < size ; ++i )
    fElements[i] = elements[i];
}

// copy constructor
Vector::Vector(const Vector &source){
  initialize( source.getDimension() );
  setDimension( source.getDimension() );
  for( int i = 0 ; i < source.getDimension() ; ++i )
    fElements[i] = source[i];
}

// destructor
Vector::~Vector(){
  delete [] fElements;
}

// get the dimension of the vector
int 
Vector::getDimension() const{
  return fDimension;
}

/**
 * set the dimension of the vector
 * vector is trucated if the new dimension is shorter than the current one
 * vector is copied over if the new dimension is longer
 */
void
Vector::setDimension(int dimension){
  if( dimension == fDimension )
    return;
  double *tmp = (double*)realloc(fElements,sizeof(double)*dimension);
  for( int i = fDimension ; i < dimension ; ++i )
    tmp[i] = 0;
  fElements = tmp;
  fDimension = dimension;
}
// operator overloading 
// assignment operator
Vector& 
Vector::operator=(const Vector &v2){
  initialize(v2.getDimension());
  setDimension(v2.getDimension());
  for( int i = 0 ; i < v2.getDimension(); ++i )
    fElements[i] = v2[i];
  return *this; 
}

// element access
// You need to have two versions: a constant one and non-constant one
double& 
Vector::operator[] (int index){
  return fElements[index];
}
double
Vector::operator[] (int index) const{
  return fElements[index];
}

// addition of two vectors
Vector 
Vector::operator+ (const Vector &v2) const{
  if( fDimension != v2.getDimension() ){
    //TODO
    cout<<"ERROR!!!"<<endl;
    return *this;
  }
  Vector tmp(fDimension);
  for( int i = 0 ; i < fDimension ; ++i )
    tmp.fElements[i] = fElements[i] + v2[i];
  return tmp;
}
// substraction of two vectors
Vector 
Vector::operator- (const Vector &v2) const{
  if( fDimension != v2.getDimension() ){
    //TODO
    cout<<"ERROR!!!"<<endl;
    return *this;
  }
  Vector tmp(fDimension);
  for( int i = 0 ; i < fDimension ; ++i )
    tmp.fElements[i] = fElements[i] - v2[i];
  return tmp;
}
// add the given vector to the current one
Vector&
Vector::operator+= (const Vector &v2){
  *this = *this + v2;
  return *this;
}
// substract the given vector to the current one
Vector& 
Vector::operator-= (const Vector &v2){
  *this = *this - v2;
  return *this;
}
// unary negation operator
Vector 
Vector::operator- (){
  return ( *this )*-1;
}
// scalar multiplication and assignment
Vector 
Vector::operator* (double scale){
  Vector tmp(fDimension);
  for( int i = 0 ; i < fDimension ; ++i )
    tmp[i] = fElements[i] * scale;
  return tmp; 
}
// scalar multiplication and assignment
Vector&
Vector::operator*= (double scale){
  *this = *this * scale;
  return *this;
}
// equality
bool 
Vector::operator== (const Vector &v2) const{
  if( fDimension != v2.getDimension() )
    return false;
  for( int i = 0 ; i < fDimension ; ++i )
    if( fElements[i] != v2[i] )
      return false;
  return true;
}
// inequality
bool 
Vector::operator!= (const Vector &v2) const{
  return !(*this == v2 );
}
// length of a vector
double 
Vector::length() const{
  double sum = 0;
  for( int i = 0 ; i < fDimension ; ++i )
    sum += fElements[i] * fElements[i];
  return pow(sum,0.5);
}

// display the vector to the output stream
ostream & operator << (ostream &os, const Vector &v){
  os<<"(";
  int i;
  for( i = 0 ; i < v.getDimension()-1 ; ++i ){
    os<<v[i]<<", ";
  }
  os<<v[i]<<")";
  return os;
}

// initialization routine for allocating appropriate memory
void 
Vector::initialize(int size){
  fElements = (double*)calloc(size,sizeof(double)*size);
  allocSize = size;
}
