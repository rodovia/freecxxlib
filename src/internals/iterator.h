#pragma once

#include "btypes.h"
#include "../type_traits"
#include <stddef.h>

#define __fclmax(X, y) ((X > y) ? X : y)
#define __fclmin(X, y) ((X > y) ? y : X) 


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
    using iterator_category = _FCL::input_iterator_tag;
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
    using iterator_category = _FCL::forward_iterator_tag;
    using value_type = remove_const_t<_Ty>;
    using difference_type = ptrdiff_t;
    using pointer = _Ty*;
    using reference = _Ty&;

    fwd_iterator(value_type* counter)
        : _m_Pointer(counter)
    { }

    fwd_iterator(const value_type* counter)
        : _m_Pointer(const_cast<value_type*>(counter))
    { }

    constexpr fwd_iterator operator++() noexcept
    {
        _m_Pointer++;
        return _m_Pointer;
    }

    constexpr pointer operator++(int) noexcept
    {
        _m_Pointer++;
        return _m_Pointer;
    }

    constexpr _Ty& operator*() noexcept
    {
        return *_m_Pointer;
    }

    constexpr _Ty& operator->() noexcept
    {
        return *_m_Pointer;
    }

    constexpr bool operator==(const fwd_iterator& it) noexcept
    {
        return _m_Pointer == it._m_Pointer;
    }

    constexpr bool operator==(fwd_iterator&& it) noexcept
    {
        return _m_Pointer == it._m_Pointer;
    }

    constexpr bool operator!=(const fwd_iterator& it) noexcept
    {
        return !operator==(it);
    }

    constexpr bool operator!=(fwd_iterator&& it) noexcept
    {
        return !operator==(it);
    }

    constexpr difference_type operator-(difference_type rhs)
    {
        return _m_Pointer - rhs;
    }

    constexpr difference_type operator-(fwd_iterator<_Ty>& rhs)
    {
        return __fclmin(_m_Pointer, rhs._m_Pointer) 
                ? rhs._m_Pointer - _m_Pointer 
                : _m_Pointer - rhs._m_Pointer;
    }

    constexpr pointer operator+(size_t offset)
    {
        return _m_Pointer + offset;
    }

protected:
    pointer _m_Pointer;
};

template<class _Ty>
struct bidi_iterator : public fwd_iterator<_Ty>
{
    using iterator_category = _FCL::bidirectional_iterator_tag;
    using fwd_iterator<_Ty>::fwd_iterator;

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
    using bidi_iterator<_Ty>::bidi_iterator;
    using iterator_category = _FCL::random_access_iterator_tag;
    using typename fwd_iterator<_Ty>::value_type;
    using typename fwd_iterator<_Ty>::reference;
    using typename fwd_iterator<_Ty>::difference_type;

    constexpr reference operator+=(difference_type rhs) noexcept
    {
        const_cast<_Ty*>(_m_Pointer) += rhs;
        return *_m_Pointer;
    };

    constexpr reference operator+(difference_type rhs) noexcept
    {
        return *(_m_Pointer + rhs);
    }

    constexpr reference operator[](difference_type offset)
    {
        return *(this + offset);
    }
private:
    using fwd_iterator<_Ty>::_m_Pointer;
};

template<class _Ty, class _Iter>
struct output_iterator : public _Iter
{
    using iterator_category = _FCL::output_iterator_tag;

    constexpr typename iterator_traits<_Iter>::reference operator*() noexcept
    {
        return *const_cast<_Ty*>(_Iter::_m_Pointer);
    }

    constexpr typename iterator_traits<_Iter>::reference operator->() noexcept
    {
        return *const_cast<_Ty*>(_Iter::_m_Pointer);
    }
protected:
    using typename _Iter::_m_Pointer;
};

template<class _Ty>
struct fwd_iterator_const
{
    using iterator_category = _FCL::forward_iterator_tag;
    using value_type = const _Ty;
    using difference_type = ptrdiff_t;
    using pointer = _Ty*;
    using reference = const _Ty&;

    fwd_iterator_const(pointer counter)
        : _m_Pointer(counter)
    { }

    reference operator++() noexcept
    {
        _m_Pointer++;
        return *_m_Pointer;
    }

    reference operator--() noexcept
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

    constexpr bool operator==(const fwd_iterator_const& it) noexcept
    {
        return _m_Pointer == it._m_Pointer;
    }

    constexpr bool operator!=(fwd_iterator_const& it) noexcept
    {
        return !operator==(it);
    }

    constexpr pointer operator+(size_t offset) const noexcept
    {
        return _m_Pointer + offset;
    }
private:
    pointer _m_Pointer;
};

}

_FCL_NAMESPACE_BEGIN

using ::__fcl::iterator_traits;

template<class _Inpy> 
constexpr typename iterator_traits<_Inpy>::difference_type
distance(_Inpy begin, _Inpy end)
{
    using _Try = iterator_traits<_Inpy>;
    if constexpr (_FCL::is_same<typename _Try::iterator_category, 
                                random_access_iterator_tag>())
    {
        return (end - begin);
    }

    typename _Try::difference_type __di = 0;
    while (begin != end)
    {
        ++__di; ++begin;
    }

    return __di;
}

_FCL_NAMESPACE_END
