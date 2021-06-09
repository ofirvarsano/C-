#include <stdio.h>
#include <stdlib.h>

#include "string_t.h"

int main()
{
	String_t s1("hiii");
	String_t s2("123");
	String_t s3("hiii");
	String_t* s4 = new String_t();
	char* input;
	char b = '1';
	char c[] = "bye";
	input = c;
	s1.Print();
	printf("s1 length: %ld\n",s1.Length());
	s1.SetString(input);
	printf("%s\n",s1.GetString());
	
	printf("s1 length: %ld\n",s1.Length());
	printf("s2 length: %ld\n",s2.Length());
	printf("s4 length: %ld\n",s4->Length());
	printf("%d\n",s1.Compare(s2));
	printf("%d\n",s1.Compare(*s4));
	s1 = s2;
	printf("%d\n",s1.Compare(s2));
	*s4 = s1;
	s4->Print();
	printf("\n");
	cout << s1;
	printf("\n");
	s1[1] = b;
	cout << s1;
	printf("\n");
	printf("%c\n", s1[2]);

	delete s4;
	return 0;
}
