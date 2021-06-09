#ifndef __MEMPAGE_H__
#define __MEMPAGE_H__
#include "memManager_t.h"

class MemPage_t : public MemManager_t
{
	public:
		MemPage_t() : m_capacity(defaultCapacity) { m_buffer = new char[defaultCapacity];}
		MemPage_t(size_t _capacity) : m_capacity(_capacity) { m_buffer = new char[_capacity];}
		virtual ~MemPage_t()  { delete[] m_buffer;}

		virtual size_t read(size_t _position, void* _buff, size_t _size);  // read from a specific position
		virtual size_t read(void* _buff, size_t _size);
		virtual size_t write(size_t _position, const void* _buff, size_t _size); // write from a specific position
		virtual size_t write(const void* _buff, size_t _size);
		
		bool IsFull() const { return m_capacity == GetSize();}
		size_t GetCapacity() const { return m_capacity;}
		static size_t GetDefaultCapacity() { return defaultCapacity;} 
		static size_t SetDefaultCapacity(size_t _capacity) // returns previous global capacity
		{
			size_t prev = defaultCapacity;
			defaultCapacity = _capacity;
			return prev;
		}
		
		//bool IsEmpty() const	{ return m_actualSize == 0;}
		//size_t GetPosition() const	{ return m_position;}
		//bool SetPosition(size_t _position)
		//size_t GetSize() const	{ return m_actualSize;}
	private:
		char* m_buffer;
		static size_t defaultCapacity;
		const size_t m_capacity;
		
		MemPage_t(const MemPage_t& _memPage); // copy CTOR
		const MemPage_t& operator = (const MemManager_t& _memPage);
		//void SetSize( size_t _size) { m_actualSize = _size;}
};

#endif /*__MEMPAGE_H__*/

