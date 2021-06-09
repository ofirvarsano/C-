#ifndef BIN_IO_H
#define BIN_IO_H

#include <string>
#include "VirtIO.h"
using namespace std;

class BinIO_t : public VirtIO_t {
public:
	BinIO_t() {m_buf = 0 ; m_flag = no_buf_e;}
	BinIO_t(const char* _fileName, const char* _mode) : VirtIO_t(_fileName, _mode) {m_buf = 0 ; m_flag = no_buf_e;}
	virtual ~BinIO_t() {}

	virtual BinIO_t& operator << (char _c) 				{ return write(_c);}
	virtual BinIO_t& operator << (unsigned char _uc) 	{ return write(_uc);}
	virtual BinIO_t& operator << (short _s)				{ return write(_s);}
	virtual BinIO_t& operator << (unsigned short _us)	{ return write(_us);}
	virtual BinIO_t& operator << (int _i) 				{ return write(_i);}
	virtual BinIO_t& operator << (unsigned int _ui)  	{ return write(_ui);}
	virtual BinIO_t& operator << (long _l)  			{ return write(_l);}
	virtual BinIO_t& operator << (unsigned long _ul)	{ return write(_ul);}
	virtual BinIO_t& operator << (float _f)  			{ return write(_f);}
	virtual BinIO_t& operator << (double _d) 			{ return write(_d);}

	virtual BinIO_t& operator >> (char& _c)				 { return read(_c);}
	virtual BinIO_t& operator >> (unsigned char& _uc)	 { return read(_uc);}
	virtual BinIO_t& operator >> (short& _s)			 { return read(_s);}
	virtual BinIO_t& operator >> (unsigned short& _us)	 { return read(_us);}
	virtual BinIO_t& operator >> (int& _i)				 { return read(_i);}
	virtual BinIO_t& operator >> (unsigned int& _ui)	 { return read(_ui);}
	virtual BinIO_t& operator >> (long& _l)				 { return read(_l);}
	virtual BinIO_t& operator >> (unsigned long& _ul)	 { return read(_ul);}
	virtual BinIO_t& operator >> (float& _f)			 { return read(_f);}
	virtual BinIO_t& operator >> (double& _d)			 { return read(_d);}

	BinIO_t& operator << (const void* _buff)
	{
		if(GetStatus() == ok_e && IsOpenForWrite() && NULL != _buff)
		{
			m_buf = (void*)_buff;
			m_flag = write_e;
			return *this;
		}
		throw TException_t<int>(1, __FILE__, __LINE__, "Can't write");
	}

	BinIO_t& operator >> (void* _buff)
	{
		if(GetStatus() == ok_e && IsOpenForRead() && NULL != _buff)
		{
			m_buf = _buff;
			m_flag = read_e;
			return *this;
		}
		throw TException_t<int>(1, __FILE__, __LINE__, "Can't read");
	}

	void operator , (size_t _size)
	{
		if(m_flag == write_e)
		{
			if(0 == fwrite(m_buf, _size, 1, GetFile()))
			{
				//SetStatus(writeErr_e);
				throw TException_t<int>(1, __FILE__, __LINE__, "Write error");
			}
			m_flag = no_buf_e;
		}
		else if(m_flag == read_e)
		{
			if(0 == fread(m_buf, _size, 1, GetFile()))
			{
				//SetStatus(readErr_e);
				throw TException_t<int>(1, __FILE__, __LINE__, "Read error");
			}
			m_flag = no_buf_e;			
		}
	}

private:
	enum flag_e
	{
		write_e,
		read_e,
		no_buf_e
	};

	void*	m_buf;
	flag_e	m_flag;

	template <class T>
	BinIO_t& write(const T& _item)
	{
		*this << (const void*)&_item, sizeof(T);
		return *this;
	}

	template <class T>
	BinIO_t& read(T& _item)
	{
		*this >> (void*)&_item, sizeof(T);
		return *this;
	}

};

#endif //BIN_IO_H
