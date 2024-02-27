/* list.h
   Purpose: the implementation of std::list. */
#pragma once

#include "../btypes.h"
#include "../ctordtor.h"
#include "../../memory"
#include "../iterator.h"
#include <cstdio>

namespace __fcl
{

template<class _Ty>
struct __list_data
{
    __list_data<_Ty>* Next;
    __list_data<_Ty>* Previous;
    _Ty Data;

    constexpr __list_data()
        : Next(nullptr),
          Previous(nullptr),
          Data()
    {}

    _Ty* _Get_Data()
    {
        return __fcl::addressof(Data);
    } 

    const _Ty* _Get_Data() const
    {
        return __fcl::addressof(Data);
    } 
};

template<class _Ty>
struct __list_iter
{
    using node_type = __list_data<_Ty>;
    using iterator_category = _FCL::bidirectional_iterator_tag;
    using value_type = remove_const_t<_Ty>;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;

    __list_iter(node_type* node)
        : _m_Node(node)
    {}

    __list_iter& operator++()
    {
        _m_Node = _m_Node->Next;
        return *this;
    }

    __list_iter& operator--()
    {
        _m_Node = _m_Node->Previous;
        return *this;
    }

    __list_iter& operator++(int)
    {
        auto __th = *this;
        _m_Node = _m_Node->Next;
        return __th;
    }

    __list_iter& operator--(int)
    {
        auto __th = *this;
        _m_Node = _m_Node->Previous;
        return __th;
    }

    reference operator*() const
    {
        return *_m_Node->_Get_Data();
    }

    pointer operator->() const
    {
        return _m_Node->_Get_Data();
    }

    bool operator==(const __list_iter& __rhs) const
    {
        return __rhs._m_Node == _m_Node;
    }

    bool operator!=(const __list_iter& __rhs) const
    {
        return __rhs._m_Node != _m_Node;
    }

    node_type* _m_Node;
};

template<class _Ty, class _Aly = _FCL::allocator<_Ty>>
class __list
{
    using value_type = _Ty;
    using allocator = _Aly;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using iterator = __list_iter<_Ty>;
    
public:
    explicit __list(_Aly __al = _Aly())
        : _m_Allocator(__al),
          _m_Begin(nullptr),
          _m_End(nullptr),
          _m_Length(0)
    {}

    explicit __list(size_type __items, _Aly __al = _Aly())
        : __list(__al)
    {
        _m_Begin = _Construct_Many(__items, &_m_End);
    }

    void _Resize(size_type __s)
    {
        if (__s > _Get_Size())
        {
            __list_data<_Ty>* __nend;
            _m_End->Next = _Construct_Many(__s - _Get_Size(), &__nend);
            _m_End = __nend;
            return;
        }

        auto __beg = _Get_Begin();
        _FCL::advance(__beg, __s);
        _m_End = __beg;
    }

    void _Push_Back(const _Ty& value)
    {
        auto __tmp = _m_DataAlloc.allocate(1);
        auto* __cplace = &_m_End->Next;
        if (!_m_End)
        {
            __cplace = &_m_Begin;
            _m_End = _m_DataAlloc.allocate(1);
            _m_End->Previous = _m_Begin;
            _m_Begin->Next = _m_End;
        }
        
        __tmp->Data = value;
        (*__cplace) = __tmp;
        
        _m_Length++;
    }

    constexpr __list_data<_Ty>* _Construct_Many(size_type __items, 
                                                __list_data<_Ty>** __end)
    {
        __items++;
        __list_data<_Ty>* __tmp = nullptr;
        __list_data<_Ty>* __tmp_2 = nullptr;
        __list_data<_Ty>* __prev = nullptr;
        __list_data<_Ty>* __first = nullptr;

        while(__items > 0)
        {
            __tmp = _m_DataAlloc.allocate(1);
            if (__first == nullptr)
                __first = __tmp;
            
            __tmp_2 = __tmp;
            __tmp->Data = _Ty();
            __tmp->Previous = __prev;
            if (__prev)
                __prev->Next = __tmp;

            __prev = __tmp;

            _m_Length++;
            __items--;
        }

        if (__end != nullptr)
        {
            __tmp = _m_DataAlloc.allocate(1);
            __tmp->Previous = __tmp_2;
            (*__end) = __tmp;
        }
            
        return __first;
    }

    constexpr void _Create_End()
    {
        if (_m_End == nullptr && _m_Begin == nullptr)
        {
            _m_Begin = _Construct_Many(1, &_m_End);
            return;
        }
        
        /* If we don't have an end, we also don't have a length */
        auto __t = _m_Begin;
        size_t __length = 0;
        while(__t->Next != nullptr)
        {
            __length++;
            __t = __t->Next;
        }
        
        _m_Length = __length;
        _m_End = __t;
    }

    constexpr iterator begin()
    {
        return _Get_Begin();
    }

    constexpr iterator end()
    {
        return _Get_End();
    }

    constexpr iterator _Get_Begin()
    {
        return iterator(_m_Begin);
    }

    constexpr iterator _Get_End()
    {
        return iterator(_m_End);
    }

    constexpr _Aly _Get_Allocator()
    {
        return _m_Allocator;
    }

    constexpr size_type _Get_Size()
    {
        return _m_Length;
    }

private:
    _FCL::allocator<__list_data<_Ty>> _m_DataAlloc;
    __list_data<_Ty>* _m_Begin;
    __list_data<_Ty>* _m_End;
    size_type _m_Length;
    _Aly _m_Allocator;
};

}

_FCL_NAMESPACE_BEGIN

template<class _Ty, class _Aly = _FCL::allocator<_Ty>>
using list = __fcl::__list<_Ty, _Aly>;

_FCL_NAMESPACE_END

