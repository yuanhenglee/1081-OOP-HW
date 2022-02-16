#ifndef _VECTOR_H
#define _VECTOR_H

#include <iostream>

using namespace std;


// scalar multiplication
class Vector;
Vector operator* (double scale, Vector v);

class Vector {

public:

    // default constrcutor
    Vector();

    // construct a vector of the give dimension
    Vector(int dimension);

    // constructor for easier initialization
    Vector(int size, const double elements[]);

    // copy constructor
    Vector(const Vector &source);

    // destructor
    ~Vector();

    // get the dimension of the vector
    int getDimension() const;

    /**
     * set the dimension of the vector
     * vector is trucated if the new dimension is shorter than the current one
     * vector is copied over if the new dimension is longer
     */
    void setDimension(int dimension);

    /* operator overloading */
    // assignment operator
    Vector & operator=(const Vector &v2);

    // element access
    // You need to have two versions: a constant one and non-constant one
    double & operator[] (int index);
    double operator[] (int index) const;

    // addition of two vectors
    Vector operator+ (const Vector &v2) const;
    // substraction of two vectors
    Vector operator- (const Vector &v2) const;
    // add the given vector to the current one
    Vector & operator+= (const Vector &v2);
    // substract the given vector to the current one
    Vector & operator-= (const Vector &v2);
    // unary negation operator
    Vector operator- ();
    // scalar multiplication and assignment
    Vector operator* (double scale);
    // scalar multiplication and assignment
    Vector & operator*= (double scale);
    // equality
    bool operator== (const Vector &v2) const;
    // inequality
    bool operator!= (const Vector &v2) const;
    // length of a vector
    double length() const;
    // display the vector to the output stream
    friend ostream & operator << (ostream &os, const Vector &v);
    //double operator*();
    
private:

    // initialization routine for allocating appropriate memory
    void initialize(int size);
    // current allocated number of elements >= fDimension
    int allocSize = 0;
    // dimension of the vector
    int fDimension = 0;
    // array of double for storing vector elements
    double *fElements;

};

#endif
