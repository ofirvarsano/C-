#ifndef __MEMMANAGER_H__
#define __MEMMANAGER_H__
#include <stddef.h> //size_t

class MemManager_t
{
	public:
		MemManager_t() { m_position = 0; m_actualSize = 0;} 
		virtual ~MemManager_t(){};
		
		bool IsEmpty() const	{ return m_actualSize == 0;}
		size_t GetPosition() const	{ return m_position;}	//not virtual because the same for every one
		size_t GetSize() const	{ return m_actualSize;}
		
		virtual size_t read(size_t _position, void* _buff, size_t _size) = 0; // read from a specific position
		virtual size_t read(void* _buff, size_t _size) = 0; // read from a specific position pure virtual
		virtual size_t write(const void* _buff, size_t _size) = 0; // write to a specific position
		virtual size_t write(size_t _position, const void* _buff, size_t _size) = 0; // write to a specific position
		bool SetPosition(size_t _position)
		{
			if(_position <= m_actualSize)
			{
				m_position = _position;
				return true;
			}
			return false;
		}

	protected:
		//virtual dctor because this class will be derived
		void SetSize( size_t _size) { m_actualSize = _size;}
		
	private:
		size_t m_position;          // the position of the cursor
		size_t m_actualSize;              // the actual written size 

		MemManager_t(const MemManager_t& _memManager); // copy CTOR
		MemManager_t& operator = (const MemManager_t& _memManager); // assignmant 
};

#endif /* __MEMMANAGER_H__*/
