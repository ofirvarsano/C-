#ifndef STRING_T_H
#define STRING_T_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class String_t {

	public:
		typedef enum Result
		{
			EQUAL,
			SMALLER,
			GREATER
		}Result;
		
		String_t(); //defult CTOR, loads object with '\0'

		String_t(const char* _st); //CTOR from, loads object with _st

		String_t(const String_t& _st); //copy CTOR, loads object with _st

		~String_t(); //default DTOR

		String_t& operator = (const String_t& _st); //assiment operator

		size_t Length() const { return strlen(GetString()) ;} //return object's length - inline

		void SetString(const char* _st); //sets object with _st if exist '\0' otherwise

		const char* GetString() const { //return const char pointer of m_str - inline
			return m_str;
		}

		Result Compare(const String_t& _st) const; //compare object with _st RET VAL : 0 if equal , 1 if object is less than parameter, 2 otherwise
		
		void Print() const; //prints object

		String_t& UpperCase(); //convers all characters to uppercase

		String_t& LowerCase(); //convers all characters to lowercase
		
		String_t& Prepend(const char* _str);

		String_t& Prepend(const String_t& _str);

		String_t& operator += (const char* _str); //appends

		String_t& operator += (const String_t& _str); //appends

		bool operator > (const String_t& _str) const;

		bool operator < (const String_t& _str) const;

		bool operator >= (const String_t& _str) const;

		bool operator <= (const String_t& _str) const;

		bool operator == (const String_t& _str) const;

		bool operator != (const String_t& _str) const;

		bool Contains(const String_t& _st) const; //return 1 if object contains _st

		const char& operator [] (size_t _index) const; //return _index char value of object, '\0' if out of bound index 

		char& operator [] (size_t _index); //assign _index char value of object with rvalue of operator, does nothing if out of bound

		int FirstOccurrence(const char _c) const; // return index of first occurrence of _c in object

		int LastOccurrence(const char _c) const; // return index of last occurrence of _c in object
		
		static size_t NumOfStrings() { return numOfStrings; } //return number of objects in the program - inline
		
		static bool CaseSensativeFlip() {CaseSensative = !CaseSensative; return !CaseSensative; } // sets a new flag and returns the previous one

		static unsigned int CapacitySet(unsigned int _newSize); // sets a new global capacity and returns the previous one

		static unsigned int GetGlobalCapacity() { return GlobalCapacity; } // returns global capacity - inline

		unsigned int GetCapacity() { return Capacity; } // returns capacity - inline

		String_t operator()(unsigned int start, unsigned int len) const; // returns substring which starts in start position and has a length len 

	private:
		char* m_str;
		char* CreateFrom(const char* _st);
		unsigned int Capacity;
		static size_t numOfStrings;
		static unsigned int GlobalCapacity;
		static bool CaseSensative;
};

ostream& operator << (ostream& _os, const String_t& _str);

istream& operator >> (istream& _is, String_t& _str);

#endif //STRING_T_H
