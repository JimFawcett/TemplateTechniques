/////////////////////////////////////////////////////////////////////
// crtp.cpp - Curiously Recurring Template Pattern                 //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2006       //
/////////////////////////////////////////////////////////////////////

#include "crtp.h"
#include <string>
#include <iostream>

class Apple : public Compare<Apple>   // CRTP
{
public:
  Apple(size_t size) : size_(size) {}
  size_t size() const { return size_; }
private:
  size_t size_;
};

bool operator<(Apple const& aLft, Apple const& aRgt)
{
  return aLft.size() < aRgt.size();
}

class Person : public Compare<Person>   // CRTP
{
public:
  Person(const std::string& name) : name_(name) {}
  std::string name() const { return name_; }
private:
  std::string name_;
};

bool operator<(Person const& pLft, Person const& pRgt)
{
  return pLft.name() < pRgt.name();
}

std::string predValue(bool op)
{
  if (op) return "true";
  return "false";
}

int main(int argc, char* argv[])
{
  std::cout << "\n  Demonstrate the Curiosly Recurring Template Pattern (CRTP)";
  std::cout << "\n ============================================================\n";

  std::cout << "\n  Comparing apple sizes";
  std::cout << "\n -----------------------";

  Apple aBig(3), aSmall(1);
  std::cout << "\n  aBig   <  aSmall  is " << predValue(aBig < aSmall);
  std::cout << "\n  aBig   == aSmall  is " << predValue(aBig == aSmall);
  std::cout << "\n  aBig   != aSmall  is " << predValue(aBig != aSmall);
  std::cout << "\n  aBig   >  aSmall  is " << predValue(aBig > aSmall);
  std::cout << "\n  aBig   == aBig    is " << predValue(aBig == aBig);
  std::cout << "\n  aSmall != aSmall  is " << predValue(aSmall != aSmall);
  std::cout << "\n";

  std::cout << "\n  Comparing people's names";
  std::cout << "\n --------------------------";

  Person ashok("Ashok"), xing("Xing");
  std::cout << "\n  ashok <  xing     is " << predValue(ashok < xing);
  std::cout << "\n  ashok == xing     is " << predValue(ashok == xing);
  std::cout << "\n  ashok != xing     is " << predValue(ashok != xing);
  std::cout << "\n  ashok >  xing     is " << predValue(ashok > xing);
  std::cout << "\n  ashok == ashok    is " << predValue(ashok == ashok);
  std::cout << "\n  xing  != xing     is " << predValue(xing != xing);
  std::cout << "\n\n";
}
