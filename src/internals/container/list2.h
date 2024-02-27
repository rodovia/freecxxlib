#pragma once

#include "../iterator.h"
#include "../ctordtor.h"
#include <cstdio>

namespace __fcl
{

template<class _Ty>
struct list_node
{
    list_node<_Ty>* _m_Next;
    list_node<_Ty>* _m_Previous;
    _Ty _m_Data;

    list_node(_Ty __data = _Ty())
        : _m_Data(__data),
          _m_Next(nullptr),
          _m_Previous(nullptr)
    {}
};

template<class _Ty>
struct list_iterator
{
    using node_type = list_node<_Ty>;
    using iterator_category = _FCL::bidirectional_iterator_tag;
    using value_type = remove_const_t<_Ty>;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;

    list_iterator(node_type* node = nullptr)
        : _m_Node(node)
    {}

    list_iterator& operator++()
    {
        _m_Node = _m_Node->_m_Next;
        return *this;
    }

    list_iterator& operator--()
    {
        _m_Node = _m_Node->_m_Previous;
        return *this;
    }

    list_iterator& operator++(int)
    {
        auto __th = *this;
        _m_Node = _m_Node->_m_Next;
        return __th;
    }

    list_iterator& operator--(int)
    {
        _m_Node = _m_Node->_m_Previous;
        return *this;
    }

    reference operator*() const
    {
        return _m_Node->_m_Data;
    }

    pointer operator->() const
    {
        return __fcl::addressof(_m_Node->_m_Data);
    }

    bool operator==(const list_iterator& __rhs) const
    {
        return __rhs._m_Node == _m_Node;
    }

    bool operator!=(const list_iterator& __rhs) const
    {
        return __rhs._m_Node != _m_Node;
    }

    node_type* _m_Node;
};

template<class _Ty>
struct linked_list
{
    using iterator = list_iterator<_Ty>;

    linked_list()
        : _m_Head(nullptr),
          _m_Tail(nullptr),
          _m_UseEndTail(false),
          _m_Length(0)
    {}

    ~linked_list()
    {
        printf("DTOR! size() = %i\n", size());

        size_t __dtored = 0;
        list_node<_Ty>* __old;
        list_node<_Ty>* __ptr = _m_Head;
        while (__dtored < size())
        {
            __old = __ptr;
            __ptr = __ptr->_m_Next;
            printf("dtoring %p\n", __old);
            __fcl::destroy_one(__fcl::addressof(__old));
            __dtored++;
        }

        printf("end of DTOR\n");
    }

    void insert_pos(iterator __iter, const _Ty& __value)
    {
        auto __ptr = new list_node(__value);
        auto __old_next = __iter._m_Node->_m_Next;
        __iter._m_Node->_m_Next = __ptr;
        __ptr->_m_Previous = __iter._m_Node;
    }

    /* Inserts value at the end of list.
       No iterators are invalidated at function call. */
    void insert_back(const _Ty& __value)
    {
        auto __ptr = new list_node(__value);
        _m_Length++;

        if (_m_Head == nullptr)
        {
            _m_Head = __ptr;
            return;
        }

        if (_m_Tail == nullptr)
        {
            _m_Tail = __ptr;
            _m_Tail->_m_Previous = _m_Head;
            _m_Head->_m_Next = _m_Tail;
            return;
        }

        _m_Tail->_m_Next = __ptr;
        __ptr->_m_Previous = _m_Tail;
        _m_Tail = __ptr;
    }

    /* Removes the item located at *iter, and executes
       its destructor, if it has a non-trivial destructor.
       
       Only iter is invalidated.iter must not be reused; the behaviour is undefined
       if it is. */
    void remove(iterator __iter)
    {
        iterator __old_iter;
        _m_Length--;

        /* it is the first element */
        if (__iter._m_Node == _m_Head)
        {
            __old_iter = _m_Head;
            _m_Head = _m_Head->_m_Next;
            goto __l_delete;
        }
        
        /* it is the last element */
        if (__iter._m_Node->_m_Next == nullptr)
        {
            __old_iter = __iter;
            auto __iteri = __iter._m_Node->_m_Previous;
            __iteri->_m_Next = nullptr;
            goto __l_delete;
        }

        __old_iter = __iter;
        __iter._m_Node->_m_Previous->_m_Next = __old_iter._m_Node->_m_Next;
        __iter._m_Node->_m_Next->_m_Previous = __iter._m_Node->_m_Previous->_m_Next;
        
    __l_delete:
        delete __old_iter._m_Node;
    }

    constexpr iterator begin()
    {
        return iterator(_m_Head);
    }

    constexpr iterator end()
    {
        return iterator(_m_Tail);
    }

    constexpr size_t size()
    {
        return _m_Length;
    }

private:
    /* Ensure the tail is always one bit after. */
    void _Ensure_End()
    {
        auto __old_tail = _m_Tail;
        _m_Tail = new list_node<_Ty>();
        __old_tail->_m_Next = _m_Tail;
        _m_Tail->_m_Previous = __old_tail;
        _m_UseEndTail = true;
    }

    list_node<_Ty>* _m_Head;
    list_node<_Ty>* _m_Tail;
    size_t _m_Length;
    bool _m_UseEndTail;
};

}
