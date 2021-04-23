#include <iostream>

#include "common.h"

using namespace std;

char usage[] = "./out/h2b64 <hex string>";

/**
 * Convert an integer to base64.
 */
void _int_to_base64(unsigned int num, char * base64_string, unsigned int pos)
{
    unsigned int k = 0x00FC0000;
    unsigned int q = 0;

    for (int i = 0; i < 4; i++)
    {
        q = (num & k) >> ((3 - i) * 6);
        k = k >> 6;

        if (q >= 0 && q <= 25)
        {
            base64_string[pos + i] = (char)((int)'A' + q);
        }
        else if (q >= 26 && q <= 51)
        {
            base64_string[pos + i] = (char)((int)'a' + (q - 26));
        }
        else if (q >= 52 && q <= 61)
        {
            base64_string[pos + i] = (char)((int)'0' + (q - 52));
        }
        else if (q == 62)
        {
            base64_string[pos + i] = '+';
        }
        else if (q == 63)
        {
            base64_string[pos + i] = '/';
        }
    }
}

/**
 * Base 64 encoding => Converting data to Base 64.
 *
 * 2 ^ (no. of positions) = (no. of numbers that can be represented)
 * 2 ^ 1 = 2 (0, 1)
 * 2 ^ 2 = 4 [0 - 3]
 * 2 ^ 3 = 8 [0 - 7]
 * ...
 * 2 ^ 6 = 64 [0 - 63] <- Base 64
 *
 */
char * hex_to_base64(char * text)
{
    char * iter = text;
    char * base64_string = new char[strlen(text) * 4 / 6];
    unsigned int num = 0;
    unsigned int count = 0;
    unsigned int c = 0;

    while((*iter) != '\0')
    {
        if (count == 6)
        {
            // We have read 6 hex values, iterate to convert to base 64
            _int_to_base64(num, base64_string, c);
            c += 4;

            // Reset
            num = 0;
            count = 0;
        }

        num = num << 4;
        num = num | (_hex_to_int(*iter) & 0x0000000F);
        count++;
        iter++;
    }

    // We still have something left here
    if (count > 0)
    {
        num = num << (6 - count) * 4;

        _int_to_base64(num, base64_string, c);
        c += 4;

        if (count <= 2)
        {
            // Replace last 2
            base64_string[c - 2] = '=';
            base64_string[c - 1] = '=';
        }
        else if (count <= 4)
        {
            // Replace last
            base64_string[c - 1] = '=';
        }
    }

    base64_string[c] = '\0';

    return base64_string;
}

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        cout << usage << endl;
        return -1;
    }

    cout << hex_to_base64(argv[1]) << endl;

    return 0;
}
