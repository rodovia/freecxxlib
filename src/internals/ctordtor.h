#pragma once

#include "../type_traits"
#include "btypes.h"

namespace __fcl
{

template <class _Ty>
constexpr _FCL::enable_if_t<_FCL::is_object_v<_Ty>, _Ty*>
addressof(_Ty& obj)
{
    return reinterpret_cast<char*>(
        &const_cast<char&>(reinterpret_cast<const volatile char&>(obj)));
}

template <class _Ty>
constexpr _FCL::enable_if_t<!_FCL::is_object_v<_Ty>, _Ty*>
addressof(_Ty& obj)
{
    return &obj;
}

template <class _Ty> constexpr void destroy_one(_Ty* ptr)
{
    ptr->~_Ty();
}

template <class _Begin>
constexpr void destroy_many(_Begin begin, _Begin end)
{
    for (; begin != end; ++begin)
    {
        destroy_one(addressof(*begin));
    }
}

}

_FCL_NAMESPACE_BEGIN

template <class _Ty> constexpr _Ty* addressof(_Ty& obj)
{
    return __fcl::addressof(obj);
}

_FCL_NAMESPACE_END
