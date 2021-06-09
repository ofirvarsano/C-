#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
using namespace std;

template <class B>
class Building_t
{
	public:
		Building_t();
		Building_t(const B& _bID);
		Building_t(const Building_t<B>& _b);
		Building_t<B>& operator = (const Building_t<B>& _b);

		const B& GetBuildingID() const;
		void SetBuildingID(const B& _bID);

	private:
		B m_bID;
};

template <class B>
Building_t<B>::Building_t() {}

template <class B>
Building_t<B>::Building_t(const B& _bID)
{
	m_bID = _bID;
}

template <class B>
Building_t<B>::Building_t(const Building_t<B>& _b)
{
	m_bID = _b.GetBuildingID();
}

template <class B>
Building_t<B>& Building_t<B>::operator = (const Building_t<B>& _b)
{
	if(this != &_b)
	{
		m_bID = _b.GetBuildingID();
	}

	return *this;
}

template <class B>
const B& Building_t<B>::GetBuildingID() const
{
	return m_bID;
}

template <class B>
void Building_t<B>::SetBuildingID(const B& _bID)
{
	m_bID = _bID;
}

template <class B>
ostream& operator << (ostream& _os, const Building_t<B>& _b)
{
	_os << _b.GetBuildingID();
	return _os;
}

#endif //BUILDING_H
