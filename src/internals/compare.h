#pragma once

#include "btypes.h"
#include "move.h"

_FCL_NAMESPACE_BEGIN

template<class _Ty = void>
struct equal_to
{
    constexpr bool operator()(const _Ty& _x, const _Ty& _y) const
    {
        return _x == _y;
    }
};

template<>
struct equal_to<void>
{
    template<class _Ty, class _Zy>
    constexpr bool operator()(const _Ty& _x, const _Zy& _y) const
    {
        return __fcl::forward(_x) == __fcl::forward(_y);
    }
};

template<class _Ty = void>
struct not_equal_to
{
    constexpr bool operator()(_Ty&& _x, _Ty&& _y) const
    {
        return _x != _y;
    }
};

template<>
struct not_equal_to<void>
{
    template<class _Ty, class _Zy>
    constexpr bool operator()(_Ty&& _x, _Zy&& _y) const
    {
        return __fcl::forward(_x) != __fcl::forward(_y);
    }
};

template<class _Ty = void>
struct greater
{
    constexpr bool operator()(_Ty&& _x, _Ty&& _y) const
    {
        return _x > _y;
    }
};

template<>
struct greater<void>
{
    template<class _Ty, class _Zy>
    constexpr bool operator()(_Ty&& _x, _Zy&& _y) const
    {
        return __fcl::forward(_x) > __fcl::forward(_y);
    }
};

template<class _Ty = void>
struct less
{
    constexpr bool operator()(const _Ty& _x, const _Ty& _y) const
    {
        return _x < _y;
    }
};

template<>
struct less<void>
{
    template<class _Ty, class _Zy>
    constexpr bool operator()(_Ty&& _x, _Zy&& _y) const
    {
        return __fcl::forward(_x) < __fcl::forward(_y);
    }
};

template<class _Ty = void>
struct greater_equal
{
    constexpr bool operator()(_Ty&& _x, _Ty&& _y) const
    {
        return _x >= _y;
    }
};

template<>
struct greater_equal<void>
{
    template<class _Ty, class _Zy>
    constexpr bool operator()(_Ty&& _x, _Zy&& _y) const
    {
        return __fcl::forward(_x) >= __fcl::forward(_y);
    }
};

template<class _Ty = void>
struct less_equal
{
    constexpr bool operator()(_Ty&& _x, _Ty&& _y) const
    {
        return _x <= _y;
    }
};

template<>
struct less_equal<void>
{
    template<class _Ty, class _Zy>
    constexpr bool operator()(_Ty&& _x, _Zy&& _y) const
    {
        return __fcl::forward(_x) <= __fcl::forward(_y);
    }
};

_FCL_NAMESPACE_END

