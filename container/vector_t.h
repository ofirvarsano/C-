#ifndef __VECTOR_T_H__
#define __VECTOR_T_H__
#include "container_t.h"
#include <stdlib.h>
#include <string.h>
using namespace std;

template <class T>
class vector_t : public container_t<T>
{
	public:
		//size_t Count() const { return m_numOfItems; };
		//bool IsEmpty() const { return m_numOfItems == 0; };
		vector_t();
		vector_t(const vector_t<T>& _vec);
		~vector_t() { delete [] m_elements; }
		
		const vector_t& operator = (const vector_t<T>& _vec);
		virtual bool Append(size_t _index, const T* _item) { return AddTo(_item, _index + 1); }
		virtual bool Prepend(size_t _index, const T* _item) { return AddTo(_item, _index); }
		virtual bool Contains(const T& _item) const;
		virtual const T* Find(const T& _value) const;
		virtual int Index(const T& _item) const;
		virtual bool Insert(const T* _item) { return AddTo(_item, this->Count()); }
		virtual const T* Remove(const T& _value);
		virtual bool RemoveAndDelete(const T& _value);
		virtual void RemoveAll();
		virtual void RemoveAndDeleteAll();
  
	private:
		//size_t m_nOfElements;
		T** m_elements;
		size_t m_capacity;
		
		bool AddTo(const T* _item, size_t _index);
		void Resize();
		void ShiftElements(size_t _begin, size_t _end);
};

const size_t defaultCapacity = 8;

template <class T>
vector_t<T>::vector_t() : m_capacity(defaultCapacity)
{
    m_elements = new T*[defaultCapacity];
}

template <class T>
vector_t<T>::vector_t(const vector_t<T>& _vec) : container_t<T>(_vec) , m_capacity(_vec.m_capacity)
{
	size_t size = _vec.Count();
	m_elements = new T*[m_capacity];
	for(size_t i = 0; i < size; i++)
	{
		m_elements[i] = (T*)_vec.m_elements[i];
	}
}

template <class T>
const vector_t<T>& vector_t<T>::operator = (const vector_t<T>& _vec)
{
	size_t size;

	if(this == &_vec)
	{
		return *this;
	}
	container_t<T>::operator = (_vec); // number of elements
	
	delete[] m_elements;
	m_elements = new T*[_vec.m_capacity];

	size = _vec.Count();

	for(size_t i = 0; i < size; ++i)
	{
		m_elements[i] = _vec.m_elements[i];
	}
	return *this;
}

template <class T>
bool vector_t<T>::Contains(const T& _item) const
{
    size_t curr = 0;
    while (curr < this->m_numOfItems)
    {
        if (_item == *m_elements[curr])
        {
        	return true;
        }
        ++curr;
    }
    return false;
}

template <class T>
const T* vector_t<T>::Find(const T& _item) const
{
    size_t curr = 0;
    while (curr < this->m_numOfItems)
    {
        if (_item == *m_elements[curr])
        {
        	return m_elements[curr];
        }
        ++curr;
    }
    return NULL;
}

template <class T>
int vector_t<T>::Index(const T& _item) const
{
    int curr = 0;
    while (curr < (int)this->m_numOfItems)
    {
        if (_item == *m_elements[curr])
        {
        	return curr;
        }
        ++curr;
    }
    return -1;
}

template <class T>
const T* vector_t<T>::Remove(const T& _item)
{
	size_t size = this->Count();
	T* removed = (T*)Find(_item);
	if(!removed)
	{
		return NULL;
	}

	for(size_t i = Index(_item); i < size - 1; ++i)
	{
		m_elements[i] = m_elements[i+1];
	}

	--this->m_numOfItems;
	return removed;
}

template <class T>
bool vector_t<T>::RemoveAndDelete(const T& _item)
{
	const T* removed = Remove(_item);
	if(removed)
	{
		delete removed;
		return true;
	}

	return false;
}

template <class T>
void vector_t<T>::RemoveAll()
{
	this->m_numOfItems = 0;
}

template <class T>
void vector_t<T>::RemoveAndDeleteAll()
{
	T* removed = NULL;
	size_t size = this->Count();

	for(size_t i = 0; i < size; ++i)
	{
		removed = m_elements[i];
		delete removed;
	}
	this->m_numOfItems = 0;
}

template <class T>
bool vector_t<T>::AddTo(const T* _item, size_t _index)
{
	size_t size = this->Count();
	if(!m_elements || !_item || _index > size)
	{
		return false;
	}
	if(size == m_capacity)
	{
		Resize();
	}
	if(_index != this->m_numOfItems)
	{
		ShiftElements(_index, this->m_numOfItems - 1);
	}
	m_elements[_index] = (T*)_item;
	++this->m_numOfItems;

	return true;
}

template <class T>
void vector_t<T>::Resize()
{
    T** temp = new T*[m_capacity * 2];
    size_t size = this->Count();

	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = m_elements[i];
	}
	
    delete [] m_elements;
    m_elements = temp;
    m_capacity *= 2;
}

template <class T>
void vector_t<T>::ShiftElements(size_t _begin, size_t _end)
{
    while (_end >= _begin)
    {
        m_elements[_end + 1] = m_elements[_end];
        --_end;
    }
}

#endif //__VECTOR_T_H__
