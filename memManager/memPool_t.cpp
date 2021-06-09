#include "memPool_t.h"
#include <iostream>

MemPool_t::MemPool_t()
{
    MemPage_t* memPage = new MemPage_t;
    vec.insert(vec.end(), memPage); 
}

size_t MemPool_t::read(size_t _position, void* _buff, size_t _size)
{
    size_t read = 0;
    if(_buff == NULL || _position >= GetSize())
    {
        return 0;
    }
    SetPosition(_position);
    size_t page = GetPage(GetPosition());
    
    size_t sizeVector = vec.size();
	
    while(sizeVector > page)
    {
        read += vec[page]->read((char*)_buff + read, _size -read);
        if(read == _size)
        {
            break;
        }
        page++;
        vec[page]->SetPosition(0);
    }
    
    SetPosition(_position + read);
    return read;
}

size_t MemPool_t::read(void* _buff, size_t _size)
{
    return read(GetPosition(), _buff, _size);
}


size_t MemPool_t::write(size_t _position, const void* _buff, size_t _size)
{
    size_t write = 0;
    if(_buff == NULL || _position > GetSize())
    {
        return 0;
    }
    SetPosition(_position);
    size_t page = GetPage(GetPosition());

    // write until we reach the _size
    size_t sizeVector = vec.size();
    while(1)
    {
        write += vec[page]->write((char*)_buff + write, _size - write);
        if(write == _size)
        {
            break;
        }
        // no more pages in the vector
        if(sizeVector == page + 1)
        {
            MemPage_t* memPage = new MemPage_t;
            vec.insert(vec.end(), memPage);
        }
        page++;
        vec[page]->SetPosition(0);
    }
    size_t size = (_position + write < GetSize() ? GetSize() : _position + write);
    SetSize(size);
    SetPosition(_position + write);
    
    return write;
}

size_t MemPool_t::write(const void* _buff, size_t _size)
{
    return write(GetPosition(), _buff, _size);
}

size_t MemPool_t::GetPage(size_t _position)
{
	size_t i = 0;
    size_t globalPosition = 0;
    size_t insidePosition = 0;
    for (i = 0; i < vec.size(); ++i)
    {
    	if((globalPosition + vec[i]->GetSize()) < _position)
    	{
    		globalPosition += vec[i]->GetSize();
    	}
    	else
    	{
            insidePosition = _position - globalPosition;
            ++i;
            break;
    	}
    }
    --i;
    vec[i]->SetPosition(insidePosition);
    return i;
}

MemPool_t::~MemPool_t() 
{
    vector<MemPage_t*>::iterator it = vec.begin();
    for(; it != vec.end(); ++it)
    {
        delete *it;
    }
}

