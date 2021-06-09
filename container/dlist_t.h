#ifndef __DLIST_T__
#define __DLIST_T__

#include <iostream>
#include <stddef.h>
#include "container_t.h"

#define IS_BEFORE 	true
#define IS_AFTER 	false

using namespace std;

template <class T>
class dlist_t : public container_t<T>
{
	public:
	/*
		size_t Count() const { return m_numOfItems; }
		bool IsEmpty() const { return m_numOfItems == 0; }
	*/
		dlist_t();
		dlist_t(const dlist_t<T>& _list);
		virtual ~dlist_t();
		
		const dlist_t& operator = (const dlist_t<T>& _list);
		virtual bool Append(size_t _index, const T* _item);
		virtual bool Prepend(size_t _index, const T* _item);
		virtual bool Contains(const T& _item) const {const T* t = Find(_item); return (bool)t; }
		virtual const T* Find(const T& _value) const;
		virtual int Index(const T& _item) const;
		virtual bool Insert(const T* _item);
		virtual const T* Remove(const T& _value);
		virtual bool RemoveAndDelete(const T& _value);
		virtual void RemoveAll();
		virtual void RemoveAndDeleteAll();

	private:
		class Node
		{
		public:
			Node(){ m_data = NULL; m_prev = m_next = NULL; }
			Node(const T* _data) { m_data = _data; m_next = m_prev = NULL;}
			~Node(){}
			
			const T* m_data; //delete const
			Node* m_next;
			Node* m_prev;
		};

		Node m_head;
		Node m_tail;
		//size_t m_numOfItems;
		bool InsertBefore(Node* _t, const T* _item);

};

template <class T>
dlist_t<T>::dlist_t()
{
	m_head.m_prev = NULL;
	m_tail.m_next = NULL;
	m_head.m_next = &m_tail;
	m_tail.m_prev = &m_head;
}

template <class T>
dlist_t<T>::~dlist_t()
{
	Node* curr = m_head.m_next;
	for(size_t i = 0; i < this->m_numOfItems; ++i)
	{
		curr = curr->m_next;
		delete curr->m_prev;
	}
}

template <class T>
dlist_t<T>::dlist_t(const dlist_t<T>& _list)
{
	Node* curr = _list.m_head.m_next;
	for(size_t i = 0; i < _list.m_numOfItems; ++i)
	{
		Insert(curr->m_data);
		curr = curr->m_next;
	}
}

template <class T>
const dlist_t<T>& dlist_t<T>::operator = (const dlist_t<T>& _list)
{
	if(this == &_list)
	{
		return *this;
	}
	RemoveAll();
	Node* curr = _list.m_head.m_next;
	for(size_t i = 0; i < _list.m_numOfItems; ++i)
	{
		Insert(curr->m_data);
		curr = curr->m_next;
	}
	return *this;
}

template <class T>
bool dlist_t<T>::Append(size_t _index, const T* _item)
{
	Node* curr = m_head.m_next;
	if(_index > this->m_numOfItems || !_item)
	{
		return false;
	}
	for (size_t i = 0; i < _index; ++i)
	{
		curr = curr->m_next;
	}
	if(_index == 0)
	{
		return InsertBefore(m_head.m_next, _item);
	}
	return InsertBefore(curr->m_next, _item);
}

template <class T>
bool dlist_t<T>::Prepend(size_t _index, const T* _item)
{
	Node* curr = m_head.m_next;
	if(_index > this->m_numOfItems || !_item)
	{
		return false;
	}
	for (size_t i = 0; i < _index; ++i)
	{
		curr = curr->m_next;
	}
	if(_index == 0)
	{
		return InsertBefore(m_head.m_next, _item);
	}
	return InsertBefore(curr->m_prev, _item);
}

template <class T>
bool dlist_t<T>::InsertBefore(Node* _t, const T* _item)
{
	Node* node = new(nothrow) Node(_item);
	if (!node)
	{
		return false;
	}
	node->m_next = _t;
	node->m_prev = _t->m_prev;
	_t->m_prev->m_next = node;
	_t->m_prev = node;
	
	++this->m_numOfItems;
	return true;
}
	
template <class T>
bool dlist_t<T>::Insert(const T* _item)
{
	if (!_item)
	{
		return false;
	}
	return InsertBefore(&m_tail, _item);
}	
	
template <class T>
const T* dlist_t<T>::Find(const T& _item) const
{
	Node* curr = m_head.m_next;
	for (size_t i = 0; i < this->m_numOfItems; ++i)
	{
		if(*(curr->m_data) == _item)
		{
			return curr->m_data;
		}
		curr = curr->m_next;
	}
	return NULL;
}

template <class T>
int dlist_t<T>::Index(const T& _item) const
{
	Node* curr = m_head.m_next;
	for (int i = 0; i < (int)this->m_numOfItems; ++i)
	{
		if(*(curr->m_data) == _item)
		{
			return i;
		}
		curr = curr->m_next;
	}
	return -1;
}

template <class T>
const T* dlist_t<T>::Remove(const T& _item)
{
	Node* curr = m_head.m_next;
	size_t size = this->m_numOfItems;
	for (size_t i = 0; i < size; ++i)
	{
		if(*(curr->m_data) == _item)
		{
			curr->m_next->m_prev = curr->m_prev;
			curr->m_prev->m_next = curr->m_next;
			const T* data = curr->m_data;
			delete curr;
			--this->m_numOfItems;
			return data;
		}
		curr = curr->m_next;
	}
	return NULL;
}

template <class T>
bool dlist_t<T>::RemoveAndDelete(const T& _value)
{
	const T* data = Remove(_value);
	return (data ? delete data, true : false);
}

template <class T>
void dlist_t<T>::RemoveAll()	
{
	Node* curr = m_head.m_next;
	for(size_t i = 0; i < this->m_numOfItems; ++i)
	{
		curr = curr->m_next;
		delete curr->m_prev;
	}
	m_head.m_next = &m_tail;
	m_tail.m_prev = &m_head;
	this->m_numOfItems = 0;
}

template <class T>
void dlist_t<T>::RemoveAndDeleteAll()
{
	Node* curr = m_head.m_next;
	for(size_t i = 0; i < this->m_numOfItems; ++i)
	{
		curr = curr->m_next;
		delete curr->m_prev->m_data;
		delete curr->m_prev;
	}
	m_head.m_next = &m_tail;
	m_tail.m_prev = &m_head;
	this->m_numOfItems = 0;
}

#endif // __DLIST_T__

