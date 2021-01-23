#include "hamming_distance.h"

unsigned int hamming_distance(string str1, string str2)
{
    char str1_c;
    char str2_c;
    char temp = 0;

    unsigned int hamming_distance = 0;

    // Assuming str1 & str2 are of the same length
    for (int i = 0; i < str1.length(); i++)
    {
        str1_c = str1[i];
        str2_c = str2[i];

        temp = str1_c ^ str2_c;

        for (int j = 0; j < 8; j++)
        {
            hamming_distance += (((temp >> j) & 0x01) == 1) ? 1 : 0;
        }
    }

    return hamming_distance;
}
