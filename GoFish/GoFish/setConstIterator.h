#ifndef SETCONSTITERATOR_H
#define SETCONSTITERATOR_H

/*********************************************************************
* Class: SETCONSTITERATOR
*********************************************************************/
template <class T>
class SetConstIterator
{
public:
   // pre-fix increment
   SetConstIterator<T> & operator ++ ()
   {
      return *this;
   }

   // de-referecne
   T operator * () const
   {
      return T();
   }
};

template <class T>
bool operator == (const SetConstIterator<T> & lhs, const SetConstIterator<T> & rhs)
{
   return false;
}

template <class T>
bool operator != (const SetConstIterator<T> & lhs, const SetConstIterator<T> & rhs)
{
   return false;
}

#endif // !SETCONSTITERATOR_H
