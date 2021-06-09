#include "Tokenizer.h"
#include "Analyzer.h"
#include "Parser.h"

Parser_t::Parser_t()
{
	m_tokenizer = new Tokenizer_t("()[]{};,<>=+-*&\n\t\v\f\r");
	m_analyzer = new Analyzer_t;
}
Parser_t::~Parser_t()
{
	delete m_tokenizer;
	delete m_analyzer;
}

void Parser_t::Compile(const string& _file)
{
	size_t lineCounter = 1;
	char line[256];
	m_file.open(_file.c_str());
	if(!m_file.good())
	{
		cout << "Error, can't open file" << endl;
		return;
	}

	cout << "**********************************" << endl;
	cout << "Compiling: "<< _file << endl;
	cout << "**********************************" << endl;
	while(!m_file.eof())
	{
		m_file.getline(line, 256);
		string newLine(line);

		if(newLine.size() == 1)
		{
			lineCounter += 1;
			continue;	
		}
	
		const vector<string>& tokens = m_tokenizer->Tokenize(newLine);
		m_analyzer->Analyze(tokens, lineCounter++);
	}
	m_analyzer->Summarize();
	m_file.close();
	cout << "**********************************" << endl;
}
