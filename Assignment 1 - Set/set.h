#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED


#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include "read.hpp"


class Set
{
public:

    enum Exception{EmptyVec, WrongInput};
    Set() : _vec(0) {}
    Set(const std::vector<int> &vec) { _vec = vec; }
    void insert(const int num);
    void print();
    void remove(int num);
    bool empty() const;
    bool contains(int num);
    int random();
    int sum();
    int getLength();



private:
    std::vector<int> _vec;
    int Sum=0;


};



#endif // SET_H_INCLUDED
