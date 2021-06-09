#include "../mu_test.hpp"
#include "bitset.hpp"

#include <stdio.h>
#include <iostream>

UNIT(BitsetCTOR)
    experis::Bitset<65> b1; 
END_UNIT

UNIT(BitsetTurnOn)
    experis::Bitset<65> b65;
    experis::Bitset<10000> b10000;
    
	ASSERT_THAT(b65.CountOnBits() == 0);
    
    b65.TurnOn(60);
    b65.TurnOn(59);
    b65.TurnOn(0);
    b65.TurnOn(64);
    b65.CountOnBits();
    b65.Print();
    std::cout << "b65 on bits : " << b65.CountOnBits() << std::endl;
    b65.Fill();
    std::cout << "b65 on bits after fill: " << b65.CountOnBits() << std::endl;

    ASSERT_THAT(b10000.TurnOn(1587) == 2251799813685248);
END_UNIT

UNIT(BitsetTurnOff)
    experis::Bitset<65> b65;
    experis::Bitset<10000> b10000;

    ASSERT_THAT(b65.TurnOn(64) == 1);
    ASSERT_THAT(b65.TurnOn(3) == 8);
    ASSERT_THAT(b10000.TurnOn(1587) == 2251799813685248);
    b65.TurnOff(3);
    b65.TurnOff(64);
    ASSERT_THAT(b65.TurnOff(64) == 0);
    ASSERT_THAT(b10000.TurnOff(1587) == 0);
END_UNIT

UNIT(BitsetSet)
    experis::Bitset<65> b65;
    experis::Bitset<10000> b10000;

    ASSERT_THAT(b65.Set(64, true) == 1);
    ASSERT_THAT(b65.Set(3, true) == 8);
    ASSERT_THAT(b65.Set(64, false) == 0);
    ASSERT_THAT(b10000.Set(1587, true) == 2251799813685248);
    ASSERT_THAT(b10000.Set(1587, false) == 0);
END_UNIT

UNIT(BitsetFlip)
    experis::Bitset<65> b65;
    experis::Bitset<10000> b10000;
	
	try {
    	b65.Flip(65);
    }
    catch (const std::out_of_range& ex) {
    	std::cout << ex.what() << std::endl;
    }
    ASSERT_THAT(b65.Flip(64) == 1);
    std::cout << "b65 : " << b65 << std::endl;
    ASSERT_THAT(b65.Flip(64) == 0);
    std::cout << "b65 : " << b65 << std::endl;
    b10000.Flip(1587);
    ASSERT_THAT(b10000.Flip(1587) == 0);

    ASSERT_THAT(b65.Flip(3) == 8);
    std::cout << "b65 : " << b65 << std::endl;
    try {
    	b65.Flip(65);
    }
    catch (const std::out_of_range& ex) {
    	std::cout << ex.what() << std::endl;
    }
    ASSERT_THAT(b65.Flip(64) == 1);
END_UNIT

UNIT(BitsetIsOn)
    experis::Bitset<65> b65;
    experis::Bitset<10000> b10000;

    ASSERT_THAT(b65.IsOn(65) == false); // out of range
    ASSERT_THAT(b65.Flip(64) == 1);
    ASSERT_THAT(b65.IsOn(64) == true);
    b10000.Flip(1587);
    ASSERT_THAT(b10000.IsOn(1587) == true);
END_UNIT

UNIT(BitsetIsAllOff)
    experis::Bitset<65> b65;
    experis::Bitset<5> b5;
    experis::Bitset<10000> b10000;

    ASSERT_THAT(b65.AreAllOff() == true);
    try {
    	b65.Flip(65);
    }
    catch (const std::out_of_range& ex) {
    	std::cout << ex.what() << std::endl;
    }
    b65.Flip(64);
    std::cout << "b65 after flip 64 :" << std::endl << b65 << std::endl;

    ASSERT_THAT(b65.AreAllOff() == false);
    b10000.Flip(1587);
    ASSERT_THAT(b10000.AreAllOff() == false);
    
    b65.Clear();
    ASSERT_THAT(b65.AreAllOff() == true);
    ASSERT_THAT(b65.AreAllOn() == false);
    
    b65.FlipAll();
    ASSERT_THAT(b65.AreAllOff() == false);
    ASSERT_THAT(b65.AreAllOn() == true);
    
    b5.FlipAll();
    b5.Flip(0);
    b5.Flip(1);
    b5.Flip(2);
    b5.Flip(3);
    b5.Flip(4);
    ASSERT_THAT(b5.AreAllOn() == false);
    ASSERT_THAT(b5.AreAllOff() == true);
END_UNIT

UNIT(BitsetIsAllOn)
    experis::Bitset<65> b65;
    experis::Bitset<5> b5;
    experis::Bitset<10000> b10000;

	ASSERT_THAT(b5.AreAllOff() == true);
    ASSERT_THAT(b65.AreAllOn() == false);
    ASSERT_THAT(b10000.AreAllOn() == false);
    b65.Flip(63);
    b65.Flip(64);
    b65.Flip(0);
    b65.Flip(1);
    b65.Print();
    ASSERT_THAT(b65.AreAllOn() == false);
    b5.TurnOn(0);
    b5.TurnOn(1);
    b5.TurnOn(2);
    b5.TurnOn(3);
    b5.TurnOn(4);
	
	std::cout << "b65 : " << b65 << std::endl;
    ASSERT_THAT(b5.AreAllOn() == true);

END_UNIT

UNIT(BitsetCopyCTOR)
    experis::Bitset<65> b65;

    b65.Flip(63);
    b65.Flip(64);
    b65.Flip(0);
    b65.Flip(1);
    experis::Bitset<65> b65temp(b65);
    ASSERT_THAT(b65temp.IsOn(63) == true);
    ASSERT_THAT(b65temp.IsOn(64) == true);
    ASSERT_THAT(b65temp.IsOn(0) == true);
    ASSERT_THAT(b65temp.IsOn(1) == true);
END_UNIT

UNIT(BitsetClear)
    experis::Bitset<65> b65;

    b65.Flip(63);
    b65.Flip(64);
    b65.Flip(0);
    b65.Flip(1);
    experis::Bitset<65> b65temp(b65);
    b65.Clear();
    
    ASSERT_THAT(b65.AreAllOff() == true);
    ASSERT_THAT(b65.AreAllOn() == false);
    ASSERT_THAT(b65temp.IsOn(63) == true);
    ASSERT_THAT(b65temp.IsOn(64) == true);
    ASSERT_THAT(b65temp.IsOn(0) == true);
    ASSERT_THAT(b65temp.IsOn(1) == true);
END_UNIT

UNIT(BitsetFill)
    experis::Bitset<65> b65;
    experis::Bitset<65> b65temp(b65);

    std::cout << std::endl << "b65 " << b65 << std::endl;
    ASSERT_THAT(b65.AreAllOff() == true);
    std::cout << "b65 AreAllOff " << b65.AreAllOff() << std::endl;

    b65.Fill();
    std::cout << "b65 after fill: " << std::endl << b65 << std::endl;

    std::cout << "b65 AreAllOff : " << b65.AreAllOff() << std::endl;
    std::cout << "b65 AreAllOn : " << b65.AreAllOn() << std::endl;
    
    ASSERT_THAT(b65.AreAllOff() == false);
    ASSERT_THAT(b65temp.AreAllOn() == false);
    ASSERT_THAT(b65.AreAllOn() == true);
END_UNIT

UNIT(BitsetFilpAllBits)
    experis::Bitset<65> b65;
    b65.Flip(63);
    b65.Flip(64);
    b65.Flip(0);
    b65.Flip(1);
    b65.FlipAll();
END_UNIT

UNIT(BitsetSetAndTowBitset)
    experis::Bitset<64> b1;
    experis::Bitset<64> b2;
    b1.Flip(63);
    b1.Flip(62);
    b1.Flip(0);
    b1.Flip(1);
    b1.FlipAll();
    b2.Flip(63);
    b2.Flip(18);
    b2.Flip(10);
    b2.Flip(28);

    experis::Bitset<64> andBit;
    std::cout << "b2 : " << b2 << std::endl;
    std::cout << "b1 : " << b2 << std::endl;
    andBit = b2 & b1;
    std::cout << "b2 & b1 " << andBit << std::endl;
    std::cout << andBit << std::endl;
    andBit = b1;
    std::cout << "andBit = b1 " << std::endl << andBit << std::endl;
END_UNIT

UNIT(BitsetOperator)
    experis::Bitset<64> b1;
    experis::Bitset<64> b2;
    b1.TurnOn(0);
    b1.TurnOn(8);
    b1.TurnOn(16);
    b1.TurnOn(24);
    b1.TurnOn(32);
    b1.TurnOn(40);
    b1.TurnOn(48);
    b1.TurnOn(56);
    b2.Fill();
    ASSERT_THAT((b1 == b2) == false);
    std::cout << "b1 " << b1 << std::endl;
    std::cout << "b2 " << b2 << std::endl;
    std::cout << "b1 & b2 " << std::endl;
    (b1 & b2).Print();
    std::cout << "b1 | b2" << std::endl;
    (b1 | b2).Print();
    std::cout << "b1 ^ b2 " << std::endl;
    (b1 ^ b2).Print();
    std::cout << "b2 &= b1" << std::endl;
    b2 &= b1;
    std::cout << "b2 ";
    b2.Print();
    b2.Fill();
    std::cout << "b2 |= b1" << std::endl;
    b2 |= b1;
    std::cout << "b2 ";
    b2.Print();
    std::cout << "b2 ^= b1" << std::endl;
    b2 ^= b1;
    std::cout << "b2 ";
    b2.Print();
    std::cout << "~b2 " << std::endl;
    ~b2;
    b2.Print();
    std::cout << "~b1 " << std::endl;
    ~b1;
    b1.Print();
    std::cout << "b1 == b2 : ";
    std::cout << (b1 == b2) << std::endl;
    std::cout << "b1 != b2 : ";
    std::cout << (b1 != b2);
    std::cout << std::endl << std::endl;

    std::cout << "Clear b2";
    std::cout << std::endl;
    b2.Clear();
    std::cout << "b1 ";
    b1.Print();
    std::cout << "b2 ";
    b2.Print();
    std::cout << "b1 & b2 " << std::endl;
    (b1 & b2).Print();
    std::cout << "b1 | b2 " << std::endl;
    (b1 | b2).Print();
    std::cout << "b1 ^ b2 " << std::endl;
    (b1 ^ b2).Print();
    std::cout << "b2 &= b1 " << std::endl;
    b2 &= b1;
    std::cout << "b2 ";
    b2.Print();
    
    std::cout << "b2 |= b1 " << b2 << std::endl;
    b2 |= b1;
	
    std::cout << "b2 ^= b1 " << std::endl;
    b2 ^= b1;
    std::cout << "b2 " << b2 << std::endl;
    ~b2;
    std::cout << "~b2 " << b2 << std::endl;
    ~b1;
    std::cout << "~b1 " << b1 << std::endl;
    std::cout << "b1 == b2 : " << (b1 == b2) << std::endl;
    std::cout << "b1 != b2 : " << (b1 != b2);
END_UNIT

UNIT(BitsetOperatorXor)
	experis::Bitset<5> b1;
    experis::Bitset<5> b2;
    b1.TurnOn(0);
    b1.TurnOn(2);
    b1.TurnOn(4);
    
    b2.TurnOn(1);
    
    experis::Bitset<5> b3;
    b3 = b1 ^ b2;
    std::cout << std::endl << b3 << std::endl;
    std::cout << "b3[0] = " << b3[0] << std::endl;
    std::cout << "b3[3] = " << b3[3] << std::endl;
END_UNIT

TEST_SUITE(Test Bitset)
	TEST(BitsetCTOR)
    TEST(BitsetTurnOn)
    TEST(BitsetTurnOff)
    TEST(BitsetSet)
    TEST(BitsetFlip)
    TEST(BitsetIsOn)
    TEST(BitsetIsAllOff)
    TEST(BitsetIsAllOn)
    TEST(BitsetCopyCTOR)
    TEST(BitsetClear)
    TEST(BitsetFill)
    TEST(BitsetFilpAllBits)
    TEST(BitsetSetAndTowBitset)
    TEST(BitsetOperator)
    TEST(BitsetOperatorXor)
END_SUITE
