/***********************************************************************
* Header:
*    Set
* Summary:
*    This class contains a set class (with the same functionality as
*    the standard template library (STL) Set class).
*
*    This will contain the class definition of:
*        Set         : A class that holds unique elements
*        SetIterator : An interator through a set
* Author
*    Shayla Nelson
************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>
#include <iostream>
using namespace std;

// declare SetIterator
template <class T>
class SetIterator;

// declare SetConstIterator
template <class T>
class SetConstIterator;

/************************************************
 * SET
 * A class that holds unique elements
 ***********************************************/
template <class T>
class Set
{
public:
   // default constructor
   Set() : numItems(0), m_capacity(0), data(NULL) {}

   // non-default constructor
   Set(int m_capacity) throw (const char *);

   // copy constructor
   Set(const Set & rhs) throw (const char *);

   // destructor
   // ~Set()   { if (m_capacity) delete [] data; }

   // assignment operator
   Set<T>& operator=(const Set<T> &rhs) throw (const char *);

   // check if set is empty
   bool empty() const   { return numItems == 0; }

   // return capacity of set
   int capacity() const { return m_capacity; }

   // remove all items from the set
   void clear()   { numItems = 0; }

   // return number of items in set
   int size() const  { return numItems; }

   // find the index of an item
   int findIndex(const T & t);

   // determine if an item is in the set
   SetIterator <T> find(const T & t) throw (const char *);

   // add an item to the set
   void insert(const T & t) throw (const char *);

   // delete an item from the set
   void erase(SetIterator <T> & it) throw (const char *);

   // add to end of set
   void addToEnd(const T & t) throw (const char *);

   // intersection operator
   Set<T> operator&&(Set<T> rhs) throw (const char * );
   const Set<T> operator&&(Set<T> rhs) const throw (const char *);

   // union operator
   Set<T> operator||(Set<T> rhs) throw (const char * );
   const Set<T> operator||(Set<T> rhs) const throw (const char *);

   // return an iterator to first element in set
   SetIterator <T> begin() { return SetIterator<T>(data); }
   SetConstIterator <T> cbegin() const
         { return SetConstIterator<T>(data); }

   // return an iterator to the past-the-end element in set
   SetIterator <T> end() { return SetIterator<T>(data + numItems);}
   SetConstIterator <T> cend() const
         { return SetConstIterator<T>(data + numItems); }

private:
   T * data;          // dynamically allocated array of T
   int numItems;      // number of items in the set
   int m_capacity;    // number of items the set can hold
};

/**************************************************
 * SET ITERATOR
 * An iterator through Set
 *************************************************/
template <class T>
class SetIterator
{
  public:
   // default constructor
   SetIterator() : p(NULL) {}

   // initialize to direct p to some item
   SetIterator(T * p) : p(p) {}

   // copy constructor
   SetIterator(const SetIterator & rhs) { *this = rhs; }

   // assignment operator
   SetIterator & operator = (const SetIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const SetIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   SetIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   SetIterator <T> operator++(int postfix)
   {
      SetIterator tmp(*this);
      p++;
      return tmp;
   }

   // prefix decrement
   SetIterator <T> & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   SetIterator <T> operator--(int postfix)
   {
      SetIterator tmp(*this);
      p--;
      return tmp;
   }

  private:
    T * p;
};

/**************************************************
 * SET CONST ITERATOR
 * An iterator through Set
 *************************************************/
template <class T>
class SetConstIterator
{
  public:
   // default constructor
   SetConstIterator() : p(NULL) {}

   // initialize to direct p to some item
   SetConstIterator(T * p) : p(p) {}

   // copy constructor
   SetConstIterator(const SetConstIterator & rhs) { *this = rhs; }

   // assignment operator
   SetConstIterator & operator = (const SetConstIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const SetConstIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   SetConstIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   SetConstIterator <T> operator++(int postfix)
   {
      SetConstIterator tmp(*this);
      p++;
      return tmp;
   }

   // prefix decrement
   SetConstIterator <T> & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   SetConstIterator <T> operator--(int postfix)
   {
      SetConstIterator tmp(*this);
      p--;
      return tmp;
   }

  private:
   T * p;
};

/**********************************************
 * SET : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Set to "capacity"
 **********************************************/
template <class T>
Set <T> :: Set(int m_capacity) throw (const char *)
{
   assert(m_capacity >= 0);

   // do nothing if there is nothing to do
   if (m_capacity == 0)
   {
      this->m_capacity = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[m_capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Set";
   }

   // copy over the stuff
   this->m_capacity = m_capacity;
   this->numItems = 0;

   // initialize the set by calling the default constructor
   for (int i = 0; i < m_capacity; i++)
      data[i] = T();
}

/*******************************************
 * SET :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Set <T> :: Set(const Set <T> & rhs) throw (const char *)
{
   assert(rhs.m_capacity >= 0);

   // do nothing if there is nothing to do
   if (rhs.m_capacity == 0)
   {
      m_capacity = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.m_capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Set";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.m_capacity);
   m_capacity = rhs.m_capacity;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < m_capacity; i++)
      data[i] = T();
}

/***************************************************
 * SET :: ASSIGNMENT OPERATOR
 * Copy data from one set to another
 **************************************************/
template <class T>
Set<T> & Set<T> :: operator=(const Set & rhs) throw (const char *)
{
   assert(rhs.m_capacity >= 0);

   // do nothing if there is nothing to do
   if (rhs.m_capacity == 0)
   {
      m_capacity = numItems = 0;
      data = NULL;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.m_capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Set";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.m_capacity);
   m_capacity = rhs.m_capacity;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < m_capacity; i++)
      data[i] = T();

   return *this;
}

/***************************************************
 * SET :: FIND INDEX
 * Finds the index of an item
 **************************************************/
template <class T>
int Set <T> :: findIndex(const T & t)
{
   int iBegin = 0;
   int iEnd = numItems - 1;
   while (iBegin <= iEnd)
   {
      int iMiddle = (iBegin + iEnd) / 2;
      if (t == data[iMiddle])
         return iMiddle;
      if (t < data[iMiddle])
         iEnd = iMiddle - 1;
      else
         iBegin = iMiddle + 1;
   }
   return -1;
}

/***************************************************
 * SET :: FIND
 * If item is in set, returns an iterator pointing to it
 **************************************************/
template <class T>
SetIterator <T> Set <T> :: find(const T & t) throw (const char *)
{
   int index = findIndex(t);
   if (index > -1)
      return SetIterator <T>(data + index);
   else
      return end();
}

/***************************************************
 * SET :: INSERT
 * Insert an item into the set
 **************************************************/
template <class T>
void Set <T> :: insert(const T & t) throw (const char *)
{
   // if empty, set capacity to 1
   if (numItems == 0) {
      m_capacity = 1;
      data = new T[m_capacity];
   }

   if (m_capacity == numItems)
   {
      // allocate the new buffer
      try {
         T *bufferNew = new T[m_capacity *= 2];

         // copy the data into the new buffer
         int i;
         for (i = 0; i < numItems; i++)
            bufferNew[i] = data[i];
         bufferNew[i] = '\0';

         // delete the old buffer
         delete [] data;

         // reset data
         data = bufferNew;
      }
      catch(std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Set";
         m_capacity /= 2;
         return;
      }
   }

   // add an item to the ordered set
   int index = findIndex(t);
   if (empty())
   {
      data[0] = t;
      numItems++;
   }
   else if (index == -1)
   {
      T * tempSet = new T[m_capacity];
      T greatest = t;
      for (int i = 0; i < numItems; i++)
      {
         if (greatest > data[i])
         {
            tempSet[i] = data[i];
         }
         else
         {
            tempSet[i] = greatest;
            greatest = data[i];
         }
      }
      tempSet[numItems] = greatest;
      delete [] data;
      data = tempSet;
      numItems++;
   }
}

/***************************************************
 * SET :: ERASE
 * Removes an element from the set
 **************************************************/
template <class T>
void Set <T> :: erase(SetIterator <T> & it) throw (const char *)
{
   try
   {
      T value = *it;
      int index = findIndex(value);
      for (int i = index; i < numItems - 1; i++)
      {
         data[i] = data[i + 1];
      }
      numItems--;
   }
   catch(...)
   {
      throw "ERROR: Unable to erase item";
   }
}

/***************************************************
 * SET :: ADD TO END
 * Add item to the end of a set
 **************************************************/
template <class T>
void Set <T> :: addToEnd(const T & t) throw (const char *)
{
   // if empty, set capacity to 1
   if (numItems == 0) {
      m_capacity = 1;
      data = new T[m_capacity];
   }

   if (m_capacity == numItems)
   {
      // allocate the new buffer
      try {
         T *bufferNew = new T[m_capacity *= 2];

         // copy the data into the new buffer
         int i;
         for (i = 0; i < numItems; i++)
            bufferNew[i] = data[i];
         bufferNew[i] = '\0';

         // delete the old buffer
         delete [] data;

         // reset data
         data = bufferNew;
      }
      catch(std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Set";
         m_capacity /= 2;
         return;
      }
   }
   data[numItems++] = t;
}

/***************************************************
 * SET :: INTERSECTION OPERATOR
 * Returns a new set containing all the elements
 * that are in both this and in the parameter
 **************************************************/
template <class T>
Set<T> Set<T> :: operator&&(Set <T> rhs) throw (const char * )
{
   Set <T> setReturn;
   int iSet1 = 0;
   int iSet2 = 0;
   while (iSet1 < this->size() || iSet2 < rhs.size())
   {
      if (iSet1 == this->size())
         return setReturn;
      else if (iSet2 == rhs.size())
         return setReturn;
      else if (this->data[iSet1] == rhs.data[iSet2])
      {
         setReturn.addToEnd(this->data[iSet1]);
         iSet1++;
         iSet2++;
      }
      else if (this->data[iSet1] < rhs.data[iSet2])
         iSet1++;
      else
         iSet2++;
   }
   return setReturn;
}

/***************************************************
 * SET :: INTERSECTION OPERATOR (CONST)
 * Returns a new set containing all the elements
 * that are in both this and in the parameter
 **************************************************/
template <class T>
const Set<T> Set<T> :: operator&&(Set <T> rhs) const throw (const char * )
{
   Set <T> setReturn;
   int iSet1 = 0;
   int iSet2 = 0;
   while (iSet1 < this->size() || iSet2 < rhs.size())
   {
      if (iSet1 == this->size())
         return setReturn;
      else if (iSet2 == rhs.size())
         return setReturn;
      else if (this->data[iSet1] == rhs.data[iSet2])
      {
         setReturn.addToEnd(this->data[iSet1]);
         iSet1++;
         iSet2++;
      }
      else if (this->data[iSet1] < rhs.data[iSet2])
         iSet1++;
      else
         iSet2++;
   }
   return setReturn;
}

/***************************************************
 * SET :: UNION OPERATOR
 * Returns a new set containing all the elements
 * that are in either this or in the parameter
 **************************************************/
template <class T>
Set<T> Set<T> :: operator||(Set <T> rhs) throw (const char * )
{
   Set <T> setReturn;
   int iSet1 = 0;
   int iSet2 = 0;
   while (iSet1 < this->size() || iSet2 < rhs.size())
   {
      if (iSet1 == this->size())
         setReturn.addToEnd(rhs.data[iSet2++]);
      else if (iSet2 == rhs.size())
         setReturn.addToEnd(this->data[iSet1++]);
      else if (this->data[iSet1] == rhs.data[iSet2])
      {
         setReturn.addToEnd(this->data[iSet1]);
         iSet1++;
         iSet2++;
      }
      else if (this->data[iSet1] < rhs.data[iSet2])
         setReturn.addToEnd(this->data[iSet1++]);
      else
         setReturn.addToEnd(rhs.data[iSet2++]);
   }
   return setReturn;
}

/***************************************************
 * SET :: UNION OPERATOR (CONST)
 * Returns a new set containing all the elements
 * that are in either this or in the parameter
 **************************************************/
template <class T>
const Set<T> Set<T> :: operator||(Set<T> rhs) const throw (const char * )
{
   Set <T> setReturn;
   int iSet1 = 0;
   int iSet2 = 0;
   while (iSet1 < this->size() || iSet2 < rhs.size())
   {
      if (iSet1 == this->size())
         setReturn.addToEnd(rhs.data[iSet2++]);
      else if (iSet2 == rhs.size())
         setReturn.addToEnd(this->data[iSet1++]);
      else if (this->data[iSet1] == rhs.data[iSet2])
      {
         setReturn.addToEnd(this->data[iSet1]);
         iSet1++;
         iSet2++;
      }
      else if (this->data[iSet1] < rhs.data[iSet2])
         setReturn.addToEnd(this->data[iSet1++]);
      else
         setReturn.addToEnd(rhs.data[iSet2++]);
   }
   return setReturn;
}

#endif // SET_H
