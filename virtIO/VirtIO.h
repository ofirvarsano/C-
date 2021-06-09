#ifndef VIRT_IO_H
#define VIRT_IO_H

#include <stdio.h>
#include "../ExceptionHandler.h"
using namespace std;

class VirtIO_t {
public:
	enum status_e {
		ok_e,
		cant_open_file_e,
		bad_access_e,
		writeErr_e,
		readErr_e
	};

	VirtIO_t();
	VirtIO_t(const char* _fileName, const char* _mode);
	virtual ~VirtIO_t() { Close(); }

	bool Open(const char* _fileName, const char* _mode);
	void Close();

	status_e		GetStatus() const	{ return m_status; }
	bool			SetPosition(size_t _pos);
	const string&	GetPath() const		{ return m_filename; }
	const string&	GetMode() const		{ return m_mode; }
	size_t			GetPosition() const	{ return (m_status == ok_e) ? ftell(m_file) : 0; }		
	size_t			Length() const;

	virtual VirtIO_t& operator << (char _c) 			= 0;
	virtual VirtIO_t& operator << (unsigned char _uc) 	= 0;
	virtual VirtIO_t& operator << (short _s)			= 0;
	virtual VirtIO_t& operator << (unsigned short _us)	= 0;
	virtual VirtIO_t& operator << (int _i) 				= 0;
	virtual VirtIO_t& operator << (unsigned int _ui)  	= 0;
	virtual VirtIO_t& operator << (long _l)  			= 0;
	virtual VirtIO_t& operator << (unsigned long _ul)	= 0;
	virtual VirtIO_t& operator << (float _f)  			= 0;
	virtual VirtIO_t& operator << (double _d) 			= 0;

	virtual VirtIO_t& operator >> (char& _c)			 = 0;
	virtual VirtIO_t& operator >> (unsigned char& _uc)	 = 0;
	virtual VirtIO_t& operator >> (short& _s)			 = 0;
	virtual VirtIO_t& operator >> (unsigned short& _us)	 = 0;
	virtual VirtIO_t& operator >> (int& _i)				 = 0;
	virtual VirtIO_t& operator >> (unsigned int& _ui)	 = 0;
	virtual VirtIO_t& operator >> (long& _l)			 = 0;
	virtual VirtIO_t& operator >> (unsigned long& _ul)	 = 0;
	virtual VirtIO_t& operator >> (float& _f)			 = 0;
	virtual VirtIO_t& operator >> (double& _d)			 = 0;


protected:
	bool		IsOpenForWrite() const;
	bool		IsOpenForRead() const;
	FILE*		GetFile() const						{ return m_file; }
	void		SetStatus(status_e _status) const	{ m_status = _status; }

private:
	mutable status_e	m_status;
	FILE*				m_file;
	string				m_mode;
	string				m_filename;

	VirtIO_t(const VirtIO_t&);
	VirtIO_t& operator = (const VirtIO_t&);
};

#endif //VIRT_IO_H

