#include <iostream>

#include "common.h"

/**
 * Convert a hex character to an integer.
 */
unsigned int _hex_to_int(char c)
{
    unsigned int i = (int)c;

    if (i >= 97 && i <= 102)
    {
        i = i - 97 + 10;
    }
    else if (i >= 48 && i <= 57)
    {
        i -= ((int)'0');
    }
    else
    {
        cout << "Non hex string cannot be parsed." << endl;
        exit(-1);
    }

    return i;
}

/**
 * Convert an integer to hex.
 */
char _int_to_hex(unsigned int i)
{
    char c = (char)i;

    if (i >= 10 && i <= 15)
    {
        c = 'a' + (i - 10);
    }
    else if (i >= 0 && i <= 9)
    {
        c = '0' + i;
    }
    else
    {
        cout << "Not a hex integer." << endl;
        exit(-1);
    }

    return c;
}

/**
 * Convert a string of hex characters to a string of ASCII characters.
 */
void _hex_to_ascii(string& hex_str, string& char_str)
{
    unsigned int i = 0;
    unsigned int hex_str_sz = hex_str.size();
    unsigned int hex_str_limit = hex_str_sz - (hex_str_sz & 0x1);

    while (i < hex_str_limit)
    {
        char_str += (char)((_hex_to_int(hex_str[i]) << 4) | (_hex_to_int(hex_str[i + 1])));
        i += 2;
    }

    if (hex_str_sz & 0x1)
    {
        char_str += (char)(_hex_to_int(hex_str[i]) << 4);
    }
}

