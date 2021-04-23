#include <iostream>
#include <string>
#include <fstream>

#include "common.h"

#define DEBUG   0

using namespace std;

/**
 * Convert an base64 character to an integer.
 */
unsigned int base64_to_int(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A';
    }
    else if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 26;
    }
    else if (c >= '0' && c <= '9')
    {
        return c - '0' + 52;
    }
    else if (c == '+')
    {
        return 62;
    }
    else if (c == '/')
    {
        return 63;
    }
    else if (c == '=')
    {
        return 0;
    }

    exit(-1);
}

/**
 * Convert an base64 string to a hex string.
 */
void base64_to_hex(string base64_string, string &hex_string)
{
    unsigned int count = 0;
    unsigned int rolling_num = 0;
    unsigned int padding_count = 0;
    unsigned int mask = 0x00FF0000;

    char * c = (char *)base64_string.c_str();

    for (int i = 0; i < base64_string.length(); i++)
    {
        if (count == 4)
        {
            // We have 24 bits. Convert to hex.
            for (int j = 0; j < 3; j++)
            {
                count = rolling_num & (mask >> (8 * j));
                count = count >> (8 * (2 - j));
                hex_string += _int_to_hex((count & 0x000000F0) >> 4);
                hex_string += _int_to_hex(count & 0x0000000F);
            }

            count = 0;
        }

        rolling_num = rolling_num << 6;
        rolling_num = rolling_num | base64_to_int(*c);
        if (*c == '=') padding_count++;
        count++;
        c++;
    }

    if (count > 0)
    {
        #if DEBUG
            cout << padding_count << endl;
        #endif

        int k = (padding_count == 1) ? 2 : 1;
        for (int i = 0; i < k; i++)
        {
            count = rolling_num & (mask >> (8 * i));
            count = count >> (8 * (2 - i));
            hex_string += _int_to_hex((count & 0x000000F0) >> 4);
            hex_string += _int_to_hex(count & 0x0000000F);
        }
    }

#if DEBUG
    cout << hex_string << endl;
#endif

}
