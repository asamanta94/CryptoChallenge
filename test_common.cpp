#include <iostream>
#include <map>
#include "common.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

using namespace std;

string TEST_HEX_STRING_1 = "0123456789abcdef";
uint8_t TEST_BYTES_1 [] = {
    0x01,
    0x23,
    0x45,
    0x67,
    0x89,
    0xab,
    0xcd,
    0xef,
};

string TEST_HEX_STRING_2 = "deadbeef";
uint8_t TEST_BYTES_2 [] = {
    0xde,
    0xad,
    0xbe,
    0xef,
};

string TEST_HEX_STRING_3 = "deadbee";
uint8_t TEST_BYTES_3 [] = {
    0xde,
    0xad,
    0xbe,
    0xe0,
};

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

TEST(CommonTestGroup, AsciiToHexTest)
{
    string char_str = "test";
    string hex_str;

    _ascii_to_hex(char_str, hex_str);

    STRCMP_EQUAL("74657374", hex_str.c_str());
}

/**
 * Test Hexadecimal String to byte array conversion.
 */
TEST(CommonTestGroup, HexToBytesTest)
{
    map<string, uint8_t *> test_cases;

    uint8_t * actual_bytes = new uint8_t[10];

    test_cases[TEST_HEX_STRING_1] = TEST_BYTES_1;
    test_cases[TEST_HEX_STRING_2] = TEST_BYTES_2;
    test_cases[TEST_HEX_STRING_3] = TEST_BYTES_3;

    for (map<string, uint8_t *>::iterator it = test_cases.begin(); it != test_cases.end(); ++it)
    {
        _hex_to_bytes((char *) it->first.c_str(), actual_bytes);

        MEMCMP_EQUAL(it->second, actual_bytes, (it->first.length() / 2));
    }

    delete[] actual_bytes;
}

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
