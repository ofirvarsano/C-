#ifndef STRING_H
#define STRING_H

#include <iostream>

namespace experis {

class String {
public:
	String();
	String(const String& a_st);
	String(const char* a_st);
	~String();
	String& operator=(const String& a_st);
	
	const char& operator[](size_t a_index) const;
	char& operator[](size_t a_index);
	bool operator==(const String& a_str) const;
	
	const char* AsCString() const { return m_str; }
	size_t Length() const { return m_len; }
	
private:
	char* createFrom(const char* a_st, size_t a_len);
	
	size_t m_len; //MUST be before m_str
	char* m_str;
};

std::ostream& operator<<(std::ostream& a_os, const String& a_str);
bool operator==(const char* a_str1, const String& a_str);

} // experis

#endif //STRING_H
