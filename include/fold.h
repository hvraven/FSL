#ifndef FSL_LIST_H
#define FSL_LIST_H

#include <functional>
#include <memory>

namespace FSL
{

  template <class F, class A, class B,
           template <class T, class All = std::allocator<T> > class V>
  A
  foldl(F fun, const A& a, const V<B>& list)
  {
    A result = a;
    for (auto it = begin(list); it != end(list); ++it)
      result = fun(result, *it);
    return result;
  }

  template <template <class T, class All = std::allocator<T> > class V, class B>
  bool
  fand(V<B> list)
  {
    return foldl(std::logical_and<B>(), true, list);
  }
  
}

#endif /* FSL_LIST_H */
