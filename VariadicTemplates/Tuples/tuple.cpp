///////////////////////////////////////////////////////////////////////////
// Tuple: one way to implement std::tuple                                //
//                                                                       //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018             //
// Source:                                                               //
// This is a very slight modification of code developed by Eli Bendersky //
// presented on his website:                                             //
//   https://eli.thegreenplace.net/2014/variadic-templates-in-c/         //
//                                                                       //
// References:                                                           //
// std::enable_if<> http://en.cppreference.com/w/cpp/types/enable_if     //
///////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <iostream>
#include <string>
#include <typeinfo>

/////////////////////////////////////////////////////////////////////////////
// Recursive definition creates a chain of class derivations
// - the base class and each derived class contains one of the tuple's data members
// - so the most derived class contains all of the tuple's data
// - this derivation works because two templates parameterized on
//   different types are different classes

template <class... Ts> struct tuple {};  // specialization matched by empty parameter pack

template <class T, class... Ts>
struct tuple<T, Ts...> : tuple<Ts...> {
  tuple(T t, Ts... ts) : tuple<Ts...>(ts...), tail(t) {}

  T tail;
};

/////////////////////////////////////////////////////////////////////////////
// This elem_type_holder is here just to recursively find the kth type
// in the tuple's parameter pack

template <size_t, class> struct elem_type_holder;

template <class T, class... Ts>
struct elem_type_holder<0, tuple<T, Ts...>> {
  using type = T;
};

template <size_t k, class T, class... Ts>
struct elem_type_holder<k, tuple<T, Ts...>> {
  using type = typename elem_type_holder<k - 1, tuple<Ts...>>::type;
};

/////////////////////////////////////////////////////////////////////////////
// get is a template function that has a type element if, and only if,
// the std::enable_if predicate evaluates to true
// https://en.cppreference.com/w/cpp/types/enable_if

template <size_t k, class... Ts>
typename std::enable_if<
  k == 0, typename elem_type_holder<0, tuple<Ts...>>::type&>::type
  get(tuple<Ts...>& t) {
  return t.tail;
}

template <size_t k, class T, class... Ts>
typename std::enable_if<
  k != 0, typename elem_type_holder<k, tuple<T, Ts...>>::type&>::type
  get(tuple<T, Ts...>& t) {
  tuple<Ts...>& base = t;
  return get<k - 1>(base);
}

int main(int argc, char** argv) {

  std::cout << "\n  Demonstrating Tuple Design";
  std::cout << "\n ============================\n";

  std::cout << "\n  after declaring tuple<double, uint64_t, const char*> t1(12.2, 42, \"big\");\n";

  tuple<double, uint64_t, const char*> t1(12.2, 42, "big");
  std::cout << "\n  0th elem is " << get<0>(t1);
  std::cout << "\n  1th elem is " << get<1>(t1);
  std::cout << "\n  2th elem is " << get<2>(t1);

  get<1>(t1) = 103;

  std::cout << "\n  after executing get<1>(t1) = 103:";
  std::cout << "\n  1th elem is " << get<1>(t1) << "\n";

  std::cout << "\n  testing elem_type_holder:";
  std::cout << "\n ---------------------------";

  typename elem_type_holder<0, tuple<double, int, const char*>>::type foo0;
  std::cout << "\n  " << typeid(foo0).name();
  typename elem_type_holder<1, tuple<double, int, const char*>>::type foo1;
  std::cout << "\n  " << typeid(foo1).name();
  typename elem_type_holder<2, tuple<double, int, const char*>>::type foo2;
  std::cout << "\n  " << typeid(foo2).name();
  std::cout << "\n\n";
  return 0;
}
