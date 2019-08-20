///////////////////////////////////////////////////////////////////////////
// Adder.cpp - simple example of variadic template function              //
// Source:  Eli Bendersky,                                               //
//          https://eli.thegreenplace.net/2014/variadic-templates-in-c/  //
// Adapted: Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018    //
///////////////////////////////////////////////////////////////////////////

#include "Adder.h"
#include <iostream>

int main()
{
  std::cout << "\n  Demo of variadic template function";
  std::cout << "\n ====================================";

  long sum = adder(1, 2, 3, 4, 5);
  std::cout << "\n  the sum of 1 + 2 + 3 + 4 + 5 = " << sum;
  std::cout << "\n";
  double dsum = adder(1.5, 2.5, 2.5, 4.5);
  std::cout << "\n  the sum of 1.5 + 2.5 + 3.5 + 4.5 = " << dsum;
  std::cout << "\n\n";
  return 0;
}