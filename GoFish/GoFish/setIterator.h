#ifndef SETITERATOR_H
#define SETITERATOR_H

#include <cassert>
/********************************************************************
* Class: SETITERATOR
********************************************************************/
template <class T>
class SetIterator
{
public:

   // constructor
   SetIterator(T * in_ptr = NULL) : m_ptr(in_ptr) { }

   // pre-fix increment
   SetIterator<T> & operator ++()
   {
      ++m_ptr;
      return *this;
   }

   // de-reference
   T operator * () const
   {
      assert(m_ptr != NULL);
      if (NULL == m_ptr)
         throw "ERROR: attempt to access an empty iterator.";

      return *m_ptr;
   }

   // equality
   bool operator == (const SetIterator<T> & rhs) const;
   bool operator != (const SetIterator<T> & rhs) const;

private:
   T * m_ptr;
};

template <class T>
bool SetIterator<T> ::operator == (const SetIterator<T> & rhs) const
{
   return this->m_ptr == rhs.m_ptr;
}

template <class T>
bool SetIterator<T> ::operator != (const SetIterator<T> & rhs) const
{
   return !(*this == rhs);
}

#endif // !SETITERATOR_H
