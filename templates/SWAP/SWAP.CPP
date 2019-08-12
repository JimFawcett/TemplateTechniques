///////////////////////////////////////////////////////////////////////
// swap.cpp - demonstrate function templates                         //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004         //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include "swap.h"
using namespace std;

void main() {

  cout << "Demonstrating Template Function - swap(T& t1, T& t2)\n"
       << "====================================================\n";

  int x = 1; int y = 2;

  cout << "\nbefore swapping integers:\n";
  cout << "  x is " << x << endl;
  cout << "  y is " << y << endl;

  ::swap(x,y);  
  
    // global resolution operator needed to resolve
    // ambiguity with std::swap

  cout << "after swapping integers:\n";
  cout << "  x now is " << x << endl;
  cout << "  y now is " << y << endl;

  double u = 1.5; double v = 2.5;

  cout << "\nbefore swapping doubles:\n";
  cout << "  u is " << u << endl;
  cout << "  v is " << v << endl;

  ::swap(u,v);

  cout << "after swapping doubles:\n";
  cout << "  u now is " << u << endl;
  cout << "  v now is " << v << endl;

  char *s = "a string";
  char *t = "more string";
  cout << "\nbefore swapping C strings:\n";
  cout << "  s = \"" << s << "\"\n";
  cout << "  t = \"" << t << "\"\n";

  ::swap(s,t);

  cout << "\nafter swapping C strings:\n";
  cout << "  s = \"" << s << "\"\n";
  cout << "  t = \"" << t << "\"\n";

  cout << endl;

}