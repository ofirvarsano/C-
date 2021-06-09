#include "Analyzer.h"

string Analyzer_t::KeyWords[] = {"if", "else", "for" , "while", "class", "private", "public", "protected", "main", "const", "virtual"};

string Analyzer_t::Operators[] = {"=", "+", "-", "*", "&", "<", ">", ",", ";"};

string Analyzer_t::Types[] = { "char", "short", "int", "long", "float", "double", "void" };

Analyzer_t::Analyzer_t() :	m_operators(Operators, Operators + sizeof(Operators) / sizeof(Operators[0])),
							m_types(Types, Types + sizeof(Types) / sizeof(Types[0])),
							m_keyWords(KeyWords, KeyWords + sizeof(KeyWords) / sizeof(KeyWords[0]))
{
	m_ifFlag = false; m_mainFlag = true;
	m_typeFlag = false; m_operatorFlag = false; m_opErrOccur = false;
}

void Analyzer_t::Analyze(const vector<string>& _tokens, size_t _lineNum)
{
	size_t i;
	if(m_mainFlag && _tokens[0] != "main")
	{
		cout << "Line "<< _lineNum <<": error, file must begin with 'main'" << endl;
		m_mainFlag = false;
	}

	for(i = 0 ; i < _tokens.size() ; ++i)
	{
		m_lastToken = i > 0 ? _tokens[i-1] : m_lastToken;
		m_lineNum = _lineNum;

		if(AnalyzeIfElse(_tokens[i])) continue;

		if(AnalyzeBracket(_tokens[i])) continue;

		if(AnalyzeType(_tokens[i])) continue;

		m_typeFlag = IsType(_tokens[i]) ? true : false;

		if(AnalyzeOperator(_tokens[i])) continue;

		if(AnalyzeWord(_tokens[i])) continue;

		m_lastToken = _tokens[i];
	}
}

void Analyzer_t::Summarize()
{
	int countb1 = 0, countb2 = 0, countb3 = 0;
	size_t i = 0;
	for(i = m_brackets.find('('); i != string::npos; i = m_brackets.find('(',i + 1))
	{
		++countb1;
	}
	if(countb1)
	cout << "Error: no closing bracket for " << countb1 << " '('" << endl;

	for(i = m_brackets.find('{'); i != string::npos; i = m_brackets.find('{',i + 1))
	{
		++countb2;
	}
	if(countb2)
	cout << "Error: no closing bracket for " << countb2 << " '{'" << endl;

	for(i = m_brackets.find('['); i != string::npos; i = m_brackets.find('[',i + 1))
	{
		++countb3;
	}
	if(countb3)
	cout << "Error: no closing bracket for " << countb3 << " '['" << endl;

	m_brackets.clear();
	m_names.clear();
	m_ifFlag = false; m_mainFlag = true;
	m_typeFlag = false; m_operatorFlag = false;
}

bool Analyzer_t::IsKeyWord(const string& _word)
{
	return m_keyWords.end() != m_keyWords.find(_word);
}

bool Analyzer_t::IsOperator(const string& _word)
{
	return m_operators.end() != m_operators.find(_word);
}

bool Analyzer_t::IsType(const string& _word)
{
	return m_types.end() != m_types.find(_word);
}

bool Analyzer_t::IsNameExist(const string& _name)
{
	return m_names.end() != m_names.find(_name);
}

bool Analyzer_t::IsOpenBracket(const string& _b)
{
	return (_b == "(" || _b == "[" || _b == "{");
}

bool Analyzer_t::IsCloseBracket(const string& _b)
{
	return (_b == ")" || _b == "]" || _b == "}");
}

bool Analyzer_t::FindAndDeleteBracket(const string& _b)
{
	string br;
	if(_b == ")")
		br = "(";
	else if(_b == "]")
		br = "[";
	else if(_b == "}")
		br = "{";

	size_t pos = m_brackets.find_first_of(br);
	return (pos != string::npos) ? m_brackets.erase(pos, 1), true : false;
}

bool Analyzer_t::AnalyzeIfElse(const string& _token)
{
	if("else" == _token)
	{
		if(!m_ifFlag)
		{
			cout << "Line " << m_lineNum << ": error, else witout if" << endl;
		}
		else
		{
			m_ifFlag = false;
		}
		return true;
	}
	else if("if" == _token)
	{
		m_ifFlag = true;
		return true;
	}
	return false;
}

bool Analyzer_t::AnalyzeBracket(const string& _token)
{
	if(IsOpenBracket(_token))
	{
		m_brackets += _token;
		return true;
	}
	else if(IsCloseBracket(_token))
	{
		if(!FindAndDeleteBracket(_token))
		{
			cout << "Line " << m_lineNum << ": error, no matching open bracket for: '" << _token << "'" << endl;
		}
		return true;
	}
	return false;
}

bool Analyzer_t::AnalyzeType(const string& _token)
{
	if(m_typeFlag)
	{
		if(!IsLegalName(_token))
		{
			cout << "Line " << m_lineNum << ": error, '" << _token << "' is not a legal name" << endl;
		}
		else if(IsNameExist(_token))
		{
			cout << "Line " << m_lineNum << ": error, '" << _token << "' is a occupied name" << endl;
		}
		else if(IsKeyWord(_token))
		{
			cout << "Line " << m_lineNum << ": error, '" << _token << "' keyword can't be a type name" << endl;
		}
		else if(IsType(_token))
		{
			cout << "Line " << m_lineNum << ": error, multiple type declaration" << endl;
		}
		else
		{
			m_names.insert(_token);
		}
		m_typeFlag = false;
		return true;
	}
	return false;
}

bool Analyzer_t::AnalyzeOperator(const string& _token)
{
	if(IsOperator(_token))
	{
		if(_token != m_lastToken)
		{
			m_operatorFlag = false;
			m_opErrOccur = false;
		}
		else if(!m_operatorFlag && _token == m_lastToken && !m_opErrOccur)
		{
			m_operatorFlag = true;
		}
		else if(m_operatorFlag && _token == m_lastToken && (_token == "+" || _token == "-"))
		{
			cout << "Line " << m_lineNum << ": error, '" << _token <<  _token <<  _token << "' illigal operator" << endl;
			m_operatorFlag = false;
			m_opErrOccur = true;
		}
		else
		{
			m_opErrOccur = false;
		}
		m_lastToken = _token;
		return true;
	}
	return false;
}

bool Analyzer_t::AnalyzeWord(const string& _token)
{
	if(!m_typeFlag && !IsKeyWord(_token) && !IsOperator(_token))
	{
		if(!IsLegalName(_token))
		{
			cout << "Line " << m_lineNum << ": error, '" << _token << "' is not a legal name" << endl;
		}
		else if(!IsNameExist(_token))
		{
			cout << "Line " << m_lineNum << ": error, '" << _token << "' not defined" << endl;
		}
		m_lastToken = _token;
		return true;
	}
	return false;
}
