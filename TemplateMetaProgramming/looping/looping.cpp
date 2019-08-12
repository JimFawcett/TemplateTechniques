/////////////////////////////////////////////////////////////////////
// looping.cpp - Compile-time pseudo-iteration via recursion       //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

#include <iostream>

/////////////////////////////////////////////////////////////////////
// simple loop

template <int i>
class LOOP
{
public:
  static inline void EXEC()
  {
    std::cout << i << " ";
    LOOP<i-1>::EXEC();
  }
};

template <>
class LOOP<0>
{
public:
  static inline void EXEC()
  {
    std::cout << 0;
  }
};

/////////////////////////////////////////////////////////////////////
// FOR loop evaluates static function body(int i)

template <int n, class B>
struct FOR
{
  static void iteration(int i)
  {
    B::eval(i);
    FOR<n-1,B>::iteration(i+1);
  }
};

template <class B>
struct FOR<0,B>
{
  static void iteration(int i) {}
};
  
class B
{ 
public: 
  static void eval(int i) 
  { 
    std::cout << i << " "; 
  } 
};
//
/////////////////////////////////////////////////////////////////////
// accumulation

template <int n, template <int> class F>
struct ACCUMULATE
{
  enum { value = ACCUMULATE<n-1,F>::value + F<n>::value };
};

template <template<int> class F> 
struct ACCUMULATE<0,F>
{
  enum { value = F<0>::value };
};

template<int n> struct IDENTITY { enum { value = n }; };

template<int n> struct SQUARE { enum { value = n*n }; };

/////////////////////////////////////////////////////////////////////
// Demonstrations

void main()
{
  std::cout << "\n  Demonstrating TMP Loops";
  std::cout << "\n =========================\n";

  std::cout << "\n  Counting backward from 4:\n  ";
  LOOP<4>::EXEC(); 

  std::cout << "\n\n  Counting forward 10 times:\n  ";
  FOR<10,B>::iteration(0);

  std::cout << "\n\n  Accumulating the natural numbers up to 4,\n  e.g., 0 + 1 + 2 + 3 + 4 = 10:";
  std::cout << "\n  " << ACCUMULATE<4,IDENTITY>::value;   

  std::cout << "\n\n  Accumulating squares of the natural numbers up to 4, \n  e.g., 0 + 1 + 4 + 9 + 16 = 30:";
  std::cout << "\n  " << ACCUMULATE<4,SQUARE>::value;

  std::cout << "\n\n";
}