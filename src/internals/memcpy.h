#pragma once

#include "btypes.h"

namespace __fcl
{

template<class _Ty>
constexpr _Ty* generic_memcpy(_Ty* to, const _Ty* from, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        to[i] = from[i];
    }

    return to;
}

template<class _Ty>
constexpr _Ty* generic_memset(_Ty* to, _Ty value, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        to[i] = value;
    }
    return to;
}

}

