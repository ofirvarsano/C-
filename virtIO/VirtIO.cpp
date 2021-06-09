#include "VirtIO.h"

using namespace std;

VirtIO_t::VirtIO_t()
{
	m_file = NULL;
	m_status = cant_open_file_e;
}

VirtIO_t::VirtIO_t(const char* _fileName, const char* _mode)
{
	m_file = NULL;
	m_status = cant_open_file_e;
	Open(_fileName, _mode);
}

bool VirtIO_t::Open(const char* _fileName, const char* _mode)
{
	if(m_status == ok_e)
	{
		Close();
	}
	m_mode = "NO FILE";
	m_filename = "NO FILE";
	if(_fileName == NULL || _mode == NULL)
	{
		m_status = bad_access_e;
		return false;
	}
	
	m_file = fopen(_fileName, _mode);
	if(NULL == m_file)
	{
		m_status = cant_open_file_e;
		return false;
	}
	m_mode = _mode;
	m_filename = _fileName;
	m_status = ok_e;
	return true;
}

void VirtIO_t::Close()
{
	if(ok_e == m_status)
	{
		fclose(m_file);
		m_status = cant_open_file_e;
		m_mode = "NO FILE";
		m_filename = "NO FILE";
		m_file = NULL;	
	}
}

bool VirtIO_t::IsOpenForWrite() const
{
	size_t found1 = m_mode.find("a");
	size_t found2 = m_mode.find("w");
	size_t found3 = m_mode.find("+");
	return (found1 != string::npos) || (found2 != string::npos) || (found3 != string::npos);
}

bool VirtIO_t::IsOpenForRead() const
{
	size_t found1 = m_mode.find("r");
	size_t found2 = m_mode.find("+");
	return (found1 != string::npos) || (found2 != string::npos);
}

bool VirtIO_t::SetPosition(size_t _pos)
{
	if(m_status != ok_e)
	{
		return false;
	}
	if(_pos <= Length() && 0 == fseek(m_file, _pos, SEEK_SET))
	{
		return true;
	}
	return false;
}

size_t VirtIO_t::Length() const
{
	if(m_status != ok_e)
	{
		return 0;
	}
	size_t pos = ftell(m_file);
	fseek(m_file, 0, SEEK_END);
	size_t size = ftell(m_file);
	fseek(m_file, pos, SEEK_SET);

	return size;
}



