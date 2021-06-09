#ifndef PRIVATE_T_H
#define PRIVATE_T_H

#include "car_t.h"

const size_t kmh = 10;

class Private_t : public Car_t
{
    public:
        Private_t();                 //defult CTOR
        Private_t(size_t _capacity); //CTOR with capacity
        Private_t(const Private_t& _private); //copy CTOR

        size_t getSpeed() const { return m_speed; }
        void accelerate() { m_speed += kmh; }
        void reduceSpeed() { if ( m_speed >= kmh) m_speed -= kmh; }

    private:
        size_t m_speed;
        Private_t &operator = (const Private_t& _private); //assiment operator
};

#endif //PRIVATE_T_H
