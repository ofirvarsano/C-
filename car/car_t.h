#ifndef CAR_T_H
#define CAR_T_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../string/string_t.h"

using namespace std;

class Car_t
{
	public:
		typedef enum Gear
		{
		    STANDARD,
		    AUTOMATIC
		} Gear;

		Car_t();                 //defult CTOR
		Car_t(size_t _capacity); //CTOR with capacity
		Car_t(const Car_t& _car); //copy CTOR

		const String_t& getName() const { return m_name; }
		Gear getGear() const { return m_gear; }
		size_t getCapacity() const { return m_capacity; }

		bool operator < (const Car_t& _car) const;
		bool Compare(const Car_t& _car) const;
		size_t getID() const { return m_id;}

	protected:
		~Car_t(){} //default DTOR
		void setName(const String_t& _name);
		void setGear(Gear _gearType);
		void setCapacity(size_t _capacity) { m_capacity = _capacity; }

	private:
		Car_t &operator = (const Car_t& _car); //assiment operator
		
		String_t m_name;
		Gear m_gear;
		size_t m_capacity;
		const size_t m_id;
		static size_t globalID;
		static size_t globalCapacity; 
};

#endif //CAR_T_H
