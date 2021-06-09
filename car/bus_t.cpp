#include "bus_t.h"

Bus_t::Bus_t() : m_line(0) , m_seats(0) // default
{
    setName("Bus");
    setGear(STANDARD);
}

Bus_t::Bus_t(size_t _capacity) : Car_t(_capacity)
{
     m_line = 0;
    m_seats = 0;
    setName("Bus");
    setGear(STANDARD);
}

Bus_t::Bus_t(const Bus_t& _bus) : Car_t(_bus)// copy
{
    m_line = _bus.getLine();
    m_seats = _bus.getSeats();
}

