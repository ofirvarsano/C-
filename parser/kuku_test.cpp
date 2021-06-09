#include "Parser.h"
#include "Tokenizer.h"
#include "Analyzer.h"

using namespace std;

int main(int argc, char* argv[])
{
	Parser_t p;
	for(int i = 1 ; i < argc; ++i)
	{
		p.Compile(argv[i]);
	}

	return 0;
}
