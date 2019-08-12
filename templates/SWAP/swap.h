#ifndef SWAP_H
#define SWAP_H
///////////////////////////////////////////////////////////////////////
// swap.cpp - demonstrate function templates                         //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004         //
///////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

template <class T> void swap(T& t1, T& t2) {

  T temp = t1;
  t1 = t2;
  t2 = temp;
  return;
}

#endif
