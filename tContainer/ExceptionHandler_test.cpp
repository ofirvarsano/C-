#include "ExceptionHandler.h"

int main()
{
	try{
		throw TException_t<int>(5, __FILE__, __LINE__, "error");;
	} catch(TException_t<int> _ex){
		cout << "File name: " << _ex.GetFileName() << endl;
		cout << "Line number: " << _ex.GetLineNum() << endl;
		cout << "Exception: " << _ex.GetException() << endl;
	}

	return 0;
}

