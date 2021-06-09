#include "City.h"
#include <iostream>
using namespace std;

template <class T>
void ExceptionHandler(const TException_t<T>& _ex)
{
	cout << _ex.GetText() << ". Exception: " << _ex.GetException() << endl;
	cout << "File: " << _ex.GetFileName() << " Line: " << _ex.GetLineNum() << endl;	
}

int main()
{
	Building_t<int> b1, b2;
	b1.SetBuildingID(6);
	b2.SetBuildingID(20);

	Street_t<string, int> s1, s2, s3, s4;
	s1.SetStreetID("Herzl");
	s2.SetStreetID("A10");

	Street_t<string, int> s5 = s2;
	cout << "Street: " << s5 << endl;

	s4 = s1;
	cout << "Street: " << s4 << endl;

	City_t<string, string, int> c1;
	c1.SetCityID("Rishon Lezion");
	
	s1.AddBuilding2Street(b1);
	s1.AddBuilding2Street(b2);
	s2.AddBuilding2Street(b1);
	s2.AddBuilding2Street(b2);

	c1.AddStreet(s1);
	c1.AddStreet(s2);
	
	try
	{
		b2 = s1.GetBuilding(20);
		cout << "Building: " << b2 << " Found" << endl;
	} 
	catch (TException_t<int> ex) { ExceptionHandler(ex); }

	try
	{
		s3 = c1.GetStreet("abc");
		cout << "Street: " << s3 << " Found" << endl;
	} 
	catch (TException_t<string> ex) { ExceptionHandler(ex); }

	return 0;
}
