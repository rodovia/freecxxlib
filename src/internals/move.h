#pragma once

#include "../type_traits"
#include "btypes.h"

namespace __fcl 
{

template<class _Ty>
constexpr _Ty&& forward(_FCL::remove_reference<_Ty>& _t) noexcept
{
    return static_cast<_Ty&&>(_t);
}

template<class _Ty, class _Zy>
[[nodiscard]] constexpr auto forward_like(_Zy&& _z) noexcept
{
     using __copy_const = _FCL::conditional_t<_FCL::is_const_v<_FCL::remove_reference_t<_Ty>>, 
                                             const _FCL::remove_reference<_Zy>, 
                                             _FCL::remove_reference<_Zy>>;
    using __no_ref = _FCL::conditional_t<_FCL::is_rvalue_reference_v<_Ty&&>, 
                                            _FCL::remove_reference<__copy_const>&&, 
                                            __copy_const&>;
    return static_cast<__no_ref>(_z);
}

template<class _Ty> 
constexpr _FCL::remove_reference_t<_Ty>&& move(_Ty&& _t) noexcept
{
    return static_cast<_FCL::remove_reference_t<_Ty>&&>(_t);
}

}

_FCL_NAMESPACE_BEGIN

template<class _Ty> 
constexpr _FCL::remove_reference_t<_Ty>&& move(_Ty&& _t) noexcept
{
    return __fcl::move(_t);
}
_FCL_NAMESPACE_END
