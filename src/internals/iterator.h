#pragma once

#include "btypes.h"
#include <stddef.h>

_FCL_NAMESPACE_BEGIN

struct input_iterator_tag 
{ };

struct output_iterator_tag 
{ };

struct forward_iterator_tag: public input_iterator_tag 
{ };

struct bidirectional_iterator_tag: public forward_iterator_tag 
{ };

struct random_access_iterator_tag: public bidirectional_iterator_tag 
{ };

struct contiguous_iterator_tag: public random_access_iterator_tag 
{ }; 

_FCL_NAMESPACE_END

namespace __fcl
{

template<class _Iy>
struct iterator_traits
{
    using iterator_category = typename _Iy::iterator_category;
    using value_type        = typename _Iy::value_type;
    using difference_type   = typename _Iy::difference_type;
    using pointer           = typename _Iy::pointer;
    using reference         = typename _Iy::reference;
};

template<class _Ty>
struct input_iterator
{
    using iterator_category = std::input_iterator_tag;
    using value_type = _Ty;
    using difference_type = ptrdiff_t;
    using pointer = _Ty*;
    using reference = _Ty&;

    input_iterator(pointer counter)
        : _m_Pointer(counter)
    { }

    input_iterator(input_iterator&&) = delete;
    input_iterator(const input_iterator&) = delete; 

    reference operator++() noexcept
    {
        return ++_m_Pointer;
    }

    reference operator*() noexcept
    {
        return *_m_Pointer;
    }

    reference operator->() noexcept
    {
        return *_m_Pointer;
    }

private:
    pointer _m_Pointer;
};

template<class _Ty>
struct fwd_iterator
{
    using iterator_category = std::forward_iterator_tag;
    using value_type = _Ty;
    using difference_type = ptrdiff_t;
    using pointer = _Ty*;
    using reference = _Ty&;

    fwd_iterator(pointer counter)
        : _m_Pointer(counter)
    { }

    reference operator++() noexcept
    {
        _m_Pointer++;
        return *_m_Pointer;
    }

    reference operator*() noexcept
    {
        return *_m_Pointer;
    }

    reference operator->() noexcept
    {
        return *_m_Pointer;
    }

    constexpr bool operator==(fwd_iterator& it) noexcept
    {
        return _m_Pointer == it._m_Pointer;
    }

    constexpr bool operator!=(fwd_iterator& it) noexcept
    {
        return !operator==(it);
    }

protected:
    pointer _m_Pointer;
};

template<class _Ty>
struct bidi_iterator : public fwd_iterator<_Ty>
{
    using iterator_category = _FCL::bidirectional_iterator_tag;

    constexpr typename fwd_iterator<_Ty>::reference operator--() noexcept
    {
        _m_Pointer--;
        return *_m_Pointer;
    }

private:
    using fwd_iterator<_Ty>::_m_Pointer;
};

template<class _Ty>
struct random_access_iterator : public bidi_iterator<_Ty>
{
    using iterator_category = _FCL::random_access_iterator_tag;
    using typename fwd_iterator<_Ty>::value_type;
    using typename fwd_iterator<_Ty>::reference;
    using typename fwd_iterator<_Ty>::difference_type;

    constexpr reference operator+=(difference_type rhs) noexcept
    {
        _m_Pointer += rhs;
        return *_m_Pointer;
    };

    constexpr value_type operator+(difference_type rhs) noexcept
    {
        return this += rhs;
    }

    constexpr reference operator[](difference_type offset)
    {
        return *(this + offset);
    }
private:
    using fwd_iterator<_Ty>::_m_Pointer;
};

template<class _Ty>
struct fwd_iterator_const
{
    using iterator_category = std::forward_iterator_tag;
    using value_type = const _Ty;
    using difference_type = ptrdiff_t;
    using pointer = _Ty*;
    using reference = const _Ty&;

    fwd_iterator_const(pointer counter)
        : _m_Pointer(counter)
    { }

    fwd_iterator_const(fwd_iterator_const&&) = delete;
    fwd_iterator_const(const fwd_iterator_const&) = delete; 

    reference operator++() const noexcept
    {
        _m_Pointer++;
        return *_m_Pointer;
    }

    reference operator--() const noexcept
    {
        _m_Pointer--;
        return *_m_Pointer;
    }

    reference operator*() const noexcept
    {
        return *_m_Pointer;
    }

    reference operator->() const noexcept
    {
        return *_m_Pointer;
    }

    constexpr bool operator==(fwd_iterator_const& it) noexcept
    {
        return _m_Pointer == it._m_Pointer;
    }

    constexpr bool operator!=(fwd_iterator_const& it) noexcept
    {
        return !operator==(it);
    }

private:
    pointer _m_Pointer;
};

}