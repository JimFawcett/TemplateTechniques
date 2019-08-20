#pragma once
#include <type_traits>

template <class... Ts> struct tuple {};

template <class T, class... Ts>
struct tuple<T, Ts...> : tuple<Ts...> {
  tuple(T t, Ts... ts) : tuple<Ts...>(ts...), tail(t) {}

  T tail;
};

//template <typename T, class... Ts>
//struct elem_type_holder/*<0, tuple<T, Ts...>>*/ {
//  typedef T type;
//};
//
//template <size_t k, class T, class... Ts>
//struct elem_type_holder<k, tuple<T, Ts...>> {
//  typedef typename elem_type_holder<k - 1, tuple<Ts...>>::type type;
//};
//
//template <size_t k, class... Ts>
//typename std::enable_if<
//  k == 0, typename elem_type_holder<0, tuple<Ts...>>::type&>::type
//  get(tuple<Ts...>& t) {
//  return t.tail;
//}
//
//template <size_t k, class T, class... Ts>
//typename std::enable_if<
//  k != 0, typename elem_type_holder<k, tuple<T, Ts...>>::type&>::type
//  get(tuple<T, Ts...>& t) {
//  tuple<Ts...>& base = t;
//  return get<k - 1>(base);
//}
