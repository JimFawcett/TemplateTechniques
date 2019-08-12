/////////////////////////////////////////////////////////////////////////
// FunctorsEtc.cpp - Demonstrate Functors and Function Pointers with   //
//                   template arguments                                //
//                                                                     //
// Jim Fawcett, CSE67 - Object Oriented Design, Spring 2009            //
/////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <string>

// Functor interface, to support substitutability

template <typename C>
struct IFunctor
{
  virtual void operator()(typename C::iterator& iter)=0;
};

// Global function that accepts iterators and base functor reference,
// templatized on a container argument.

template <typename C>
void Traverse(typename C::iterator& Begin, typename C::iterator& End, IFunctor<C>& funct)
{
  C::iterator iter;
  for(iter=Begin; iter!=End; ++iter)
    funct(iter);
}

// Global function that accepts iterators and function pointer to member
// templatized on a container argument

template <class C, template <class C> class X>
void Traverse(
  typename C::iterator& Begin, 
  typename C::iterator& End, 
  X<C>& x, 
  void(X<C>::*fptr)(typename C::iterator&)
)
{
  C::iterator iter;
  for(iter=Begin; iter!=End; ++iter)
  {
    (x.*fptr)(iter);
  }
}

//----< Demonstrate >----------------------------------------------------

#include <string>
#include <iostream>

// one of many possible operations to apply to some container

class aFunctor : public IFunctor<std::string>
{
  void operator()(std::string::iterator& iter)
  {
    std::cout << *iter << " ";
  }
};

// template class that has a member function we will point to

template <typename C>
class X
{
public:
  void doOp(typename C::iterator& iter)
  {
    std::cout << *iter << " ";
  }
};

// alias for this convoluted template function pointer to member syntax

typedef void (X<std::string>::*fptr)(std::string::iterator&);

void main()
{
  std::string test = "CSE687 - Object Oriented Design";
  
  // testing functor
  aFunctor func;
  std::cout << "\n  ";
  Traverse(test.begin(), test.end(), func);
  
  // testing function pointer to member

  std::cout << "\n  ";
  X<std::string> x;
  fptr f = &X<std::string>::doOp;
  Traverse<std::string>(test.begin(), test.end(), x, f); 

  // this syntax works too
  
  std::cout << "\n  ";
  Traverse<std::string>(test.begin(), test.end(), x, &X<std::string>::doOp); 

  std::cout << "\n\n";
}