#include <iostream>
#include <map>
#include "common.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

using namespace std;

void initialize_hex_int_map(map<char, int>& hex_to_int_map)
{
    hex_to_int_map['0'] = 0;
    hex_to_int_map['1'] = 1;
    hex_to_int_map['2'] = 2;
    hex_to_int_map['3'] = 3;
    hex_to_int_map['4'] = 4;
    hex_to_int_map['5'] = 5;
    hex_to_int_map['6'] = 6;
    hex_to_int_map['7'] = 7;
    hex_to_int_map['8'] = 8;
    hex_to_int_map['9'] = 9;
    hex_to_int_map['a'] = 10;
    hex_to_int_map['b'] = 11;
    hex_to_int_map['c'] = 12;
    hex_to_int_map['d'] = 13;
    hex_to_int_map['e'] = 14;
    hex_to_int_map['f'] = 15;
}

TEST_GROUP(CommonTestGroup)
{

};

/**
 * Test Hexadecimal String to ASCII String conversion.
 */
TEST(CommonTestGroup, HexToAsciiTest)
{
    string hex_str_even_len = "74657374";
    string hex_str_odd_len = "7465737465";
    string char_str;

    _hex_to_ascii(hex_str_even_len, char_str);

    STRCMP_EQUAL("test", char_str.c_str());

    char_str.clear();

    _hex_to_ascii(hex_str_odd_len, char_str);

    STRCMP_EQUAL("teste", char_str.c_str());
}

/**
 * Test hexadecimal to Integer conversion.
 */
TEST(CommonTestGroup, HexToIntTest)
{
    map<char, int> hex_to_int_map;
    map<char, int>::iterator it;

    initialize_hex_int_map(hex_to_int_map);

    for (it = hex_to_int_map.begin(); it != hex_to_int_map.end(); ++it)
    {
        CHECK_EQUAL(it->second, _hex_to_int(it->first));
    }
}

/**
 * Test Integer to Hexadecimal conversion.
 */
TEST(CommonTestGroup, IntToHexTest)
{
    map<char, int> hex_to_int_map;
    map<char, int>::iterator it;

    initialize_hex_int_map(hex_to_int_map);

    for (it = hex_to_int_map.begin(); it != hex_to_int_map.end(); ++it)
    {
        CHECK_EQUAL(it->first, _int_to_hex(it->second));
    }
}

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
