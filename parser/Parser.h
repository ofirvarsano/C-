#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include <iostream>
using namespace std;
class Tokenizer_t;
class Analyzer_t;

class Parser_t
{
	public:
		Parser_t();
		~Parser_t();
		void Compile(const string& _file);
		
	private:
		Tokenizer_t* m_tokenizer;
		Analyzer_t* m_analyzer;
		ifstream  m_file;
};


#endif //PARSER_H
