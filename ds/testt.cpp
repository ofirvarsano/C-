#include <stdio.h>
#include <iostream>
int main() {
	const int i = 11;
	int *p = const_cast<int*>(&i);
	
	*p = 17;
	
	printf("%d", i);
	printf("%d", *p);
	
	std::cout << std::endl << *p << i << std::endl;
	return 0;
}
