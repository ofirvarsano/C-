#include <iostream>
#include <string>
#include <typeinfo>
#include "VirtIO.h"
#include "AsciiIO.h"
#include "BinIO.h"
using namespace std;

template <class T>
void ExceptionHandler(const TException_t<T>& _ex)
{
	cout << _ex.GetText() << ". Exception: " << _ex.GetException() << endl;
	cout << "File: " << _ex.GetFileName() << ". Line: " << _ex.GetLineNum() << endl;	
}

void Test(VirtIO_t& _file)
{
	int 	flag = 1;			// trigger to stop loop	
	int 	option, option2, i, i1;
	size_t	pos;
	char 	c, c1;
	short	s, s1;
	long	l, l1;
	double	d, d1;
	char filename[32], access[4];

	BinIO_t* bin = dynamic_cast<BinIO_t*>(&_file);

	while (flag)
	{
		cout << endl << "Choose option: " << endl;
		cout << "1: Open file  " << endl;
		cout << "2: Close file    " << endl;
		cout << "3: Set position  " << endl;
		cout << "4: Get position  " << endl;
		cout << "5: Get PATH  " << endl;
		cout << "6: Get access" << endl;
		cout << "7: Get file length  " << endl;
		cout << "8: Write to file" << endl;
		cout << "9: Read from file" << endl;
		cout << "Any another number - Exit " << endl << endl;

		cin >>  option;
		switch (option)
		{
			case 1:
				cout << "Enter filename and access:" << endl;
				cin >> filename >> access;
				cout << (_file.Open(filename, access) ? "File opened" : "Cannot open file") << endl;
				break;
				
			case 2:
				_file.Close();
				cout << "File closed" << endl << endl;
				break;
				
			case 3:
				cout << "Enter new position:" << endl;
				cin >> pos;
				cout << (_file.SetPosition(pos) ? "Position set" : "Cannot set position") << endl;
				break;
				
			case 4:
				cout << "Current position: " << _file.GetPosition() << endl << endl;				
				break;
				
			case 5:
				cout << "Path: " << _file.GetPath() << endl << endl;				
				break;
				
			case 6:
				cout << "Access: " << _file.GetMode() << endl << endl;				
				break;
				
			case 7:
				cout << "File length: " << _file.Length() << endl << endl;	
				break;
				
			case 8:
				cout << "Choose type to write:" << endl;
				cout << "1: char  " << endl;
				cout << "2: short    " << endl;
				cout << "3: int  " << endl;
				cout << "4: long  " << endl;
				cout << "5: double  " << endl;
				cout << "6: Binary: write buffer  " << endl;
				cout << "Any another number - stop " << endl << endl;
				cin >> option2;
				try {
					switch (option2)
					{
						case 1:
							cout << "Enter char:" << endl;
							cin >> c;
							_file << c;
							break;
							
						case 2:
							cout << "Enter short:" << endl;
							cin >> s;
							_file << s;
							break;
							
						case 3:
							cout << "Enter int:" << endl;
							cin >> i;
							_file << i;
							break;
							
						case 4:
							cout << "Enter long:" << endl;
							cin >> l;
							_file << l;
							break;
							
						case 5:
							cout << "Enter double:" << endl;
							cin >> d;
							_file << d;
							break;
							
						case 6:
							if(bin != 0)
							{
								double w;
								cout << "Enter ant double :" << endl;
								cin >> w;
								*bin << &w, sizeof(double);			
							}
							break;
							
						default: break;
					}
				}
				catch (TException_t<int> ex) { ExceptionHandler(ex);  break;}
				
				if(bin == 0) 
				{
					_file << ' ';
				}
				break;
			case 9:
				cout << "Choose type to read:" << endl;
				cout << "1: char  " << endl;
				cout << "2: short    " << endl;
				cout << "3: int  " << endl;
				cout << "4: long  " << endl;
				cout << "5: double  " << endl;
				cout << "6: Binary: read buffer  " << endl;
				cout << "Any another number - Exit " << endl << endl;
				cin >> option2;
				try {
					switch (option2)
					{
						case 1:
							_file >> c1;
							cout << "Read char: " << c1 << endl << endl;
							break;
							
						case 2:
							_file >> s1;
							cout << "Read short: " << s1 << endl << endl;
							break;
							
						case 3:
							_file >> i1;
							cout << "Read int: " << i1 << endl << endl;
							break;
							
						case 4:
							_file >> l1;
							cout << "Read long: " << l1 << endl << endl;
							break;
							
						case 5:
							_file >> d1;
							cout << "Read double: " << d1 << endl << endl;
							break;
							
						case 6:
							if(bin != 0)
							{
								/*
								size_t length;
								char buf[64];
								cout << "Enter buffer length:" << endl;
								cin >> length;
								*bin >> (void*)buf, length;
								buf[length] = '\0';
								cout << buf <<endl << endl;		
								*/
								double r;
								*bin >> &r, sizeof(double);
								cout << "void* read : " << r <<endl << endl;		
							}
							break;
							
						default: break;
					}
				}
				catch (TException_t<int> ex) { ExceptionHandler(ex); break;}
				
				break;
				
			default: 	
				flag = 0;
				break;
		}
	}
}

int main()
{
	int option;
	VirtIO_t* IO = NULL;
	char path[20], mode[10];
	//AsciiIO_t	ascii;
	//BinIO_t		bin;
	cout << "Choose option: " << endl;
	cout << "1: Test with AsciiIO  " << endl;
	cout << "2: Test with BinaryIO   " << endl;
	cout << "Any another number - Exit " << endl << endl;
	cin >>  option;
	cout << "please enter a path and mode"<< endl;
    cin >> path >> mode;
	switch (option) {
		case 1:
			IO = new AsciiIO_t(path, mode);
			break;
		case 2:
			IO = new BinIO_t(path, mode);
			break;
		default: 
			break;
	}
	Test(*IO);
	delete IO;
	
	return 0;
}
