#include <iostream>
#include "container_t.h"
#include "vector_t.h"
#include "dlist_t.h"

void Test(container_t<int>* contain);
const size_t size = 256;

int PrintMenu()
{
		int choice;

		cout<<"1:  Insert"<<endl;
		cout<<"2:  Append"<<endl;
		cout<<"3:  Prepend"<<endl;
		cout<<"4:  Contains"<<endl;
		cout<<"5:  Find"<<endl;
		cout<<"6:  Index Of"<<endl;
		cout<<"7:  Count"<<endl;
		cout<<"8:  IsEmpty"<<endl;
		cout<<"9:  Remove"<<endl;
		cout<<"10: Remove All"<<endl;
		cout<<"11: RemoveAndDelete"<<endl;
		cout<<"12: RemoveAndDeleteAll"<<endl;
		cout<<"Other - EXIT"<<endl;
		cout << endl << "please enter your choice(1-12) : ";
		cin>>choice;

		return choice;
}

void Test(container_t<int>* contain)
{
	bool b, flag = true;
	int choice, num;
	int index;
	
	size_t arr_index = 0;
	int* arr[size];
	for (size_t i = 0; i < size; ++i)
	{
		arr[i] = new int;
	}
	
	while(flag)
	{
		choice = PrintMenu();

		switch(choice)
		{
			case 0:
				flag = false;
                break;
			case 1:
				cout << "Enter an Integer: " << endl;
				cin >> *arr[arr_index];
				contain->Insert(arr[arr_index++]);
				break;

			case 2:
				
				cout << "Enter an Integer To Append: " << endl;
				cin >> *arr[arr_index];
				cout << "Enter an index to append at: " << endl;
				cin >> index;
				b = contain->Append(index, arr[arr_index++]);
				cout << endl << (b ? "SUCCESS" : "FAILED") << endl;
				break;
				
			case 3:
				cout << "Enter an Integer To Prepend: " << endl;
				cin >> *arr[arr_index];
				cout << "Enter an index to prepend at: " << endl;
				cin >> index;
				b = contain->Prepend(index, arr[arr_index++]);
				cout << endl << (b ? "SUCCESS" : "FAILED") << endl;
				break;

			case 4:
				cout << "Enter an Integer: ";
				cin >> num;
				cout << endl << (contain->Contains(num) ? "Found" : "Not Found") << endl;
				cout << endl; 
				break;

			case 5:
				cout << "Enter an Integer: " << endl;
				cin >> num;
				cout << endl << (contain->Find(num) ? "Found" : "Not Found")<<endl;
				cout << endl;
				break;

			case 6:
				cout << "Enter an Integer: " << endl;
				cin >> num;
				cout << endl << "the index of this integer is : ";
				index = contain->Index(num);
				if (index >= 0)
				{
					cout << index <<endl;
				}
				else
				{
					cout << "Not Found" <<endl;
				}
				break;

			case 7:
				cout << endl << "Num Of Items : " << contain->Count() << endl;
				break;

			case 8:
				cout << (contain->IsEmpty() ? " YES " : "NO") << endl;
				break;

			case 9:
				int* res; 
				cout << "Enter an Integer to Remove: " << endl;
				cin >> num;
				res = (int*)contain->Remove(num);
				cout <<endl << (res ? "Removed" : "Not Found !") <<endl;
				break;

			case 10:
				contain->RemoveAll();
				cout << endl << "Removed All"<<endl;
				break;

			case 11:
				cout << "Enter an Integer to Remove and Delete: " << endl;
				cin >> num;
				cout << endl << (contain->RemoveAndDelete(num) ? "Removed and deleted":"Not Found!")<<endl<<endl;
				break;

			case 12:
				contain->RemoveAndDeleteAll();
				cout << endl << "All Removed and deleted" << endl;
				break;

			default:
				flag = false;
				break; 
		}
	}
}

int main()
{
	container_t<int>* contain = NULL;;
	int choice = 1;
	
	while (choice != 0)
    {
    	cout << "1 - For Vector" << endl;
		cout << "2 - For List" << endl;
		cout << "0 - Exit" << endl;
    	cin >> choice;
		switch(choice)
		{
			case 0:
                break;
			case 1:
				contain = new vector_t<int>;
				Test(contain);
				delete contain;
				break;

			case 2:
				contain = new dlist_t<int>;
				Test(contain);
				delete contain;
				break;
			default:
				break;
		}
	}
	
	return 0;
}



