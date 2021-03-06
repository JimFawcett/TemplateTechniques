///////////////////////////////////////////////////////////////////
// VariadicFunctionTemplates.cpp - demonstrates variadic mixins  //
//                                                               //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018     //
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

// Helper function
std::string strTrunc(
  const std::string& src, size_t Max = 50
) {
  if (src.size() > Max) {
    return src.substr(0, Max - 4) + " ...";
  }
  else {
    return src;
  }
}

// Template specializ'n stops recursive eval

template<typename T>
void f(T t)
{
  std::cout << "\n  " << t << " : " 
            << strTrunc(typeid(t).name(), 40) 
            << std::endl;
}

// Recursive definition of template function
// Args is a "parameter pack
// https://en.cppreference.com/w/cpp/language/parameter_pack

template<typename T, typename... Args>
void f(T t, Args... args)
{
  std::cout << "\n  " << t << " : " 
            << typeid(t).name() << std::endl;
  f(args...);
}

int main()
{
  std::cout << 
    "\n  Demonstrate Variatic Functions";
  std::cout << 
    "\n ================================\n";

  f(
    1, 3.5, 'z', 
    "a literal string", 
    std::string("a std::string")
  );
  std::cout << "\n\n";
  return 0;
}

