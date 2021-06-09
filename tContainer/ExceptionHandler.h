#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <string>
#include <iostream>
using namespace std;


template <class T>
class TException_t {
public:
	TException_t(const T& _t, const string& _file, size_t _line, const string& _text) {
		m_data = _t; 
		m_file = _file;
		m_text = _text;
		m_line = _line;
	}

	const	string& GetFileName()	const{ return m_file; } 	
	const	string& GetText()		const{ return m_text; } 	
	const T&		GetException() 	const{ return m_data; } 
	size_t			GetLineNum()	const{ return m_line; } 
private:
	T		m_data;
	string	m_file;
	size_t	m_line;
	string	m_text;
};


#endif //EXCEPTION_HANDLER_H
