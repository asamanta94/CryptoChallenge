#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>
#include <map>

#include <stdio.h>
#include <math.h>

#include "common.h"
#include "single_byte_xor.h"

using namespace std;

float char_freq_table[26] = {
    0.082,
    0.015,
    0.028,
    0.043,
    0.13,
    0.022,
    0.02,
    0.061,
    0.7,
    0.0015,
    0.0077,
    0.04,
    0.024,
    0.067,
    0.075,
    0.019,
    0.00095,
    0.06,
    0.063,
    0.091,
    0.028,
    0.0098,
    0.024,
    0.0015,
    0.02,
    0.00074
};

/**
 * Single byte XOR decode.
 */
void hex_decode(uint8_t * arr, int len, char key, uint8_t * result)
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

static inline float count_likelihood(char * arr, unsigned int len)
{
    float s = 0;
    int k = 0;

    for (int i = 0; i < len; i++)
    {
        k = (int) arr[i];
        if (k >= 65 && k <= 90)
        {
            s += char_freq_table[k + 32 - 97];
        }
        else if (k >= 97 && k <= 122)
        {
            s += char_freq_table[k - 97];
        }
    }

    return s;
}

static inline void decode_hex(uint8_t * arr, unsigned int len, char * str)
{
    for (int i = 0; i < len; i++)
    {
        str[i] = (char) arr[i];
    }
}

int char_count(char * str, unsigned int * count_arr)
{
    char * iter = str;
    unsigned int idx = 0;
    int ignored = 0;

    while ((*iter) != '\0')
    {
        idx = (unsigned int) *iter;
        // cout << idx << " " << *iter << endl;
        if (idx >= 65 && idx <= 90)
        {
            cout << (char) idx << " ";
            count_arr[idx - 65] = count_arr[idx - 65] + 1;
        }
        else if (idx >= 97 && idx <= 122)
        {
            cout << (char) idx << " ";
            count_arr[idx - 97] = count_arr[idx - 97] + 1;
        }
        else if (idx >= 32 && idx <= 126)
        {
            ignored++;
        }
        else if (idx == 9 || idx == 10 || idx == 13)
        {
            ignored++;
        }

        iter++;
    }

    cout << endl;

    return ignored;
}

void expected_count(double * arr, int len)
{
    for (int i = 0; i < 26; i++)
    {
        arr[i] = len * ((double) char_freq_table[i]);
    }
}

unsigned long long decode(char * hex_str, char * answer, char * key)
{
    map<char, unsigned long long> freq;

    freq[' '] = 700000000;
    freq['e'] = 390395169;
    freq['t'] = 282039486;
    freq['a'] = 248362256;
    freq['o'] = 235661502;
    freq['i'] = 214822972;
    freq['n'] = 214319386;
    freq['s'] = 196844692;
    freq['h'] = 193607737;
    freq['r'] = 184990759;
    freq['d'] = 134044565;
    freq['l'] = 125951672;
    freq['u'] = 88219598;
    freq['c'] = 79962026;
    freq['m'] = 79502870;
    freq['f'] = 72967175;
    freq['w'] = 69069021;
    freq['g'] = 61549736;
    freq['y'] = 59010696;
    freq['p'] = 55746578;
    freq['b'] = 47673928;
    freq['v'] = 30476191;
    freq['k'] = 22969448;
    freq['x'] = 5574077;
    freq['j'] = 4507165;
    freq['q'] = 3649838;
    freq['z'] = 2456495;

    unsigned int hex_str_len = strlen(hex_str);
    unsigned int count_arr[26];

    uint8_t * byte_arr = hex_str_to_bytes(hex_str, hex_str_len);
    uint8_t * decoded_bytes = new uint8_t[hex_str_len / 2];

    char * decoded_str = new char[(hex_str_len / 2) + 1];

    decoded_str[(hex_str_len / 2)] = '\0';

    unsigned long long score = 0;
    unsigned long long max_score = 0;

    for (int i = 0; i < 256; i++)
    {
        hex_decode(byte_arr, hex_str_len / 2, i, decoded_bytes);
        decode_hex(decoded_bytes, hex_str_len / 2, decoded_str);

        score = 0;

        for (int j = 0; j < (hex_str_len / 2); j++)
        {
            int k = decoded_str[j];
            if (k >= 65 && k <= 90)
            {
                k += 32;
                score += freq[(char)k];
            }
            else if (k >= 97 && k <= 122)
            {
                score += freq[(char)k];
            }
            else if (decoded_str[j] == ' ')
            {
                score += freq[' '];
            }
        }

        if (score > max_score)
        {
            max_score = score;
            *key = i;
            strcpy(answer, decoded_str);
        }
    }

    return max_score;
}
