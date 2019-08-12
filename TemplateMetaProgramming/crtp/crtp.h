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
   the derived class.

   The code below follows closely an example discussed by Rainer Grimm
   here: http://www.modernescpp.com/index.php/c-is-still-lazy.

   My expansion of his code provides the logical operators:
     ==, !=, and >
   for any class Derived : public Compare<Derived> that implements
   operator<.
*/


template <typename Derived>
class Compare {};

// uses Derived::operator< to define global operator==

template <typename Derived>
bool operator==(Compare<Derived> const& leftOp, Compare<Derived> const& rightOp)
{
  Derived const& dLft = static_cast<Derived const&>(leftOp);   // cast to base when called
  Derived const& dRgt = static_cast<Derived const&>(rightOp);  // cast to base when called
  return !(dLft < dRgt) && !(dRgt < dLft);
}

// uses Derived::operator< to define, indirectly, global operator!=

template <typename Derived>
bool operator!=(Compare<Derived> const& leftOp, Compare<Derived> const& rightOp)
{
  Derived const& dLft = static_cast<Derived const&>(leftOp);
  Derived const& dRgt = static_cast<Derived const&>(rightOp);
  return !(dLft == dRgt);
}

// uses Derived::operator< to define global operator>

template <typename Derived>
bool operator>(Compare<Derived> const& leftOp, Compare<Derived> const& rightOp)
{
  Derived const& dLft = static_cast<Derived const&>(leftOp);
  Derived const& dRgt = static_cast<Derived const&>(rightOp);
  return !(dLft < dRgt);
}
#endif
