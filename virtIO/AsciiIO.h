#ifndef ASCII_IO_H
#define ASCII_IO_H

#include <string>
#include <typeinfo>
#include "VirtIO.h"
using namespace std;

class AsciiIO_t : public VirtIO_t {
public:
	AsciiIO_t() {}
	AsciiIO_t(const char* _fileName, const char* _mode) : VirtIO_t(_fileName, _mode) {}
	virtual ~AsciiIO_t() {}

	virtual AsciiIO_t& operator << (char _c) 			{ return write(_c, "%c");}
	virtual AsciiIO_t& operator << (unsigned char _uc) 	{ return write(_uc, "%c");}
	virtual AsciiIO_t& operator << (short _s)			{ return write(_s, "%hi");}
	virtual AsciiIO_t& operator << (unsigned short _us)	{ return write(_us, "%hu");}
	virtual AsciiIO_t& operator << (int _i) 			{ return write(_i, "%d");}
	virtual AsciiIO_t& operator << (unsigned int _ui)  	{ return write(_ui, "%u");}
	virtual AsciiIO_t& operator << (long _l)  			{ return write(_l, "%li");}
	virtual AsciiIO_t& operator << (unsigned long _ul)	{ return write(_ul, "%lu");}
	virtual AsciiIO_t& operator << (float _f)  			{ return write(_f, "%f");}
	virtual AsciiIO_t& operator << (double _d) 			{ return write(_d, "%lf");}

	virtual AsciiIO_t& operator >> (char& _c)			 { return read(_c, "%c");}
	virtual AsciiIO_t& operator >> (unsigned char& _uc)	 { return read(_uc, "%c");}
	virtual AsciiIO_t& operator >> (short& _s)			 { return read(_s, "%hi");}
	virtual AsciiIO_t& operator >> (unsigned short& _us) { return read(_us, "%hu");}
	virtual AsciiIO_t& operator >> (int& _i)			 { return read(_i, "%d");}
	virtual AsciiIO_t& operator >> (unsigned int& _ui)	 { return read(_ui, "%u");}
	virtual AsciiIO_t& operator >> (long& _l)			 { return read(_l, "%li");}
	virtual AsciiIO_t& operator >> (unsigned long& _ul)	 { return read(_ul, "%lu");}
	virtual AsciiIO_t& operator >> (float& _f)			 { return read(_f, "%f");}
	virtual AsciiIO_t& operator >> (double& _d)			 { return read(_d, "%lf");}

private:
	template <class T>
	AsciiIO_t& write(const T& _item, const char* _format)
	{
		if(GetStatus() == ok_e && IsOpenForWrite())
		{
			int nBytes = fprintf(GetFile(), _format, _item);
			if(nBytes <= 0)
			{
				SetStatus(writeErr_e);
				throw TException_t<T>(_item, __FILE__, __LINE__, "Write error");
			}
			return *this;
		}
		throw TException_t<T>(_item, __FILE__, __LINE__, "Can't write");
		//return *this;
	}

	template <class T>
	AsciiIO_t& read(T& _item, const char* _format)
	{
		if(GetStatus() == ok_e && IsOpenForRead() && GetPosition() < Length())
		{
			int nBytes = fscanf(GetFile(), _format, &_item);
			if(nBytes <= 0)
			{
				SetStatus(readErr_e);
				throw TException_t<T>(_item, __FILE__, __LINE__, "Read error");
			}
			fseek(GetFile(), ftell(GetFile()) + 1, SEEK_SET);
			return *this;
		}
		throw TException_t<T>(_item, __FILE__, __LINE__, "Can't read");
		//return *this;
	}

};

#endif //ASCII_IO_H
