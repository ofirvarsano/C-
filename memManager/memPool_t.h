#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

#include <vector>

using namespace std;

#include "memManager_t.h"
#include "memPage_t.h"

class MemPool_t:public MemManager_t
{
	public:
		MemPool_t();
		virtual ~MemPool_t();
		
		virtual size_t read(size_t _position, void* _buff, size_t _size);  
		virtual size_t read(void* _buff, size_t _size);
		virtual size_t write(size_t _position, const void* _buff, size_t _size); 
		virtual size_t write(const void* _buff, size_t _size);
		
		static size_t GetPageSize(size_t _size)
		{ 
		    return MemPage_t::GetDefaultCapacity(); 
		}
		static size_t SetPageSize(size_t _size) // returns previous global capacity
		{ 
		    return MemPage_t::SetDefaultCapacity(_size); 
		}
		//bool IsEmpty() const	{ return m_actualSize == 0;}
		//size_t GetPosition() const	{ return m_position;}
		//bool SetPosition(size_t _position)
		//size_t GetSize() const	{ return m_actualSize;}
		
	private:
		vector<MemPage_t*> vec;
		size_t GetPage(size_t _position);
		MemPool_t(const MemPool_t&);
		const MemPool_t& operator = (const MemPool_t&);
		//void SetSize( size_t _size) { m_actualSize = _size;}
};

#endif /*__MEMPOOL_H__*/

