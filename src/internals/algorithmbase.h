#pragma once

#include "btypes.h"

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

template<class _Fitery, class _Predy>
constexpr _Fitery __removeif(_Fitery _begin, _Fitery _end, _Predy _predicate)
{
    auto __iter = find_if(_begin, _end, _predicate);
    if (__iter == _end)
    {
        return _begin;
    }
    
    _Fitery __result = _begin;
    ++_begin;
    for (; _begin != _end; ++_begin)
    {
        if (!_predicate(*_begin))
        {
            *(__result) = move(*_begin);
            __result++;
        }
    }

    return __result;
}

}
