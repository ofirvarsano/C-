#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

typedef map<string, int> StrIntMap;
	
bool cmp(const pair<string, int>& a, const pair<string, int>& b)
{
	return a.first.compare(b.first) < 0;
}

void countWords(istream& file, StrIntMap& words)
{
	string s;
	while (file >> s) 
	{
		++words[s];
	}
}       

int main(int argc, char** argv) {

	if(argc < 2)
	return 1;

	ifstream file(argv[1]);

	if(!file)
	exit(EXIT_FAILURE);

	StrIntMap wordMap;
	countWords(file, wordMap);

	sort(wordMap.begin(), wordMap.end(), cmp);
	
	for (StrIntMap::iterator itr = wordMap.begin(); itr != wordMap.end(); ++itr)
	{
		std::cout.width(16);
		cout << left << itr->first << left << itr->second << endl;
	}
	return 0;
}
