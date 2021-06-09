#ifndef ANALYZER_H
#define ANALYZER_H

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <ctype.h>

using namespace std;

class Analyzer_t {
public:
	Analyzer_t();
	virtual ~Analyzer_t() {}
	
	virtual void	Analyze(const vector<string>& _tokens, size_t _lineNum);
	virtual void	Summarize();

protected:
	size_t			m_lineNum;
	set<string>		m_names;
	set<string>		m_operators;
	set<string>		m_types;
	set<string>		m_keyWords;
	string			m_brackets;
	string			m_lastToken;
	bool			m_ifFlag;
	bool			m_mainFlag;
	bool			m_typeFlag;
	bool			m_operatorFlag;
	bool			m_opErrOccur;

	virtual bool	IsLegalName(const string& _word) { return (isalpha(_word[0]) || _word[0] == '_'); }
	virtual bool	AnalyzeWord(const string& _token);
	virtual bool	AnalyzeOperator(const string& _token);
	virtual bool	AnalyzeType(const string& _token);
	virtual bool	AnalyzeBracket(const string& _token);
	virtual bool	AnalyzeIfElse(const string& _token);
	virtual bool	IsNameExist(const string& _name);
	virtual bool	IsKeyWord(const string& _name);
	virtual bool	IsOperator(const string& _word);
	virtual bool	IsType(const string& _word);
	virtual bool	IsOpenBracket(const string& _b);
	virtual bool	IsCloseBracket(const string& _b);
	virtual bool	FindAndDeleteBracket(const string& _b);
	Analyzer_t(const Analyzer_t&) {}
	const Analyzer_t& operator = (const Analyzer_t&) {return *this;}
	
	static string KeyWords[];
	static string Operators[];
	static string Types[];
};


#endif //ANALYZER_H
