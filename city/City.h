#ifndef CITY_H
#define CITY_H

#include <vector>
#include <iostream>
#include "Street.h"
#include "Building.h"
#include "ExceptionHandler.h"
using namespace std;

template <class C, class S, class B>
class City_t
{
	public:
		City_t();
		City_t(const C& _cID);
		City_t(const City_t<C, S, B>& _c);
		City_t<C, S, B>& operator = (const City_t<C, S, B>& _c);

		const C& GetCityID() const;
		void SetCityID(const C& _cID);	
		void AddStreet(const Street_t<S, B>& _s);
		const Street_t<S, B>& GetStreet(const S& _sName) const;
	private:
		C m_cID;
		vector<Street_t<S, B> > m_streets;
};

template <class C, class S, class B>
City_t<C, S, B>::City_t() {}

template <class C, class S, class B>
City_t<C, S, B>::City_t(const C& _cID)
{
	m_cID = _cID;
}

template <class C, class S, class B>
City_t<C, S, B>::City_t(const City_t<C, S, B>& _c)
{
	m_cID = _c.GetCityID();
	m_streets = _c.m_streets;
}

template <class C, class S, class B>
City_t<C, S, B>& City_t<C, S, B>::operator = (const City_t<C, S, B>& _c)
{
	if(this != &_c)
	{
		m_cID = _c.GetCityID();
		m_streets = _c.m_streets;
	}
	
	return *this;
}

template <class C, class S, class B>
const C& City_t<C, S, B>::GetCityID() const
{
	return m_cID;
}

template <class C, class S, class B>
void City_t<C, S, B>::SetCityID(const C& _cID)
{
	m_cID = _cID;
}

template <class C, class S, class B>
void City_t<C, S, B>::AddStreet(const Street_t<S, B>& _s)
{
	m_streets.insert(m_streets.end(), _s);
}

template <class C, class S, class B>
const Street_t<S, B>& City_t<C, S, B>::GetStreet(const S& _sName) const
{
	size_t i;
	for(i = 0 ; i < m_streets.size() ; ++i)
	{
		if(m_streets[i].GetStreetID() == _sName)
		{
			break;
		}
	}
	
	if(i == m_streets.size())
	{
		throw TException_t<S>(_sName, __FILE__, __LINE__, "Street not found");
	}

	return m_streets[i];
}


template <class C, class S, class B>
ostream& operator << (ostream& _os, const City_t<C, S, B>& _c)
{
	_os << _c.GetStreetID();
	return _os;
}


#endif //CITY_H
