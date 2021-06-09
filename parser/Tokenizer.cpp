#include "Tokenizer.h"

const vector<string>& Tokenizer_t::Tokenize(string& _line)
{
	m_tokens.clear();
	for(size_t i = 0 ; i < _line.size() ; ++i)
	{
		string token;
		size_t length = 0, start = i;
		while(!IsDelimiter(_line[i]) && i < _line.size() && 0 == isspace(_line[i]))
		{
			length += 1;
			i += 1;
		}

		if(length > 0)
		{
			token = _line.substr(start, length);
			m_tokens.push_back(token);
			token.clear();
		}

		if(i < _line.size() && 0 == isspace(_line[i]))
		{
			token = _line.substr(i, 1);
			m_tokens.push_back(token);
			token.clear();
		}
	}
	return m_tokens;
}

bool Tokenizer_t::IsDelimiter(char& _val)
{
	return  string::npos != m_delimiters.find_first_of(_val);
}











