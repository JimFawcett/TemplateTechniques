#ifndef CRTP_H
#define CRTP_H
/////////////////////////////////////////////////////////////////////
// crtp.h - Curiously Recurring Template Pattern                   //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2006       //
/////////////////////////////////////////////////////////////////////
/*
   The Curiosly Recurring Template Pattern (Coplien, C++ Report, 1996)
   is implemented with a pair of classes, like this:

      template<class T> class base { ... };
      class derived : public base<derived> { ... };

   We use it when we want to factor some processing into a base class
   so that it does not have to be repeated in every class that derives
   from it.  However, some of the processing needs to use the name of
   the derived class.  That is the case for base step2(), below.
*/
#include <iostream>

/////////////////////////////////////////////////////////////////////
// algorithmWithSteps implements an algorithm with a series of
// steps, executed in an order enforced by this class.  Some of
// the steps may optionally be modified by a derived class, and
// some must be proved by the derived class.
//
// We use this structure so that algorithmWithSteps can define some
// complex processing that can be implemented once, then encapsulated
// from view.  But some of these steps need processing that it can't
// know how to do, supplied by a derived class, as in step3, below.
// The method step4 returns a temporary derived object, so must use
// the name of the derived class, hence CRTP.

template <typename T>
class algorithmWithSteps
{
public:
  algorithmWithSteps();
  virtual ~algorithmWithSteps() {}
  T* doAlgorithm();        // requires CRTP
private:
  virtual void step1();    // virtual so derived can override
  T* step2();              // non-virtual so don't override
  virtual void step3()=0;  // pure virtual so derived must override
};

//
template <typename T>
algorithmWithSteps<T>::algorithmWithSteps()
{
  std::cout << "\n    constructing instance of algorithmWithSteps";
}

template <typename T>
T* algorithmWithSteps<T>::doAlgorithm()
{
  std::cout << "\n  doAlgorithm() exercises three distinct steps:";

  step1();  std::cout << std::endl;
  T* pT = step2();  std::cout << std::endl;
  step3(); std::cout << std::endl;

  return pT;
}
template <typename T>
void algorithmWithSteps<T>::step1()
{ 
  std::cout << "\n  performing base step1()";
}
template <typename T>
T* algorithmWithSteps<T>::step2()
{ 
  std::cout << "\n  performing base step2() which returns a clone";
  return new T;  
  // this needs to be derived type, hence we need derived type T parameter 
}

// Note: no step3

/////////////////////////////////////////////////////////////////////
// modifiedAlgorithm uses the algorithm defined by its base, but
// modifies or supplies some of the steps.

class modifiedAlgorithm : public algorithmWithSteps<modifiedAlgorithm>
{
public:
  modifiedAlgorithm();
  void step3();
  // note: no step1() or step2()
};


inline modifiedAlgorithm::modifiedAlgorithm()
{
  std::cout << "\n    constructing instance of modifiedAlgorithm";
}
void modifiedAlgorithm::step3()
{
  std::cout << "\n  performing derived step3()";
}

#endif
