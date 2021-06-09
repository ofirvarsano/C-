#include <iostream>

#include "memPage_t.h"
#include "memManager_t.h"
#include "memPool_t.h"
using namespace std;

void MM_test(MemManager_t* _pmemManager);
void PrintMenu();

int main()
{
    int choice = -1;
    MemManager_t* mm;
    while (choice != 0)
    {
        PrintMenu();
        cin >> choice;
        switch(choice)
        {
        	case 0:
                break;
            case 1:
                mm = new MemPool_t;
                MM_test(mm);
                break;
            case 2:
                mm = new MemPage_t;
                MM_test(mm);
                break;
            default :
            	cout << "Invalid choice" << endl;
                break;
        }
    }
    delete mm;
    return 0;
}
void PrintMenu()
{
    cout << "welcome to the memory manager" << endl;
    cout <<"******************************" <<endl;
    cout << "1: for memory pool"<<endl;
    cout << "2: for memory page" <<endl;
    cout << "0: for exit"<< endl;
    cout <<"******************************" <<endl;
    cout <<"******************************" <<endl;
}

void MM_test(MemManager_t* _pmemManager)
{
    int choice = -1;
    int choice2 = -1;
    int buff;
    double dbuff;
    char c;
    size_t pos;
    size_t size;
    
    while(choice != 0)
    {
        cout <<"******************************"<<endl;
        cout << "1: Is empty"<<endl;
        cout << "2: get Position" << endl;
        cout << "3: Set Position" << endl;
        cout << "4: get actual size" <<endl;
        cout << "5: page: get capacity" <<endl;
        cout << "6: Is page full" <<endl;
        cout << "7: Write to a Given Position" << endl;
		cout << "8: Write" << endl;
		cout << "9: read from a Given Position" << endl;
		cout << "10: Read" << endl;
        cout << "11: pool: set default Page Size" << endl;
        cout << "12: pool: get default Page Size" << endl;
        cout << "0: exit to the main menu" << endl;
        cout <<"******************************" <<endl;

        cin >> choice;

        switch (choice)
        {
            case 0:
                break;

            case 1:
            {
                cout << (_pmemManager->IsEmpty() ? "Empty": "Not Empty") << endl;
                break;
            }

            case 2:
            {
                cout << "The position is : " << _pmemManager->GetPosition() << endl;
                break;
            }
			
			case 3:
            {
                int position = 0;
                cout << "what is the new position ?" << endl;
                cin >> position;
                _pmemManager->SetPosition(position);
                break;
            }
            
            case 4:
            {
                cout << "The size is: " << _pmemManager->GetSize() << endl;
                break;
            }
            
            case 5:
            {
                cout << "Page capacity is: " << ((MemPage_t*)_pmemManager)->GetCapacity() << endl;
                break;
            }
            
            case 6:
            {
                cout << (((MemPage_t*)_pmemManager)->IsFull() ? "Full" : "Not Full") << endl;
                break;
            }
            case 7:
            case 8:
            	cout << "Choose option: " << endl;
				cout << "1: write int  " << endl;
				cout << "2: write double  " << endl;
				cout << "3: write char  " << endl;
				cin >>  choice2;
				pos = _pmemManager->GetPosition();
				if(choice == 7)
				{
					cout << "Enter Position" <<endl;
					cin >> pos;
				}
				switch(choice2)
				{
					case 1:
						buff = 0;
				        cout << "which number do you want to write ?"<< endl;
				        cin >> buff;
				        cout << "Succees to write : " << _pmemManager->write(pos, &buff, sizeof(int)) << endl;
				        break;
				        
					case 2:
						dbuff = 0;
				        cout << "which number do you want to write ?"<< endl;
				        cin >> dbuff;
				        cout << "Succees to write : " << _pmemManager->write(pos, &dbuff, sizeof(double)) << endl;
				        break;
				        
					case 3:
						cout << "which letter do you want to write ?" << endl;
				        cin >> c;
				        cout << "succees to write : " << _pmemManager -> write(pos, &c, sizeof(char)) << endl;
						break;
						
					default:
						break;
				}
				break;
			case 9:
			case 10:
				cout << "Choose option: " << endl;
				cout << "1: Read int  " << endl;
				cout << "2: Read double  " << endl;
				cout << "3: Read char  " << endl;
				cin >> choice2;
				pos = _pmemManager->GetPosition();
				if(choice == 9)
				{
					cout << "Enter Position" <<endl;
					cin >> pos;
				}
				switch(choice2)
				{
					case 1:
						buff = 0;
                		cout << "succeed to read : " <<_pmemManager->read(pos, &buff, sizeof(int))<<" bytes"<< endl;
                		cout << "the result is : " << buff << endl;
                		break;
				        
					case 2:
						dbuff = 0;
                		cout << "succeed to read : " <<_pmemManager->read(pos, &dbuff, sizeof(double))<<" bytes"<< endl;
                		cout << "the result is : " << dbuff << endl;
                		break; 
				        
					case 3:
				        cout << "succeed to read : " <<_pmemManager->read(pos, &c, sizeof(char))<<" bytes"<< endl;
				        cout << "the result is : " << c << endl;
                		break;
						
					default:
						break;
				}
				break;
			case 11:
	            cout << "what is the new default page size ?" << endl;
	            cin >> size;
	            MemPool_t::SetPageSize(size);
	            break;
	            
			case 12:
	            cout << "Default page size is : "<< MemPool_t::GetPageSize(size) << endl;
	            break;
	            
            default:
            { 
                cout << "Invalid choice" << endl;
                break;
            }    
        }
    }
}
