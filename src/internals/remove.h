#pragma once

#include "btypes.h"
#include "algorithmbase.h"
#include "move.h"


namespace __fcl
{

template<class _Fwd, class _Pred>
constexpr _Fwd remove_if(_Fwd __begin, _Fwd __end, _Pred __predicate)
{
    bool __yet = false;
    __begin = __fcl::find_if(__begin, __end, __predicate);
    if (__begin == __end)
        return __begin;

    _Fwd __result = __begin;
    __result++;

    while (__begin != __end)
    {
        if (__predicate(*__begin))
            __yet = true;
        if (__yet)
            (*__begin) = __fcl::move(*__result);

        __begin++; __result++;
    }

    return __begin;
}

template<class _Fwd, class _Ty>
constexpr _Fwd remove(_Fwd __begin, _Fwd __end, const _Ty& __value)
{
    return remove_if(__begin, __end, __fcl::equals_with(__value));
}

}

