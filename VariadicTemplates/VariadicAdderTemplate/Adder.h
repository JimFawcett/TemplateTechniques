#pragma once
///////////////////////////////////////////////////////////////////////////
// Adder.h - simple example of variadic template function                //
// Source:  Eli Bendersky,                                               //
//          https://eli.thegreenplace.net/2014/variadic-templates-in-c/  //
// Adapted: Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018    //
///////////////////////////////////////////////////////////////////////////

// Template specialization stops recursive evaluation

template <typename T>
T adder(T t) {
  std::cout << "\n  " << __FUNCSIG__ << "\n";
  return t;
}

// Recursive evaluation of template function
// - Displays function signature to show that each of these
//   evaluations results in a compiled function.

template<typename T, typename... Args>
T adder(T first, Args... args) {
  std::cout << "\n  " << __FUNCSIG__;
  return first + adder(args...);
}


