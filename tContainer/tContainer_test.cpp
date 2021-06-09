#include "tContainer.h"
using namespace std;

const size_t size = 256;

template <class T>
void ExceptionHandler(const TException_t<T>& _ex)
{
	cout << _ex.GetText() << ". Exception: " << _ex.GetException() << endl;
	cout << "File: " << _ex.GetFileName() << ". Line: " << _ex.GetLineNum() << endl;	
}

template <typename T, typename CONT>
void Test(tContainer_t<T, CONT>& _cont)
{
	int 	cont = 1;
	int 	option, num;
	int*	get;
	
	size_t arr_index = 0;
	int* arr[size];
	for (size_t i = 0; i < size; ++i)
	{
		arr[i] = new int;
	}
	
	while (cont)
	{
		cout << endl << "Choose option: " << endl;
		cout << "1: Check if container is empty  " << endl;
		cout << "2: Get number of elements    " << endl;
		cout << "3: Insert new element  " << endl;
		cout << "4: Get first element  " << endl;
		cout << "5: Get last element" << endl;
		cout << "6: Find element  " << endl;
		cout << "7: Remove element  " << endl;
		cout << "8: Remove all elements" << endl;
		cout << "9: Remove and delete element" << endl;
		cout << "10:Remove and delete all elements" << endl;
		cout << "11:Get [N] element" << endl;
		cout << "Any other number - Exit " << endl;

		cin >>  option;
		cout << endl;
		switch (option)
		{
			case 1:
				if(_cont.IsEmpty())
					cout << "Empty" << endl;
				else
					cout << "NOT empty" << endl;					
				break;
			case 2:
				cout << _cont.NumOfElements() << endl;
				break;
			case 3:
				cout << "please insert integer to add:" << endl;
				cin >> *arr[arr_index];;
				_cont.Insert(arr[arr_index++]);
				break;
			case 4:
				get = _cont.GetFirst();
				if(get == NULL)
					cout << "Container is empty" << endl;
				else
					cout << "First element:" << *get << endl;					
				break;
			case 5:
				get = _cont.GetLast();
				if(get == NULL)
					cout << "Container is empty" << endl;
				else
					cout << "Last element:" << *get << endl;					
				break;
			case 6:
				cout << "please insert integer to find:" << endl;
				cin >> num;
				get = _cont.FindElementIf(num);
				if(get == NULL)
					cout << "Element not found" << endl;
				else
					cout << "Found element:" << *get << endl;					
				break;
			case 7:
				cout << "please insert integer to remove:" << endl;
				cin >> num;
				get = _cont.RemoveElement(num);
				if(get == NULL)
					cout << "Element not found" << endl;
				else
					cout << "Removed element:" << *get << endl;					
				break;
			case 8:
				_cont.RemoveAllElements();
				break;
			case 9:
				cout << "please insert integer to remove & delete:" << endl;
				cin >> num;
				try {
					_cont.RemoveAndDeleteElement(num);
					cout << "Element removed" << endl;	
				}
				catch (TException_t<int> ex) { ExceptionHandler(ex);}					
				break;
			case 10:
				_cont.RemoveAndDeleteAllElements();
				cout << "All element removed" << endl;	
				break;
			case 11:
				cout << "please insert index:" << endl;
				cin >> num;
				get = _cont[num];
				if(get == NULL)
					cout << "Element not found" << endl;
				else
					cout << "Found element:" << *get << endl;					
				break;
			default: cont = 0;
		}
	}
}


int main()
{
	/*tContainer_t<int, vector<int*> >* cont;*/
	tContainer_t<int, vector<int*> > vec;
	tContainer_t<int, list<int*> > list;
	int option;
	/*cont = new tContainer_t<int, vector<int*> >; */
	cout << "Choose option: " << endl;
	cout << "1: Test with vector  " << endl;
	cout << "2: Test with list   " << endl;
	cout << "Any another number - stop " << endl;

	cin >>  option;
	switch (option) {
		case 1:
			Test(vec);
			break;
		
		case 2:
			Test(list);
			break;
		default: 
			break;
	}
	
	return 0;
}
