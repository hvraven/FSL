#ifndef FSL_FOLD_H
#define FSL_FOLD_H

#include "list.h"

#include <functional>
#include <memory>

namespace FSL
{

  template <class A, class B,
            template <class T, class All = std::allocator<T> > class V>
  A
  foldl(const std::function<A(A, B)>& fun, const A& a, const V<B>& list)
  {
    A result = a;
    for (const auto& e : list)
      result = fun(result, e);
    return result;
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
