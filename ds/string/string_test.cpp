#include <stdio.h>
#include <stdlib.h>

#include "string.h"

int main()
{
	experis::String s1("abc");
	const experis::String s2("def");
	experis::String s3(s1);
	experis::String s4;
	
	std::cout << s3 << std::endl;
	std::cout << s1.Length() << std::endl;
	std::cout << s1.AsCString() << std::endl;
	
	s3 = s2;
	std::cout << s3 << std::endl;
	std::cout << s4 << std::endl;
	s3 = "Hello";
	
	std::cout << s3 << std::endl;
	
	std::cout << s1[1] << std::endl;
	std::cout << s2[1] << std::endl;
	s1[2] = 'e';
	
	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
	
	std::cout << (s1 == s2 ? "yes" : "no") << std::endl;
	std::cout << (s2 == "abc" ? "yes" : "no") << std::endl;
	std::cout << ("abc" == s2 ? "yes" : "no") << std::endl;
	std::cout << ("abe" == s1 ? "yes" : "no") << std::endl;
	
	return 0;
}
