#include "memPage_t.h"

#include <string.h>

size_t MemPage_t::defaultCapacity = 6; // initalize static member

size_t MemPage_t::read(size_t _position, void* _buff, size_t _size)
{
	if(NULL == _buff || IsEmpty() || _position >= GetSize())
	{
		return 0;
	}
    size_t readable = 0;
    size_t nbytes = 0;
	
    readable = GetSize() - _position;
    nbytes = readable < _size ? readable : _size;
    
    memcpy((char*)_buff, m_buffer + _position, nbytes);
    SetPosition(_position + nbytes);
    return nbytes;
}

size_t MemPage_t::read(void* _buff, size_t _size)
{
    return read(GetPosition(), _buff, _size);
}

size_t MemPage_t::write(size_t _position, const void* _buff, size_t _size)
{
	size_t nbytes = 0;
    if(_buff == NULL || _position > GetSize())
    {
        return 0;
    }
    size_t freeSpace = m_capacity - _position;
    nbytes = freeSpace < _size ? freeSpace : _size;

    memcpy(m_buffer + _position, _buff , nbytes);
    
    size_t size = (_position + nbytes < GetSize() ? GetSize() : _position + nbytes);
    SetSize(size);
    SetPosition(_position + nbytes);

    return nbytes;
}

size_t MemPage_t::write(const void* _buff, size_t _size)
{
    return write(GetPosition(), _buff, _size);
}
