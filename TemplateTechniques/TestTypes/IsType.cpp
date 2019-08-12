/////////////////////////////////////////////////////////////////
//  IsType.h - some metafunctions to test for specific types   //
//                                                             //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 05    //
/////////////////////////////////////////////////////////////////
//
// This example illustrates a MetaProgramming that
// manipulates types, not values.

//----< IsChar >---------------------------------

template <typename T>
struct IsChar { enum { value=false }; };
template <>
struct IsChar<char> { enum { value=true }; };

//----< IsArray >--------------------------------

template <typename T>
struct IsArray { enum { value=false }; };
template <typename A, int N>
struct IsArray<A [N]> { enum { value=true }; };

//----< IsPointer >------------------------------

template <typename T>
struct IsPointer { enum { value=false }; };
template <typename T>
struct IsPointer<T*> { enum { value=true }; };
template <typename T>
struct IsPointer<T*const> { enum { value=true }; };
template <typename T>
struct IsPointer<T*volatile> { enum { value=true }; };
template <typename T>
struct IsPointer<T*const volatile> { enum { value=true }; };

//----< IsPointer to member >--------------------

template <class U> struct IsPointerToMember
{
  enum { value=false };
};
template <class U, class V> struct IsPointerToMember<U V::*>
{
  enum { value=true };    // member data
};
template <class U, class V, class W> struct IsPointerToMember<U(V::*)(W)>
{
  enum { value=true };    // member function
};

//
//----< demonstrations >-------------------------

#ifdef TEST_ISTYPE

#include <iostream>

class Y {};

class X 
{
public:
  void fun() {}
  int i;
};

void main()
{
  if(IsChar<int>::value)
    std::cout << "\n  int is a char";
  else
    std::cout << "\n  int is not a char";

  typedef char charType;

  if(IsChar<charType>::value)
    std::cout << "\n  charType is a char";
  else
    std::cout << "\n  charType is not a char";

  if(IsArray<X[3]>::value)
    std::cout << "\n  X[3] is an array";
  else
    std::cout << "\n  X[3] is not an array";

  if(IsArray<X*>::value)
    std::cout << "\n  X* is an array";
  else
    std::cout << "\n  X* is not an array";

  if(IsPointer<X>::value)
    std::cout << "\n  X is a pointer";
  else
    std::cout << "\n  X is not a pointer";

  if(IsPointer<X*>::value)
    std::cout << "\n  X* is a pointer";
  else
    std::cout << "\n  X* is not a pointer";

  if(IsPointer<const X*>::value)
    std::cout << "\n  const X* is a pointer";
  else
    std::cout << "\n  const X* is not a pointer";

  if(IsPointer<volatile X*>::value)
    std::cout << "\n  volatile X* is a pointer";
  else
    std::cout << "\n  volatile X* is not a pointer";

    //
  // demonstrate use of pointer to members

  int X::*pXi = &X::i;              // declare pointer to member data
  void (X::*pMf)(void) = &X::fun;   // declare pointer to member function
  X x;
  x.*pXi = 3;                       // dereference member data pointer
  (x.*pMf)();                       // invoke member function pointer

  if(IsPointerToMember<X*>::value)  // false
    std::cout << "\n  X* is a pointer to member";
  else
    std::cout << "\n  X* is not a pointer to member";

  if(IsPointerToMember<Y X::*>::value)  // true
    std::cout << "\n  Y X::* is a pointer to member";
  else
    std::cout << "\n  Y X::* is not a pointer to member";

  if(IsPointerToMember<X& (X::*)(const X&)>::value)  // true
    std::cout << "\n  X& (X::*)(const X&) is a pointer to member";
  else
    std::cout << "\n  X& (X::*)(const X&) is not a pointer to member";

  std::cout << "\n\n";
}

#endif
