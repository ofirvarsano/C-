#ifndef BUS_T_H
#define BUS_T_H

#include "car_t.h"

class Bus_t : public Car_t
{
    public:
        Bus_t();                 //defult CTOR
        Bus_t(size_t _capacity); //CTOR with capacity
        Bus_t(const Bus_t& _bus); //copy CTOR

        void setLine(size_t _line) { m_line = _line; }
        void setSeats(size_t _seats) { m_seats = _seats; }

        size_t getLine() const { return m_line; }
        size_t getSeats() const { return m_seats; }

    private:
        size_t m_line;
        size_t m_seats;
        Bus_t &operator = (const Bus_t& _bus); //assiment operator
};

#endif //BUS_T_H
