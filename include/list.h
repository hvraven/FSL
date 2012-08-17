#ifndef FSL_LIST_H
#define FSL_LIST_H

#include <algorithm>
#include <memory>

namespace FSL
{
  template <class InT,
            template <class U, class All = std::allocator<U> > class InC,
            template <class V, class All = std::allocator<V> > class OutC = InC,
            class OutT = InT>
  OutC<OutT>
  map(std::function<OutT(InT)> fun, const InC<InT>& in)
  {
    OutC<OutT> out;
    out.resize(in.size());
    std::transform(begin(in), end(in), begin(out), fun);
    return out;
  }

}

#endif /* FSL_LIST_H */
