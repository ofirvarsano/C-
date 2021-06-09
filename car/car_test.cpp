#include <iostream>
#include "bus_t.h"
#include "private_t.h"

int main()
{
	int cont = 1;
	unsigned int option;
    Private_t private1, private2;
    Bus_t bus1, bus2;

    Private_t p(1500);
    Bus_t b(1500);

    Private_t p2(p); // ask
    Bus_t b2(b);

	while (cont) {
		cout << "Choose option: " << endl;
		cout << "1: getName  " << endl;
		cout << "2: getGear    " << endl;
		cout << "3: getCapacity  " << endl;
        cout << "4: setCapacity  " << endl;
        cout << "5: operator <  " << endl;
        cout << "6: Compare  " << endl;
        cout << "7: getID  " << endl;
        cout << "8: operator =  " << endl;
        cout << "9: bus setLine  " << endl;
        cout << "10: bus setSeats  " << endl;
        cout << "11: bus setLine  " << endl;
        cout << "12: private getSpeed  " << endl;
        cout << "13: private accelerate  " << endl;
        cout << "14: private reduceSpeed  " << endl;
		cout << "Any another number - stop " << endl;

		cin >>  option;

		switch (option)
        {
			case 1:
                
				cout << private1.getName() << endl;
			case 2:
				break;
			case 3:
				cout << private1.getCapacity() << endl;	break;

			default: cont = 0;	break;
		}
	}


	return 0;
}
