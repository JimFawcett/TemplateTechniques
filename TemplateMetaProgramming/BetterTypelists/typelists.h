#ifndef TYPELISTS_H
#define TYPELISTS_H
/////////////////////////////////////////////////////////////////////
// typelists.h  -  compile-time lists via recursion                //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

template <typename H, typename T>
struct TypeList
{
  typedef H Head;
  typedef T Tail;
};

struct NullType
{
  struct Head { private: Head(); };
  struct Tail { private: Tail(); };
};

struct EmptyType {};

/////////////////////////////////////////////////////////////////////
// TYPELIST macros

#define TYPELIST_1(T1) TypeList< T1, NullType >
#define TYPELIST_2(T1,T2) TypeList< T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1,T2,T3) TypeList< T1, TYPELIST_2(T2,T3) >
#define TYPELIST_4(T1,T2,T3,T4) TypeList< T1, TYPELIST_3(T2,T3,T4) >

/////////////////////////////////////////////////////////////////////
// make TypeList

template < class T1=NullType, 
           class T2=NullType, 
           class T3=NullType, 
           class T4=NullType >
struct MakeTypeList
{
private:
  typedef typename MakeTypeList< T2, T3, T4 >::Result TailResult;
public:
  typedef TypeList< T1, TailResult > Result;
};

template <>
struct MakeTypeList < NullType, NullType, NullType, NullType >
{
  typedef NullType Result;
};

//
/////////////////////////////////////////////////////////////////////
// Length - find length of TypeList

template < class TList > struct Length;

template <> struct Length<NullType> { enum { value = 0 }; };

// walk down the typelist until reaching NullType, e.g., the end
// Value is the number of steps to get to the end

template < class H, class T >
struct Length < TypeList< H, T > >
{
  enum { value = 1 + Length<T>::value };
};

/////////////////////////////////////////////////////////////////////
// TypeAt - find type at a given index

template < class TList, unsigned int index > struct TypeAt;

template < class Head, class Tail >
struct TypeAt < TypeList < Head, Tail >, 0 >
{
  typedef Head Result;
};

// recursively discard the list head until the ith type is the head,
// then use the specialization above to get the Result

template < class Head, class Tail, unsigned int i >
struct TypeAt < TypeList < Head, Tail >, i >
{
  typedef typename TypeAt < Tail, i-1 >::Result Result;
};

//
/////////////////////////////////////////////////////////////////////
// Search for Type

template < class TList, class T > struct IndexOf;

// use this specialization if not found after traversing
// the entire typelist, e.g., value = -1

template < class T >
struct IndexOf < NullType, T > { enum { value = -1 }; };

// index is zero if T is the Head

template < class Tail, class T >
struct IndexOf < TypeList < T, Tail >, T >
{
  enum { value = 0 };
};

// discard Head, increment index if T not new Head

template < class Head, class Tail, class T >
struct IndexOf < TypeList < Head, Tail >, T >
{
private:
  enum { temp = IndexOf < Tail, T >::value };
public:
  enum { value = temp == -1 ? -1 : 1 + temp };
};

/////////////////////////////////////////////////////////////////////
// Appending another type

template < class TList, class T > struct Append;

// appending NullType to NullType is empty typelist, e.g., NullType

template <> struct Append < NullType, NullType >
{
  typedef NullType Result;
};

// appending type T to NullType is typelist of size 1

template < class T >
struct Append < NullType, T>
{
  typedef TYPELIST_1(T) Result;
};

// appending typelist to NullType is the typelist

template < class Head, class Tail >
struct Append < NullType, TypeList < Head, Tail > >
{
  typedef TypeList < Head, Tail > Result;
};

// appending T to TypeList is typelist of Head and Tail with T appended to Tail
// this will keep walking down list until we get to NullType

template < class Head, class Tail, class T >
struct Append < TypeList < Head, Tail >, T >
{
  typedef TypeList < Head, typename Append < Tail, T >::Result > Result;
};

//
/////////////////////////////////////////////////////////////////////
// Replace type in TypeList

template < class TList, class T, class U > struct Replace;

// replacing T with U in empty typelist is empty typelist

template < class T, class U >
struct Replace < NullType, T, U >
{
  typedef NullType Result;
};

// if Head is T the replace Head with U

template < class T, class Tail, class U > 
struct Replace < TypeList < T, Tail >, T, U >
{
  typedef TypeList < U, Tail > Result;
};

// walk down typelist until Head is T

template < class Head, class Tail, class T, class U >
struct Replace < TypeList < Head, Tail >, T, U >
{
  typedef TypeList < Head, typename Replace < Tail, T, U >::Result > Result;
};

#endif
