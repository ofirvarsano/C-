#include "private_t.h"

Private_t::Private_t() : m_speed(0) // default
{
    setName("Private");
    setGear(AUTOMATIC);
}

Private_t::Private_t(size_t _capacity) : Car_t(_capacity)
{
    m_speed = 0;
    setName("Private");
    setGear(AUTOMATIC);
}

Private_t::Private_t(const Private_t& _private) : Car_t(_private)
{
    m_speed = 0;
}
