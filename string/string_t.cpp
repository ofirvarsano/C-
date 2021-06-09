#include <string.h>
#include <ctype.h>
#include "string_t.h"

const char none = '\0';
const size_t arrSize = 16;

size_t String_t::numOfStrings = 0;
unsigned int String_t::GlobalCapacity = 16;
bool String_t::CaseSensative = true;
unsigned int Power2_LUT[16] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768 };

String_t::String_t() //defult CTOR
{
	++numOfStrings;
	m_str = CreateFrom(0);
}

String_t::String_t(const char* _st) //CTOR with argument
{
	++numOfStrings;
	m_str = CreateFrom(_st);
} 

String_t::String_t(const String_t& _st) //copy CTOR
{
	++numOfStrings;
	m_str = (char*)CreateFrom(_st.GetString());
}

String_t::~String_t() //default DTOR
{
	--numOfStrings;
	delete[] m_str;
}

String_t& String_t::operator = (const String_t& _st) //assiment operator
{
	if(this != &_st)
	{
		if(strlen(_st.GetString() + 1) > Capacity)
		{
			delete[] m_str;
			CreateFrom(_st.GetString());
		}
		else
		{
			strcpy(m_str, _st.GetString());
		}
	}
	return *this;
}

static unsigned int GetNewCap(unsigned int _size)
{
	int i = 0;
	while(Power2_LUT[i++] < _size && i < arrSize);
	return Power2_LUT[i - 1];
}

char* String_t::CreateFrom(const char* _st)
{
	char* tmp;
	if(_st == NULL)
	{
		tmp = new char[GlobalCapacity];
		tmp[0] = '\0';
		Capacity = GlobalCapacity;
	}
	else
	{
		Capacity = GetNewCap(strlen(_st) + 1);
		tmp = new char[Capacity];
		strcpy(tmp, _st);
	}
	return tmp;	
}

void String_t::SetString(const char* _st)
{
	if(strlen(_st + 1) > Capacity)
	{
		delete[] m_str;
		m_str = CreateFrom(_st);
		return;
	}
	strcpy(m_str, _st);
}

String_t::Result String_t::Compare(const String_t& _str) const
{
	int result;
	if(CaseSensative)
	{
		result = strcmp(m_str, _str.GetString());
	}
	else
	{
		result = strcasecmp(m_str, _str.GetString());	
	}
	return !result ? EQUAL : result > 0 ? GREATER : SMALLER;
}

void String_t::Print() const
{
	printf("%s\n", m_str);
}

String_t& String_t::UpperCase()
{
	char* i = m_str;
	while(*i)
	{
		char c = *i;
		*i++ = toupper(c);
	} 
	return *this;
}

String_t& String_t::LowerCase()
{
	char* i = m_str;
	while(*i)
	{
		char c = *i;
		*i++ = tolower(c);
	} 
	return *this;
}

String_t& String_t::Prepend(const char* _str)
{
	if(_str != NULL)
	{
		char* tmp = new char[strlen(_str) + Length() + 1];
		sprintf(tmp, "%s%s", _str , m_str);
		if(strlen(tmp + 1) > Capacity)
		{
			delete[] m_str;
			CreateFrom(tmp);
		}
		else
		{
			strcpy(m_str, tmp);
		}
		delete[] tmp;
	}
	return *this;
}

String_t& String_t::Prepend(const String_t& _str)
{
	char* tmp = new char[_str.Length() + Length() + 1];
	sprintf(tmp, "%s%s", _str.GetString() , m_str);
	if(strlen(tmp + 1) > Capacity)
	{
		delete[] m_str;
		CreateFrom(tmp);
	}
	else
	{
		strcpy(m_str, tmp);
	}
	delete[] tmp;
	return *this;
}

String_t& String_t::operator += (const char* _str)
{
	if(_str != NULL)
	{
		char* tmp = new char[strlen(_str) + Length() + 1];
		sprintf(tmp, "%s%s", m_str, _str);
		if(strlen(tmp + 1) > Capacity)
		{
			delete[] m_str;
			CreateFrom(tmp);
		}
		else
		{
			strcpy(m_str, tmp);
		}
		delete[] tmp;
	}
	return *this;
}

String_t& String_t::operator += (const String_t& _str)
{
	char* tmp = new char[_str.Length() + Length() + 1];
	sprintf(tmp, "%s%s", m_str, _str.GetString());
	if(strlen(tmp + 1) > Capacity)
	{
		delete[] m_str;
		CreateFrom(tmp);
	}
	else
	{
		strcpy(m_str, tmp);
	}
	delete[] tmp;
	return *this;
}


bool String_t::operator > (const String_t& _str) const
{
	return Compare(_str) == GREATER;
}

bool String_t::operator < (const String_t& _str) const
{
	return Compare(_str) == SMALLER;
}

bool String_t::operator >= (const String_t& _str) const
{
	return Compare(_str) != SMALLER;
}

bool String_t::operator <= (const String_t& _str) const
{
	return Compare(_str) != GREATER;
}

bool String_t::operator == (const String_t& _str) const
{
	return Compare(_str) == EQUAL;
}

bool String_t::operator != (const String_t& _str) const
{
	return Compare(_str) != EQUAL;
}

bool String_t::Contains(const String_t& _st) const
{
	String_t a = *this, b = _st;
	if(CaseSensative)
	{
		return strstr(m_str, _st.GetString()) == NULL ? false : true;
	}
	else
	{
		a.UpperCase();		
		b.UpperCase();
		return strstr(a.GetString(), b.GetString()) == NULL ? false : true;
	}
}

const char& String_t::operator [] (size_t _index) const
{
	return _index < Length() ? m_str[_index] : none;	
}

char& String_t::operator [] (size_t _index)
{
	return _index < Length() ? m_str[_index] : *CreateFrom(NULL);	
}

ostream& operator << (ostream& _os, const String_t& _str)
{
	_os << _str.GetString();
	return _os;
}

istream& operator >> (istream& _is, String_t& _str)
{
	char tmp[256];
	_is >> tmp;
	_str.SetString(tmp);
	return _is;
}

int String_t::FirstOccurrence(const char _c) const
{
	char* index = strchr(m_str, _c);
	return index == NULL ? -1 : index - m_str;
}

int String_t::LastOccurrence(const char _c) const
{
	char* index = strrchr(m_str, _c);
	return index == NULL ? -1 : index - m_str;
}

unsigned int String_t::CapacitySet(unsigned int _newSize)
{
	unsigned int old = GlobalCapacity;
	GlobalCapacity = GetNewCap(_newSize);
	return old;
}

String_t String_t::operator()(unsigned int start, unsigned int len) const
{
	String_t newStr;
	if (start > Length() || start + len > Length())
	{
		return newStr;
	}
	
	char* tmp = new char[len + 1];
	if(start + len < Length())
	{
		strncpy(tmp, m_str + start, len);
		tmp[len] = 0;
		newStr.SetString(tmp);
	}
	delete[] tmp;
	return newStr;
}

