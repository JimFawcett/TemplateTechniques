/////////////////////////////////////////////////////////////////////////
// pair.cpp - demonstrate class templates                              //
//            Example in:                                              //
//            Murray, C++ Strategies and Tactics, Addison-Wesley, 1993 //
//                                                                     //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004           //
/////////////////////////////////////////////////////////////////////////

#ifdef TEST_PAIR

#include "pair.h"

demo::pair<int,double> funct(int x, double y) 
{
  demo::pair<int,double> temp(2*x,x+y);
  return temp;
}

#include <iostream>
using namespace std;

void main() 
{
  cout << "  Demonstrating Template Class - pair<L,R>\n"
       << " ==========================================\n\n";

  int x = 3; double y = 5.555;

  demo::pair<int,double> myPair = funct(x,y);

  cout << "  funct returned myPair("
       << myPair.left()
       << ", "
       << myPair.right()
       << ")" << endl<< endl;
}

#endif
