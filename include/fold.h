#ifndef FSL_FOLD_H
#define FSL_FOLD_H

#include "list.h"

#include <functional>
#include <memory>

namespace FSL
{

  template <class In, class Out, class It>
  constexpr Out
  foldl(const std::function<Out(Out, In)>& fun, const In& a, It begin, It end)
  {
    return (begin == end ? a : foldl(fun, fun(a, *begin), ++begin, end));
  }

  template <class A, class B,
            template <class T, class All = std::allocator<T> > class V>
  constexpr A
  foldl(const std::function<A(A, B)>& fun, const A& a, const V<B>& list)
  {
    return foldl(fun, a, begin(list), end(list));
  }

  template <template <class T, class All = std::allocator<T> > class V, class B>
  constexpr bool
  andf(V<B> list, B start = true)
  {
    return foldl(std::function<bool(bool, bool)>(std::logical_and<B>()), true, list);
  }

  template <template <class T, class All = std::allocator<T> > class V, class B>
  constexpr bool
  orf(V<B> list, B start = false)
  {
    return foldl(std::function<bool(bool, bool)>(std::logical_or<B>()), start, list);
  }

  template <class A,
            template <class T, class All = std::allocator<T> > class V>
  constexpr bool
  any(std::function<bool(A)> fun, V<A> list)
  {
    return orf(map(fun, list));
  }

}

#endif /* FSL_FOLD_H */
