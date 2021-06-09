#include "hash.hpp"
#include "../mu_test.hpp"
#include <iostream>

bool CompareStrings(const std::string& a_str1, const std::string& a_str2) {
    return a_str1.compare(a_str2) == 0;
}

size_t HashString(const std::string& a_str) {
	return a_str[0];
}

UNIT(test_insert)
	long x = 123;
	long y = 777;
    experis::HashTable table(10, HashString, CompareStrings);
    ASSERT_THAT(table.NumItems() == 0);
    table.Insert("ofir", x);
    try{
    	table.Insert(NULL, x);
    }
    catch(std::logic_error ex) {
    	std::cout << ex.what() << std::endl;
    }
    
    table.Insert("abc", x);
    ASSERT_THAT(table.Exists("ofir") == true);
    ASSERT_THAT(table.Exists("abc") == true);
    ASSERT_THAT(table.Exists("def") == false);
    long& value = table.Find("ofir");

    ASSERT_THAT(value == 123);
    try{
        table.Insert("ofir", y);
    }
    catch(const std::invalid_argument& ex) {
        std::cout << ex.what() << std::endl;
    }
    ASSERT_THAT(table.NumItems() == 2);
END_UNIT


UNIT(test_remove)
    long x = 123;
    experis::HashTable table(10, HashString, CompareStrings);
    table.Insert("ofir", x);
    ASSERT_THAT(table.NumItems() == 1);
    ASSERT_THAT(table.Exists("ofir") == true);
    
    table.Remove("ofir");
    ASSERT_THAT(table.NumItems() == 0);
    ASSERT_THAT(table.Exists("ofir") == false);
    
    try{
        long& value = table.Find("ofir");
    }
    catch(const std::out_of_range& ex) {
        std::cout << ex.what() << std::endl;
    }
    
    try{
        table.Remove("ofir");
    }
    catch(const std::out_of_range& ex) {
        std::cout << ex.what() << std::endl;
    }
    table.Insert("ofir", x);
    ASSERT_THAT(table.Exists("ofir") == true);
END_UNIT

UNIT(test_find)
    long x = 123;
    long y = 777;
    long z = 5;
    long t = 66;
    experis::HashTable table(2, HashString, CompareStrings);
    try {
    	table.Insert("a", x);
    	table.Insert("b", y);
    	table.Insert("c", z);
    	table.Insert("d", t);
    	table.Insert("e", x);
    	ASSERT_THAT(table.NumItems() == 5);
	}
	catch(const std::invalid_argument& ex) {
		std::cout << ex.what() << std::endl;
	}
	
	try{
        long& value = table.Find("b");
    }
    catch(const std::out_of_range& ex) {
        std::cout << ex.what() << std::endl;
    }
    try{
        long& value = table.Find("t");
    }
    catch(const std::out_of_range& ex) {
        std::cout << ex.what() << std::endl;
    }
    
    table.Remove("b");
    try{
        long& value = table.Find("b");
    }
    catch(const std::out_of_range& ex) {
        std::cout << ex.what() << std::endl;
    }
END_UNIT

TEST_SUITE(hashtable_test)
    TEST(test_insert)
    TEST(test_remove)
    TEST(test_find) 
END_SUITE


