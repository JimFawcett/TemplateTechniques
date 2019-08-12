/////////////////////////////////////////////////////////////////////
// functions.cpp - compile-time function evaluation                //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

#include <iostream>

/////////////////////////////////////////////////////////////////////
// square

template <int i>
class square { public: enum { value = i*i }; };

/////////////////////////////////////////////////////////////////////
// power

template <int n, int p>
struct POWER
{
  enum { value = n * POWER<n, p-1>::value };
};

template <int n> struct POWER<n,0> { enum { value = 1 }; };

/////////////////////////////////////////////////////////////////////
// Demonstrations

void main()
{
  std::cout << "\n  Demonstrating TMP Functions";
  std::cout << "\n =============================\n";

  std::cout << "\n  square<9>::value   = " << square<9>::value;

  std::cout << "\n  POWER<2,16>::value = " << POWER<2,16>::value;

  std::cout << "\n\n";
}