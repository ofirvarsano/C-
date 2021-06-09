#include "car_t.h"
#include "../string/string_t.h"

size_t Car_t::globalID = 1;
size_t Car_t::globalCapacity = 2000;

Car_t::Car_t() : m_id(globalID++) , m_capacity(globalCapacity) {}

Car_t::Car_t(size_t _capacity) : m_id(globalID++),
									m_capacity(_capacity){}

Car_t::Car_t(const Car_t& _car) : m_id(globalID++),
									m_capacity(_car.m_capacity),
									m_gear(_car.m_gear),
									m_name(_car.m_name){}

bool Car_t::operator < (const Car_t& _car) const
{
    return m_capacity < _car.getCapacity();
}

bool Car_t::Compare(const Car_t& _car) const
{
    return m_name.Compare(_car.getName()) == 0 ? true : false;
}

void Car_t::setName(const String_t& _name)
{
	m_name = _name;
    // m_name.SetString(_name.GetString());
}

void Car_t::setGear(Gear _gearType)
{
    m_gear = _gearType;
}

