#pragma once

#include <stdint.h>

namespace __fcl
{

template<class _Ty>
constexpr int generic_strncmp(const _Ty* t1, const  _Ty* t2, int length)
{
    for (int i = 0; i < length; i++)
    {
        _Ty c1 = t1[i];
        _Ty c2 = t2[i];

        if (c1 > c2)
        {
            return 1;
        }
        else if (c2 > c1)
        {
            return -1;
        }
    }

    return 0;
}

}
