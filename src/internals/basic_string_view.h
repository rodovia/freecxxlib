#pragma once

#include "btypes.h"
#include "string.h"
#include "iterator.h"
#include "../algorithm"
#include <cstddef>
#include "../memory"
#include "../utility"

_FCL_NAMESPACE_BEGIN

template<class _Ty>
struct char_traits
{
    static_assert(true, "No traits for non-char type");
};

template<>
struct char_traits<char>
{
    using char_type = char;
    using int_type = int;
    /* off_type, pos_type, state_type and comparison_category are purposefully omitted */

    static constexpr void assign(char_type& c1, const char_type& c2) noexcept
    {
        c1 = c2;
    }

    static constexpr bool eq(char_type c1, char_type c2) noexcept
    {
        return c1 == c2;
    }

    static constexpr bool lt(char_type c1, char_type c2) noexcept
    {
        return c1 < c2;
    }

    static constexpr int compare(const char_type* s1, const char_type* s2, size_t n)
    {
        for (size_t i = 0; i < n; i++)
        {
            char_type c = s1[i];
            char_type c2 = s2[i];
            if (lt(c, c2))
            {
                return -1;
            }

            if (lt(c2, c))
            {
                return 1;
            }
        }

        return 0;
    }

    static constexpr size_t length(const char_type* string)
    {
        /* TODO: someday remove this const cast */
        char_type* b = const_cast<char_type*>(string);
        while(*b != 0) ++b;
        return b - string;
    }

    static constexpr const char_type* find(const char_type* s, size_t n,
                                           const char_type& a)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (s[i] == a)
            {
                return &s[i];
            }
        }

        return nullptr;
    }

    static constexpr char_type* move(char_type* s1, const char_type* s2, size_t n)
    {
        /* s1 comes first than s2: copy in reverse */
        if (s2 > s1 && s1 + n >= s2)
        {
            for (size_t c = n; c != 0; c--)
            {
                s1[c] = s2[c];
            }

            return s1;
        }

        for (size_t c = 0; c < n; c++)
        {
            s1[c] = s2[c];
        }

        return s1;
    }

    static constexpr char_type* copy(char_type* s1, const char_type* s2, size_t n)
    {
        for (size_t c = 0; c < n; c++)
        {
            s1[c] = s2[c];
        }

        return s1;
    }

    static constexpr char_type* assign(char_type* s, size_t n, char_type a)
    {
        for (size_t i = 0; i < n; i++)
        {
            s[i] = a;
        }

        return s;
    }

    /* not_eof, to_char_type, to_int_type, eq_int_type and eof where purposefully omitted */
};

template<class _Cy, class _Try = char_traits<_Cy>>
class basic_string_view
{
public:
    using traits_type = _Try;
    using value_type = _Cy;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using const_iterator = __fcl::bidi_iterator<value_type>;
    using iterator = const_iterator;
    /* const_reverse_iterator and reverse_iterator were omitted. */
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    static constexpr size_type npos = size_type(-1);

    constexpr basic_string_view() noexcept
        : _m_Buffer(nullptr),
        _m_Length(0)
    {
    }

    constexpr basic_string_view(const _Cy* string)
        : _m_Buffer(string),
        _m_Length(traits_type::length(string))
    {
    }

    

    constexpr basic_string_view(const_pointer string, size_type length)
        : _m_Buffer(string),
        _m_Length(length)
    {
    }

    /* basic_string_view iterator and ranges ctor was omitted. */

    constexpr basic_string_view(const basic_string_view&) noexcept = default;
    constexpr basic_string_view& operator=(const basic_string_view&) noexcept = default;

    constexpr const_iterator begin() noexcept
    {
        return const_iterator(_m_Buffer);
    }

    constexpr const_iterator cbegin() const noexcept
    {
        return const_iterator(_m_Buffer);
    }

    constexpr const_iterator end() noexcept
    {
        return const_iterator(_m_Buffer + _m_Length);
    }

    constexpr const_iterator cend() const noexcept
    {
        return const_iterator(_m_Buffer + _m_Length);
    }

    /* The reverse variant of the above functions were omitted. */

    constexpr size_type size() const noexcept
    {
        return _m_Length;
    }

    constexpr size_type length() const noexcept
    {
        return _m_Length;
    }

    constexpr const_reference operator[](size_type pos) const
    {
        return _m_Buffer[pos];
    }

    constexpr const_reference at(size_type pos) const
    {
        return _m_Buffer[pos];
    }

    constexpr const_reference front() const
    {
        return operator[](0);
    }

    constexpr const_reference back() const
    {
        return _m_Buffer[_m_Length - 1];
    }

    constexpr const_pointer data() const noexcept
    {
        return _m_Buffer;
    }

    constexpr void remove_prefix(size_type size)
    {
        _m_Buffer += size; _m_Length -= size;
    }

    constexpr void remove_suffix(size_type size)
    {
        _m_Length -= size;
    }

    constexpr void swap(basic_string_view& rhs) noexcept
    {
        _FCL::swap(*this, rhs);
    }

    constexpr size_type copy(pointer string, size_type size, size_type pos = 0) const
    {
        size_type rlen = min(size, _m_Length - pos);
        traits_type::copy(string, _m_Buffer + pos, rlen);
        return rlen;
    }

    constexpr int compare(basic_string_view string) const noexcept
    {
        size_type rlen = min(_m_Length, string._m_Length);
        int result = traits_type::compare(_m_Buffer, string._m_Buffer, rlen);

        if (result != 0)
        {
            return result;
        }

        if (_m_Length < string._m_Length)
            return -1;
        else if (_m_Length == string._m_Length)
            return 0;
        else if (_m_Length > string._m_Length)
            return 1;
        return 0;
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return _m_Length != 0;
    }

private:
    const _Cy* _m_Buffer;
    size_type _m_Length;
};

using string_view = basic_string_view<char>;

_FCL_NAMESPACE_END
