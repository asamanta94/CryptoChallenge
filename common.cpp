#include <iostream>

#include "common.h"

using namespace std;

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
