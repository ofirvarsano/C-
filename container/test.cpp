#include <iostream>
#include "container_t.h"
#include "array_t.h"
#include "dlist_t.h"

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
		cout<<"13: Print"<<endl;
		cout<<"Other - EXIT"<<endl;
		cout<<endl<<"please enter your choice(1-12) : ";
		cin>>choice;

		return choice;
}

void ArrayTest()
{
	int* g_arrayPtr[256];
	static size_t g_index = 0;

	array_t<int> intArray;
	int choice;
	bool b;
	int indexOf;
	int tmp;
	size_t index;
	
	for (int i = 0; i < 256; ++i)
	{
		g_arrayPtr[i]=new int;
	}

	bool flag = true;
	while(flag)
	{
		choice = PrintMenu();

		switch(choice)
		{
			case 1:
				cout<< "please enter an Integer: ";
				cin>>*g_arrayPtr[g_index];
				intArray.Insert(g_arrayPtr[g_index++]);
				break;

			case 2:
				
				cout<< "please enter an Integer To Append: ";
				cin>>*g_arrayPtr[g_index];
				cout<< "enter an index to append at: ";
				cin>>index;
				b = intArray.Append(g_arrayPtr[g_index++], index);
				cout<<endl<< (b? "SUCCESS" : "FAILED") << endl<<endl;
				break;
				
			case 3:
				cout<< "please enter an Integer To Prepend: ";
				cin>>*g_arrayPtr[g_index];
				cout<< "enter an index to prepend at: ";
				cin>>index;
				b = intArray.Prepend(g_arrayPtr[g_index++], index);
				cout<<endl<< (b? "SUCCESS" : "FAILED") << endl<<endl;
				break;

			case 4:
				cout << "please enter an Integer: ";
				cin>>tmp;
				cout << endl << (intArray.Contains(tmp) ? "It is in the array!" : " Not Found ")<<endl;
				cout << endl; 
				break;

			case 5:
				cout << "please enter an Integer: ";
				cin>>tmp;
				cout << endl << (intArray.Find(tmp) ? "It is in the array!" : "Not Found ")<<endl;
				cout << endl;
				break;

			case 6:
				cout << "please enter an Integer: ";
				cin>>tmp;
				cout << endl << "the index of this integer is : ";
				indexOf = intArray.Index(tmp);
				if (indexOf >=0)
				{
					cout<< indexOf <<endl <<endl;
				}
				else
				{
					cout<< "It is not into the array :(" <<endl <<endl;
				}
				break;

			case 7:
				cout<<endl<<"The Actual size is : "<<intArray.Count()<<endl<<endl;
				break;

			case 8:
				cout<< (intArray.IsEmpty()?" YES " : "NO")<<endl<<endl;
				break;

			case 9:
				int* res; 
				cout << "please enter an Integer to Remove: ";
				cin>>tmp;
				res = (int*)intArray.Remove(tmp);
				cout <<endl<< (res? " the number has been removed ! " : "Not Found !")<<endl<<endl;
				break;

			case 10:
				intArray.RemoveAll();
				cout<<endl<<"All elements in the array were been removed !"<<endl;
				break;

			case 11:
				cout << "please enter an Integer to Remove and Delete: ";
				cin>>tmp;
				cout << endl << (intArray.RemoveAndDelete(tmp)?" The Element has been Removed !":"Not Found!")<<endl<<endl;
				break;

			case 12:
				intArray.RemoveAndDeleteAll();
				cout<<endl<<"All elements in the array were been removed and deleted!"<<endl;
				break;

			case 13:
				intArray.Print();	
				break;

			default:
				flag=false;
				break; 
		}
	}
}

int main()
{
	int choice;
	cout << "Welcome" << endl;
	cout << "For Array: 1" << endl;
	cout << "For List: 2"  << endl;
	cin >> choice;

	switch(choice)
	{
		case 1:
			ArrayTest();
			break;

		default:
			break;

	}

	
	return 0;
}