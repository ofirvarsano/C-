#ifndef _FUNCTORS_HPP_
#define _FUNCTORS_HPP_

#include <stdio.h>

#include "bitset.hpp"

#define ZERO_MASK 0

const unsigned long ONE_MASK = 1;

struct FuncIsAllOff {
	bool operator()(const unsigned long a_idx) { return a_idx == 0; };
};

struct FuncCountOnBits {
	void operator()(const unsigned long& a_idx) {
		unsigned long numInIdx = a_idx;
		
		while(numInIdx > 0) {
		    sum += numInIdx & ONE_MASK;
		    numInIdx >>= 1;
		}
	}
	unsigned int sum = 0;
};

struct FuncIsAllOn {
	bool operator()(const unsigned long& a_idx) {
    	if(a_idx == 0) {
        	return false;
    	}
    	FuncCountOnBits count;
    	count(a_idx);
    	unsigned long result = count.sum;
    	if(result == SIZE_BITS_OF_UL) {
        	return true;
    	}
    	return false;
	}
};

struct ClearAllBitsIndex {
	void operator()(unsigned long& a_idx) {
		a_idx &= 0;
	}
};

struct FillAllBitsInIndex {
	void operator()(unsigned long& a_idx) {
		a_idx = a_idx & 0;
		a_idx= ~a_idx;
	}
};

struct FilpAllBits {
	void operator()(unsigned long& a_idx) {
		unsigned long mask = ~ZERO_MASK;
		a_idx ^= mask;
	}
};

struct FirstAndSecond {
	unsigned long operator()(const unsigned long& a_idx1, const unsigned long& a_idx2) {
		unsigned long newNum = a_idx1 & a_idx2;
		return newNum;
	}
};

struct FirstOrSecond {
	unsigned long operator()(const unsigned long& a_idx1, const unsigned long& a_idx2) {
		unsigned long newNum = a_idx1 | a_idx2;
		return newNum;
	}
};

struct FirstXOrSecond {
	unsigned long operator()(const unsigned long& a_idx1, const unsigned long& a_idx2) {
		unsigned long newNum = a_idx1 ^ a_idx2;
		return newNum;
	}
};

#endif // _FUNCTORS_HPP_

