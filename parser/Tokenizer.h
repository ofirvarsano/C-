#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <iostream>
#include <vector>
#include <ctype.h>

using namespace std;

class Tokenizer_t
{
	public:
		Tokenizer_t(const string& _delimiters) : m_delimiters(_delimiters){}
		~Tokenizer_t() {}
		
		const vector<string>& Tokenize(string& _line);

	private:
		vector<string>	m_tokens;
		string			m_delimiters;
		bool IsDelimiter(char& _val);

		Tokenizer_t(const Tokenizer_t&) {}
		const Tokenizer_t& operator = (const Tokenizer_t&) {return *this;}
};


#endif //TOKENIZER_H
