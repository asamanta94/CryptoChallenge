#include <iostream>
#include <vector>
#include <cstdint>

#include <stdio.h>

#include "common.h"
#include "fixed_xor.h"

using namespace std;

/**
 * Single byte XOR decode.
 */
void hex_decode(uint8_t * arr, int len, uint8_t key, uint8_t * result)
{
    for (int i = 0; i < len; i++)
    {
        result[i] = arr[i] ^ key;
    }
}

/**
 * Convert a string of hex characters in to an array of bytes.
 */
uint8_t * hex_str_to_bytes(char * hex_str, unsigned int len)
{
    char * iter = hex_str;

    uint8_t * arr = new uint8_t[len / 2];
    uint8_t * arr_iter = arr;

    while ((*iter) != '\0')
    {
        *arr_iter = 0;
        *arr_iter = _hex_to_int(*iter) << 4;
        *arr_iter = *arr_iter | _hex_to_int(*(iter + 1));

        iter += 2;
        arr_iter++;
    }

    return arr;
}

void decode_hex(uint8_t * arr, unsigned int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << (char) arr[i];
    }

    cout << endl;
}

void decode(char * hex_str)
{
    unsigned int hex_str_len = strlen(hex_str);

    uint8_t * byte_arr = hex_str_to_bytes(hex_str, hex_str_len);
    uint8_t * decoded_str = new uint8_t[hex_str_len / 2];

    for (int i = 0; i < 256; i++)
    {
        hex_decode(byte_arr, hex_str_len / 2, (uint8_t) i, decoded_str);
        decode_hex(decoded_str, hex_str_len / 2);
    }
}

int main(int argc, char * argv[])
{
    decode((char *) argv[1]);
    return 0;
}
