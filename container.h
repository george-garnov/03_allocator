#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include "iterator.h"
#include <memory>

template<typename T, class Alloc = std::allocator<T>>
class Container
{
public:
    typedef T& reference; 
    typedef const T& const_reference;
    typedef Iterator<T> iterator;
    typedef Iterator<const T> const_iterator;

    Container() = default;
    ~Container() = default;
    
    reference operator[] (size_t n)
    {
        return data[n];
    }
    
    const_reference operator[] (size_t n) const
    {
        return data[n];
    }
    

    iterator begin()
    {
        return iterator(data);
    }
    
    iterator end()
    {
        return iterator(data + size);
    }

    const_iterator begin() const
    {
        return const_iterator(data);
    }
    
    const_iterator end() const
    {
        return const_iterator(data + size);
    }
    
private:
    const size_t size;
    T data[10];
};

#endif // __CONTAINER_H__
