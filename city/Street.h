#ifndef STREET_H
#define STREET_H

#include <vector>
#include <iostream>
#include "Building.h"
#include "ExceptionHandler.h"
using namespace std;

template <class S, class B>
class Street_t
{
	public:
		Street_t();
		Street_t(const S& _sID);
		Street_t(const Street_t<S, B>& _s);
		Street_t<S, B>& operator = (const Street_t<S, B>& _s);

		const S& GetStreetID() const;
		void SetStreetID(const S& _sID);	
		void AddBuilding2Street(const Building_t<B>& _b);
		const Building_t<B>& GetBuilding(const B& _bID) const;

	private:
		S m_sID;
		vector<Building_t<B> > m_buildings;
};


template <class S, class B>
Street_t<S, B>::Street_t() {}

template <class S, class B>
Street_t<S, B>::Street_t(const S& _sID)
{
	m_sID = _sID;
}

template <class S, class B>
Street_t<S, B>::Street_t(const Street_t<S, B>& _s)
{
	m_sID = _s.GetStreetID();
	m_buildings = _s.m_buildings;
}

template <class S, class B>
Street_t<S, B>& Street_t<S, B>::operator = (const Street_t<S, B>& _s)
{
	if(this != &_s)
	{
		m_sID = _s.GetStreetID();
		m_buildings = _s.m_buildings;
	}
	return *this;
}

template <class S, class B>
const S& Street_t<S, B>::GetStreetID() const
{
	return m_sID;
}

template <class S, class B>
void Street_t<S, B>::SetStreetID(const S& _sID)
{
	m_sID = _sID;
}

template <class S, class B>
void Street_t<S, B>::AddBuilding2Street(const Building_t<B>& _b)
{
	m_buildings.insert(m_buildings.end(), _b);
}

template <class S, class B>
const Building_t<B>& Street_t<S, B>::GetBuilding(const B& _bID) const
{
	size_t i;
	for(i = 0 ; i < m_buildings.size() ; ++i)
	{
		if(m_buildings[i].GetBuildingID() == _bID)
		{
			break;
		}
	}
	
	if(i == m_buildings.size())
	{
		 TException_t<B>(_bID, __FILE__, __LINE__, "Building not found");
	}

	return m_buildings[i];
}

template <class S, class B>
ostream& operator << (ostream& _os, const Street_t<S, B>& _s)
{
	_os << _s.GetStreetID();
	return _os;
}


#endif //STREET_H


