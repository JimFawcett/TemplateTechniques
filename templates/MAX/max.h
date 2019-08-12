#ifndef MAX_H
#define MAX_H
/////////////////////////////////////////////////////////////////////
// max.h - return maximum of two arguments                         //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

template<class T> T max(const T& t1, const T& t2)
{
  cout << "\n  -- not using specialization";
  return ((t2 > t1) ? t2 : t1);
}

typedef char* pChar;  // typedef is required

template<> pChar max(const pChar& t1, const pChar& t2);

//----< specialization of max template >-----------------------------
//
//  Since this function has no template parameters it could be
//  placed in the max.cpp file.  In that case, users would add
//  the max.cpp file to their project.  Since we are inlining
//  the function, users need only include the header file.
//
template<> inline pChar max(const pChar& t1, const pChar& t2)
{
  cout << "\n  -- using specialization";
  return ((strcmp(t1,t2)>0) ? t1 : t2);
}
//
#endif
