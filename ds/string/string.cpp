#include "string.h"
#include <string.h>
#include <stdio.h>

const char none = '\0';

using namespace std;

namespace experis {

String::String()
: m_len(0)
,m_str(createFrom(NULL, 0)) {}

String::String(const char* a_st)
: m_len(a_st ? strlen(a_st) : 0)
,m_str(createFrom(a_st, m_len)) {}

String::~String() {
	delete[] m_str;
}

String::String(const String& a_st)
: m_len(a_st.m_str ? strlen(a_st.m_str) : 0)
,m_str((char*)createFrom(a_st.m_str, m_len)) {}

char* String::createFrom(const char* a_st, size_t a_len) {
	char* newStr = new char[a_len + sizeof('\0')];
	strcpy(newStr, a_st ? a_st : "");

	return newStr;
}

String& String::operator=(const String& a_st) {
	char* tmp = createFrom(a_st.m_str, a_st.Length());
	delete[] m_str;
	m_str = tmp;
	m_len = a_st.Length();
	
	return *this;
}

const char& String::operator[](size_t a_index) const {
	return a_index < Length() ? m_str[a_index] : none;	
}

char& String::operator[](size_t a_index) {
	return a_index < Length() ? m_str[a_index] : *createFrom(NULL, 0);	
}

ostream& operator<<(ostream& a_os, const String& a_str) {
	a_os << a_str.AsCString();
	return a_os;
}

bool experis::String::operator==(const String& a_str) const {
	return strcmp(m_str, a_str.AsCString()) == 0;
}

bool operator==(const char* a_str1, const String& a_str2) {
	return strcmp(a_str1, a_str2.AsCString()) == 0;
}

} // experis

