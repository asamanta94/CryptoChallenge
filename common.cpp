#include <iostream>

#include "common.h"

#define DEBUG 0

/**
 * Convert a hex character to an integer.
 */
uint8_t _hex_to_int(char c)
{
    uint8_t i = static_cast<uint8_t>(c);

    if (i >= 97 && i <= 102)
    {
        i = i - 97 + 10;
    }
    else if (i >= 48 && i <= 57)
    {
        i -= ((uint8_t)'0');
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

/**
 * Convert a string of ASCII characters to a string of hex characters.
 */
void _ascii_to_hex(string& char_str, string& hex_str)
{
    for (int i = 0; i < char_str.size(); i++)
    {
        hex_str += _int_to_hex((unsigned int)((char_str[i] & 0xF0) >> 4));
        hex_str += _int_to_hex((unsigned int)(char_str[i] & 0x0F));
    }
}

/**
 * Convert a string of hex characters to a series of bytes.
 */
void _hex_to_bytes(char * hex_str, uint8_t * bytes)
{
    // Sanity check - can't convert unless both parameters are non NULL.
    if (!hex_str || !bytes)
    {
        return;
    }

    char * hex_str_iter = hex_str;
    uint8_t * byte = bytes;

    #if DEBUG
        int pos = 0;
        cout << "Converting " << hex_str_iter << " to bytes." << endl << endl;
    #endif

    while ((*hex_str_iter) != '\0')
    {
        // Init memory at the location.
        (*byte) = 0;

        // Take first hex character and left shift the equivalent decimal value by 4.
        (*byte) = _hex_to_int(*hex_str_iter) << 4;

        #if DEBUG
            cout << "First hex character: " << *hex_str_iter << endl;
            cout << "bytes[" << pos << "] = ";
            printf("0x%x\n", *byte);
        #endif

        // If the next character is the end of the hex string, exit.
        hex_str_iter++;
        if (*(hex_str_iter) == '\0')
        {
            #if DEBUG
                cout << "Second hex character: " << '\0' << endl;
                cout << "bytes[" << pos << "] = ";
                printf("0x%x\n\n", *byte);
                pos++;
            #endif

            return;
        }

        // Take the next hex character and or the equivalent decimal value.
        (*byte) = (*byte) | _hex_to_int(*hex_str_iter);

        #if DEBUG
            cout << "Second hex character: " << *hex_str_iter << endl;
            cout << "bytes[" << pos << "] = ";
            printf("0x%x\n\n", *byte);
            pos++;
        #endif

        // Increment memory to access next byte and next 2 hex characters.
        hex_str_iter++;
        byte++;
    }
}

