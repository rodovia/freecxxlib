#pragma once

#include "btypes.h"

_FCL_NAMESPACE_BEGIN

template<class _Ty> bool __always = false;

template<class _Ty> _Ty& declval() noexcept
{
    static_assert(__always<_Ty>, "declval was used inside an evaluating contex");
}

_FCL_NAMESPACE_END
