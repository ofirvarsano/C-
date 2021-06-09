#include <iostream>
#include "cyc_blking_queque.hpp"
#include "cyc_blking_queque_inl.hpp"
#include "../../threads/semaphore_exceptions.hpp"
#include "../../threads/mutex_exceptions.hpp"

typedef experis::MTCyclicBlokingQueue CycQ;
int main() {
	CycQ q(5);
	int x, i;
	x = 7;
	q.Enqueue(x);
	q.Dequeue(i);
	std::cout << i << std::endl;
    return 0;
}
