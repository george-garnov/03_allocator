#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <iterator>

template<typename ValueType>
class Iterator: public std::iterator<std::input_iterator_tag, ValueType>
{
public:
    Iterator(ValueType* p);
    Iterator(const Iterator &it);

    bool operator!=(Iterator const& other) const;
    bool operator==(Iterator const& other) const;
    typename Iterator::reference operator*() const;
    Iterator& operator++();
private:
    ValueType* p;
};

template<typename ValueType>
Iterator<ValueType>::Iterator(ValueType *p) :
    p(p)
{

}

template<typename ValueType>
Iterator<ValueType>::Iterator(const Iterator& it) :
    p(it.p)
{

}

template<typename ValueType>
bool Iterator<ValueType>::operator!=(Iterator const& other) const
{
    return p != other.p;
}

template<typename ValueType>
bool Iterator<ValueType>::operator==(Iterator const& other) const
{
    return p == other.p;
}

template<typename ValueType>
typename Iterator<ValueType>::reference Iterator<ValueType>::operator*() const
{
    return *p;
}

template<typename ValueType>
Iterator<ValueType> &Iterator<ValueType>::operator++()
{
    ++p;
    return *this;
}

#endif // __ITERATOR_H__
