#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <limits>
#include "single_byte_xor.h"
#include "base64_to_hex.h"
#include "common.h"

#define DEBUG 0

/**
 * Get the avg. of hamming distances of a given string and keysize.
 */
static inline double get_avg_hamming_dist_2(string& str, int keysize)
{
    int string_pos = 0;
    int count = 0;

    string str_1;
    string str_2;

    int h_dist = 0;

    while ((string_pos + (2 * keysize)) < str.length())
    {
        str_1.clear();
        str_2.clear();

        str_1 = str.substr(string_pos, keysize);
        str_2 = str.substr(string_pos + keysize, keysize);

        h_dist += _hamming_distance_str(str_1, str_2);
        count++;

        string_pos += keysize;
    }

    double dist = static_cast<double>(h_dist);
    double k_sz = static_cast<double>(keysize);
    double samples = static_cast<double>(count);

    // Normalize this result by dividing by KEYSIZE & number of samples.
    return dist / (samples * k_sz);
}

/** For each KEYSIZE, take the first KEYSIZE worth of bytes, and the second KEYSIZE worth of bytes,
 * and find the edit distance between them.
 */
static inline void decode_repeat_key(string& encoded_text, string& key, string& decoded_text)
{
    int key_pos = 0;
    for (int i = 0; i < encoded_text.length(); i++)
    {
        decoded_text += encoded_text[i] ^ key[key_pos++];
        if (key_pos == key.length())
        {
            key_pos = 0;
        }
    }
}

int main(int argc, char * argv[])
{
    char key_c;
    char * result = NULL;

    int min_dist_keysize = 0;
    int ascii_string_pos = 0;

    double min_dist = numeric_limits<double>::max();
    double curr = 0.0;

    string base64_string;
    string hex_string;
    string ascii_string;
    string possible_key;
    string transposed_str;
    string transposed_block_hex_string;
    string decoded_text;

    vector<string> keysize_set;
    vector<string> transposed_set;

    // Read file
    _read_file((char *) "6.txt", base64_string);

    // Convert text from base64 to hex
    base64_to_hex(base64_string, hex_string);

    // Convert hex string to ASCII string
    _hex_to_ascii(hex_string, ascii_string);

    // Get minimum hamming distance keysize
    for (int KEYSIZE = 2; KEYSIZE <= 40; KEYSIZE++)
    {
        curr = get_avg_hamming_dist_2(ascii_string, KEYSIZE);
        if (curr < min_dist)
        {
            min_dist = curr;
            min_dist_keysize = KEYSIZE;
        }
    }

    cout << "Minimum Hamming Distance Key Size: " << min_dist_keysize << endl << endl;

    // Now that you probably know the KEYSIZE: break the ciphertext into blocks of KEYSIZE length.
    while (ascii_string_pos < ascii_string.length())
    {
        keysize_set.push_back(ascii_string.substr(ascii_string_pos, min_dist_keysize));
        ascii_string_pos += min_dist_keysize;
    }

    /** Create Transposed blocks - The i'th position of the key will decode
     * the ith position of a block.
     */
    for (int col = 0; col < min_dist_keysize; col++)
    {
        transposed_str = "";

        for (int row = 0; row < keysize_set.size(); row++)
        {
            if (col < keysize_set[row].size())
            {
                transposed_str += keysize_set[row][col];
            }
        }

        transposed_set.push_back(transposed_str);
    }

    // Solve each transposed block for the i-th element of the key.
    result = new char[keysize_set.size()];

    for (int i = 0; i < transposed_set.size(); i++)
    {
        transposed_block_hex_string.clear();

        _ascii_to_hex(transposed_set[i], transposed_block_hex_string);

        decode((char *)transposed_block_hex_string.c_str(), result, &key_c);
        possible_key += key_c;
    }

    cout << "Possible Key: " << possible_key << endl << endl;

    // Decode the text with the possible key.
    decode_repeat_key(ascii_string, possible_key, decoded_text);

    cout << "Decoded Text: " << endl << decoded_text;

    // Clear all memory.
    delete[] result;
    base64_string.clear();
    ascii_string.clear();
    hex_string.clear();
    possible_key.clear();
    transposed_str.clear();
    decoded_text.clear();
    transposed_block_hex_string.clear();

    transposed_set.clear();
    keysize_set.clear();

    return 0;
}
