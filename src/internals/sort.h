#pragma once

#include "btypes.h"
#include "iterator.h"

namespace __fcl
{

template<class _Begy, class _Cmpy>
constexpr void perform_selectionsort(_Begy _begin, _Begy _end, _Cmpy _compare)
{
    using __valt = typename __fcl::iterator_traits<_Begy>::value_type;
    __valt __minimum;

    while (true)
    {
        if (_compare(*_begin, __minimum))
        {
            __minimum = *_begin;
        }
    }
}

}
