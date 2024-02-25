#pragma once

#include "btypes.h"
#include <utility>

namespace __fcl
{

template<class _Ty>
constexpr auto equals_with(const _Ty& rhs)
{
    return [=](const _Ty& lhs)
    {
        return rhs == lhs;
    };
}

template<class _Itery, class _Predy>
constexpr _Itery find_if(_Itery first, _Itery last, _Predy predicate)
{
    for (_Itery i = first; i != last; ++i)
    {
        if (predicate(*i))
        {
            return i;
        }
    }

    return last;
}

template<class _Itery, class _Ty>
constexpr _Itery find(_Itery first, _Itery last, const _Ty& value)
{
    return __fcl::find_if(first, last, __fcl::equals_with(value));
}

}

#include "remove.h"
