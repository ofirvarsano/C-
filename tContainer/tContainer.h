#ifndef T_CONTAINER_H
#define T_CONTAINER_H

#include <algorithm>
#include <typeinfo>
#include <vector>
#include <list>
#include <iostream>
#include "ExceptionHandler.h"
using namespace std;

template <typename T, typename CONT>
class tContainer_t
{
	public:
		typedef typename CONT::iterator iter_t;
		typedef typename CONT::const_iterator citer_t;

		tContainer_t() {}
		~tContainer_t() {}
		
		bool	IsEmpty() const				{return m_cont.empty();}
		size_t	NumOfElements() const		{return m_cont.size();}
		void	Insert(T* _element)	{m_cont.push_back(_element);}
		T*		GetFirst() const			{return m_cont.empty() ? NULL : m_cont.front();}
		T*		GetLast() const				{return m_cont.empty() ? NULL : m_cont.back();}
		T*		FindElementIf(const T& _element) const;
		T*		RemoveElement(const T& _element);
		void	RemoveAllElements() {m_cont.clear();}
		void	RemoveAndDeleteElement(const T& _element);
		void	RemoveAndDeleteAllElements();
		T*		operator [] (size_t _index) const;
		
		private:
		CONT	m_cont;

		tContainer_t(const tContainer_t&) {}
		tContainer_t& operator = (const tContainer_t&) {}
		
		class Find
		{
			public:
				Find(T _i) : val(_i) {}
				bool operator () (T* _element) { return *_element == val; }
			private:
				T val;
		};
};

template <typename T, typename CONT>
T* tContainer_t<T,CONT>::FindElementIf(const T& _element) const
{
	citer_t it = find_if(m_cont.begin(), m_cont.end(), Find(_element));
	
	return (it == m_cont.end() ? NULL : *it);
}

template <typename T, typename CONT>
T* tContainer_t<T,CONT>::RemoveElement(const T& _element)
{
	iter_t it = find_if(m_cont.begin(), m_cont.end(), Find(_element));
	if(it == m_cont.end())
	{
		return NULL;
	}
	else
	{
		T* ret = *it;
		m_cont.erase(it);
		return ret;
	}
}

template <typename T, typename CONT>
void tContainer_t<T,CONT>::RemoveAndDeleteElement(const T& _element)
{
	iter_t it = find_if(m_cont.begin(), m_cont.end(), Find(_element));
	if(it == m_cont.end())
	{
		throw TException_t<T>(_element, __FILE__, __LINE__, "element not found");
	}
	else
	{
		T* ret = *it;
		m_cont.erase(it);
		delete ret;
	}
}

template <typename T, typename CONT>
void tContainer_t<T,CONT>::RemoveAndDeleteAllElements()
{
	size_t size = m_cont.size();
	while(size)
	{
		iter_t it = m_cont.begin();
		T* ret = *it;
		m_cont.erase(it);
		delete ret;
		--size;
	}
}

template <typename T, typename CONT>
T* tContainer_t<T,CONT>::operator [] (size_t _index) const
{
	if(m_cont.size() <= _index)
	{
		NULL;
	}

	if(typeid(m_cont) == typeid(vector<T*>))
	{
		return (*(vector<T*>*)&m_cont)[_index];
	}
	else
	{
		size_t i;
		citer_t it = m_cont.begin();
		for(i = 0 ; i < _index ; it++, i++){}

		return *it;
	}
}


#endif //T_CONTAINER_H

