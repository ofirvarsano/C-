#include "hash.hpp"
#include "../mu_test.hpp"
#include <iostream>

typedef experis::HashTable<std::string,long> HashS;
typedef experis::HashIterator<std::string,long> IteratorS;
typedef experis::UniqueKeyList<std::string,long> UniqueList;
typedef experis::Table<std::string,long> TableT;
typedef experis::UniqueKeyList<std::string,long>::ListIter ListIter;
typedef experis::UniqueKeyList<std::string,long>::ListCIter ListCIter;
typedef experis::Item<std::string,long> ItemS;

bool CompareStrings(const std::string& a_str1, const std::string& a_str2) {
    return a_str1.compare(a_str2) == 0;
}

size_t HashString(const std::string& a_str) {
	return a_str[0];
}

void PrintValue(ItemS a_item) {
    std::cout << a_item.GetKey() << std::endl;
}

UNIT(test_insert)
	long x = 123;
	long y = 777;
    HashS table(10, HashString);
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
    HashS table(10, HashString);
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
    HashS table(2, HashString);
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
	
	IteratorS it = table.Begin();
	++it;
	++it;

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


UNIT(iterator)	
	long x = 123;
    long y = 777;
    TableT table(20, HashString);
	//UniqueList uList;
	table.Insert("c", x);
	table.Insert("d", y);
	ASSERT_THAT(table.Exists("c") == true);
	table.Find("c");
	/*table.Remove("c");
	try{
        table.Find("c");
    }
    catch(const std::out_of_range& ex) {
        std::cout << ex.what() << std::endl;
    }*/
    experis::HashIterator<std::string,long> it = table.Begin();
    ItemS item = *it;
    std::cout << item.GetValue() << std::endl;
    it++;
    ItemS item2 = *it;
    std::cout << item2.GetValue() << std::endl;
END_UNIT

UNIT(test_iterator_and_for_each)
    HashS hash(10, HashString);
    
    long x = 123;
    long y = 777;
    long z = 5;
    long t = 66;
    try {
    	hash.Insert("a", x);
    	hash.Insert("b", y);
    	hash.Insert("c", z);
    	hash.Insert("d", t);
    	hash.Insert("e", x);
    	ASSERT_THAT(hash.NumItems() == 5);
	}
	catch(const std::invalid_argument& ex) {
		std::cout << ex.what() << std::endl;
	}
	
    IteratorS beginItr = hash.Begin();
    IteratorS endItr = hash.End();
    std::for_each(beginItr, endItr, PrintValue);
    std::cout << std::endl;

    hash.Remove("c");
    std::for_each(beginItr, endItr, PrintValue);
    std::cout << std::endl;
END_UNIT

UNIT(test_empty_iterator)
    HashS hash(10, HashString);
    
    IteratorS beginItr = hash.Begin();
    IteratorS endItr = hash.End();
    std::for_each(beginItr, endItr, PrintValue);
    
    //beginItr--; //TODO
    beginItr++;
    beginItr++;
    endItr--;
    //endItr++; //TODO
    std::for_each(beginItr, endItr, PrintValue);
END_UNIT

UNIT(test_iterator_print_next)
    HashS hash(10, HashString);
    
    long x = 123;
    long y = 777;
    long z = 5;
    long t = 66;
    try {
    	hash.Insert("a", x);
    	hash.Insert("b", y);
    	hash.Insert("c", z);
    	hash.Insert("d", t);
    	hash.Insert("e", x);
    	ASSERT_THAT(hash.NumItems() == 5);
	}
	catch(const std::invalid_argument& ex) {
		std::cout << ex.what() << std::endl;
	}
	
    IteratorS beginItr = hash.Begin();
    IteratorS endItr = hash.End();
    PrintValue(*beginItr);
    beginItr++;
    PrintValue(*beginItr);
    beginItr++;
    PrintValue(*beginItr);
    beginItr++;
    PrintValue(*beginItr);
    beginItr++;
    PrintValue(*beginItr);
    beginItr++;
    //PrintValue(*beginItr);
END_UNIT

TEST_SUITE(hashtable_test)
	TEST(iterator)
    TEST(test_insert)
    TEST(test_remove)
    TEST(test_find) 
    TEST(test_iterator_and_for_each)
    TEST(test_empty_iterator)
    TEST(test_iterator_print_next)
END_SUITE


