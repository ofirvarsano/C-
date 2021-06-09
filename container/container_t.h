#ifndef __CONTAINER_T_H__
#define __CONTAINER_T_H__
#include <stdlib.h>

using namespace std;

template <class T>
class container_t
{
	public:
		container_t(): m_numOfItems(0) {};
		container_t(const container_t<T>& _cont) : m_numOfItems(_cont.m_numOfItems) {}
		const container_t& operator = (const container_t<T>& _cont) {m_numOfItems = _cont.m_numOfItems;}
		virtual ~container_t() {}

		virtual bool	Append(size_t _index, const T* _item) = 0;
		virtual bool	Prepend(size_t _index, const T* _item) = 0;
		virtual bool	Contains(const T& _item) const = 0;
		size_t			Count() const { return m_numOfItems; }
		virtual const T* Find(const T& _value) const = 0;
		virtual int Index(const T& _item) const = 0;
		virtual bool	Insert(const T* _item) = 0;
		bool			IsEmpty() const { return m_numOfItems == 0; }
		virtual const T* Remove(const T& _value) = 0;
		virtual bool	RemoveAndDelete(const T& _value) = 0;
		virtual void	RemoveAll() = 0;
		virtual void	RemoveAndDeleteAll() = 0;
		
	protected:
		size_t m_numOfItems;
};

#endif //__CONTAINER_T_H__
