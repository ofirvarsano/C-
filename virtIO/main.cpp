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

void printMenu();
void writeTest(VirtIO_t& _file);
void ReadTest(VirtIO_t& _file);

void Test(VirtIO_t& _file)
{
    int choice = -1;
    char c;
    size_t	pos;
    char filename[32], access[4];
    
    while(choice != 0)
    {
        printMenu();
        cin >> c;

        switch(c)
        {
        	case 'o':
        		cout << "Enter filename and access : " << endl;
				cin >> filename >> access;
				cout << (_file.Open(filename, access) ? "File opened" : "Cannot open file") << endl;
        		break;
        		
        	case 'c':
        		_file.Close();
				cout << "File closed" << endl << endl;
				break;
        		
            case '<':
                writeTest(_file);
                break;
            
            case '>':
                ReadTest(_file);
                break;
                
            case 'g':
                cout << "Current position : " << _file.GetPosition() << endl << endl;				
				break;
                
			case 'm':
               	cout << "Mode : " << _file.GetMode() << endl << endl;				
				break;
               	
            case 's':
                cout << "Enter new position:" << endl;
				cin >> pos;
				cout << (_file.SetPosition(pos) ? "Position set" : "Cannot set position") << endl;
				break;
            
            case 'l':
                cout << "File length: " << _file.Length() << endl << endl;	
				break;
                
            default:
                choice = 0;
                break;
        }
    }
}


int main()
{
	int option;
	VirtIO_t* IO = NULL;
	char path[20], mode[10];
	cout << "Choose option: " << endl;
	cout << "1: Test with AsciiIO  " << endl;
	cout << "2: Test with BinaryIO   " << endl;
	cout << "Any another number - Exit " << endl << endl;
	cin >>  option;
	cout << "please enter a file name and mode"<< endl;
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

template<class T>
void write(VirtIO_t& _file)
{
    T value;
    cout << "enter value" << endl;
    try
    {
    	cin >> value;
        _file << value << ' ';
    }
    catch (TException_t<T> ex) { ExceptionHandler(ex); }
    catch(...) {}
}

template<class T>
void Read(VirtIO_t& _file)
{
    T value;
    
	try
	{
	    _file >> value;
	    cout << "the value is: " << value << endl; 
	}
	catch (TException_t<T> ex) { ExceptionHandler(ex); }
	catch(...) {}
}

void ReadVoidP(VirtIO_t& _file)
{
    double value;
    BinIO_t* binIO = dynamic_cast< BinIO_t*>(&_file);
    if(binIO)
    {
        try
        {
            *binIO >> &value, sizeof(double) ;
            cout << "void* read : " << value << endl;
        }
        catch (TException_t<int> ex) { ExceptionHandler(ex); } 
    }
}

void WriteVoidP(VirtIO_t& _file)
{
    double value;
    BinIO_t* binIO = dynamic_cast< BinIO_t*>(&_file);
    if(binIO)
    {
        cout << "enter any double : " << endl;
        cin >> value;
        try
        {
            *binIO << &value, sizeof(double) ;
        }
        catch (TException_t<int> ex) { ExceptionHandler(ex); } 
    }
}
void ReadTest(VirtIO_t& _file)
{
    char c;
    cout <<"******************************************************************" << endl;
    cout << " (i)nt | (c)har | (s)hort | (l)ong | (f)loat | (d)ouble | (v)oid*" <<endl;
    cin >> c;
    switch(c)
    {
        case 'i':
            Read<int>(_file);
            break;
        case'c':
            Read<char>(_file);
            break;
        case 's':
            Read<short>(_file);
            break;
        case 'l':
            Read<long>(_file);
            break;
        case 'f':
            Read<float>(_file);
            break;
        case 'd':
            Read<double>(_file);
            break;
        case 'v':
            ReadVoidP(_file);
            break;
        default :
            break;
    }
}

void writeTest(VirtIO_t& _file)
{
    char c;
    cout <<"******************************************************************" << endl;
    cout << " (i)nt | (c)har | (s)hort | (l)ong | (f)loat | (d)ouble | (v)oid*" <<endl;
    cin >> c;
    switch(c)
    {
        case 'i':
            write<int>(_file);
            break;
        case'c':
            write<char>(_file);
            break;
        case 's':
            write<short>(_file);
            break;
        case 'l':
            write<long>(_file);
            break;
        case 'f':
            write<float>(_file);
            break;
        case 'd':
            write<double>(_file);
            break;
        case 'v':
            WriteVoidP(_file);
            break;
        default :
            break;
    }
}

void printMenu()
{
	cout <<"******************************************************************" << endl;
    cout << "(o)pen | (c)lose | (<)< | (>)> | (g)et position |"<< endl << "(m)ode | (s)eek | (l)ength | (e)xit" << endl;
}

