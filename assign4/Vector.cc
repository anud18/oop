#include<iostream>
#include"Vector.h"
#include<cmath>

using namespace std;

Vector::Vector(){
    initialize(2);
    fDimension = 2;
}

Vector::Vector(int dimension){
    initialize(dimension);
}

Vector::Vector(int size, const double element[]){
    initialize(size);
    for(int i = 0; i < size; ++i)
        fElements[i] = element[i];
}

Vector::Vector(const Vector &source){
    fDimension = source.getDimension();
    fElements = new double[fDimension];
    for(int i = 0; i < fDimension; ++i)
        fElements[i] = source[i];
}

Vector::~Vector(){
    delete []fElements;
}

int Vector::getDimension() const{
    return fDimension;
}

void Vector::setDimension(int dimension){
    if(dimension != fDimension){
        double *tmp = new double[dimension]{};
        for(int i = 0; i < dimension; ++i){
            tmp[i] = fElements[i];
            if(i >= fDimension)
                tmp[i] = 0;
        }
        delete []fElements;
        initialize(dimension);
        for(int i = 0; i < dimension; ++i)
            fElements[i] = tmp[i];
        delete []tmp;
    }
}

Vector &Vector::operator=(const Vector &v2){
    if(this ==  &v2)
        return *this;
    delete []fElements;
    fDimension = v2.getDimension();
    fElements = new double[fDimension];
    for(int i = 0; i < fDimension; ++i)
        fElements[i] = v2[i];
    return *this;   
}
double &Vector::operator[] (int index){
    if(index >= 0 && index < fDimension)
        return fElements[index];
    cerr << "Subscript out of range\n";
    return fElements[0];
}

double Vector::operator[] (int index) const{
    if(index >= 0 && index < fDimension)
        return fElements[index];
    cerr << "Subscript out of range\n";
    return fElements[0];
}
Vector Vector::operator+ (const Vector &v2) const{
    Vector tmp(*this);
    for(int i = 0; i < fDimension; ++i)
        tmp[i] += v2.fElements[i];
    return tmp;
}
    // substraction of two vectors
Vector Vector::operator- (const Vector &v2) const{
    Vector tmp(*this);
    for(int i = 0; (i < fDimension) && i < v2.getDimension(); ++i)
        tmp[i] -= v2.fElements[i];
    return tmp;
}
    // add the given vector to the current one
Vector &Vector::operator+= (const Vector &v2){
    for(int i = 0; (i < fDimension) && i < v2.getDimension(); ++i)
        fElements[i] += v2.fElements[i];
    return *this;
}
    // substract the given vector to the current one
Vector &Vector::operator-= (const Vector &v2){
    for(int i = 0; (i < fDimension) && i < v2.getDimension(); ++i)
        fElements[i] -= v2.fElements[i];
    return *this;
}
    // unary negation operator
Vector Vector::operator- (){
    Vector tmp(*this);
    for(int i = 0; i < fDimension; ++i)
        tmp[i] *= -1;
    return tmp;
}
    // scalar multiplication and assignment
Vector Vector::operator* (double scale){
    Vector tmp(*this);
    for(int i = 0; i < fDimension; ++i)
        tmp.fElements[i] *= scale;
    return tmp;
}
    // scalar multiplication and assignment
Vector &Vector::operator*= (double scale){
    for(int i = 0; i < getDimension(); ++i)
        fElements[i] *= scale;
    return *this;
}
    // equality
bool Vector::operator== (const Vector &v2) const{
    if(getDimension() != v2.getDimension())
        return false;
    for(int i = 0; i < getDimension(); ++i){
        if(fElements[i] != v2.fElements[i])
            return false;
    }
    return true;
}
    // inequality
bool Vector::operator!= (const Vector &v2) const{
    if(getDimension() != v2.getDimension())
        return true;
    for(int i = 0; i < getDimension(); ++i){
        if(fElements[i] != v2.fElements[i])
            return true;
    }
    return false;
}

    // length of a vector
double Vector::length() const{
    double tmp = 0;
    for(int i = 0; i < getDimension(); ++i)
        tmp += fElements[i] * fElements[i];
    return sqrt(tmp);
}
    // display the vector to the output stream
ostream& operator << (ostream &os, const Vector &v){
    os << '(';
    for(int i = 0; i < v.getDimension() - 1; ++i){
        os << v[i] << ", ";
    }
    os << v[v.getDimension() - 1] << ')';
    return os;
}
    //double operator*();
Vector operator* (double scale, Vector v){
    return v*scale;
}
void Vector::initialize(int size){
    fDimension = size;
    fElements = new double[fDimension]{};
}







































