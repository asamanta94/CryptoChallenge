#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include "single_byte_xor.h"
#include "base64_to_hex.h"
#include "common.h"

#define DEBUG 1

/**
 * Read a file and get the text.
 */
void read_file(char * file_name, string &file_text)
{
    ifstream in_file(file_name);
    if (!in_file.is_open())
    {
        cout << "Couldn't open file: " << file_name << "." << endl;
        return;
    }

    string line;

    while (getline(in_file, line))
    {
        file_text += line;
    }

    in_file.close();
}

/**
 * Get the avg. of hamming distances of a given string and keysize.
 */
static inline double get_avg_hamming_dist(string& str, int keysize)
{
    string str_1 = str.substr(keysize, keysize);
    string str_2 = str.substr(2 * keysize, keysize);
    string str_3 = str.substr(3 * keysize, keysize);
    string str_4 = str.substr(4 * keysize, keysize);

    int h_dist = 0;
    h_dist = _hamming_distance_str(str_1, str_2);
    h_dist += _hamming_distance_str(str_2, str_3);
    h_dist += _hamming_distance_str(str_3, str_4);

    double dist = static_cast<double>(h_dist);
    double k_sz = static_cast<double>(keysize);

    // Normalize this result by dividing by KEYSIZE.
    return dist / (3.0 * k_sz);
}

int main(int argc, char * argv[])
{
    int h_dist = 0;
    char key_c;

    char * result = NULL;

    double dist = 0.0;
    double k_sz = 0.0;
    double n = 3.0;

    string base64_string;
    string hex_string;
    string ascii_string;
    string possible_key;
    string transposed_str;
    string transposed_block_hex_string;

    // For averaging
    string str_1, str_2, str_3, str_4;

    vector<string> keysize_set;
    vector<string> transposed_set;

    // Map for storing hamming distance and list of keysizes.
    map < double, vector<int> > key_data;

    // Read file
    read_file((char *) "6.txt", base64_string);

    // Convert text from base64 to hex
    base64_to_hex(base64_string, hex_string);

    // Convert hex string to ASCII string
    _hex_to_ascii(hex_string, ascii_string);

    // For each KEYSIZE, take the first KEYSIZE worth of bytes, and the second KEYSIZE worth of bytes, 
    // and find the edit distance between them.
    for (int KEYSIZE = 2; KEYSIZE <= 40; KEYSIZE++)
    {
        // Normalize this result by dividing by KEYSIZE.
        key_data[get_avg_hamming_dist(ascii_string, KEYSIZE)].push_back(KEYSIZE);
    }

    #if DEBUG
        cout << "Hamming Distance : Keysizes" << endl;
        for (map<double, vector<int> >::iterator it = key_data.begin(); it != key_data.end(); ++it)
        {
            cout << it->first << " : ";

            for (int i = 0; i < it->second.size(); i++)
            {
                cout << it->second[i] << " ";
            }

            cout << endl;
        }
        cout << endl;
    #endif


    // Now that you probably know the KEYSIZE: break the ciphertext into blocks of KEYSIZE length.
    int sample_count = 0;
    int curr_key_sz = 0;
    int ascii_string_pos = 0;
    unsigned long long score = 0, max_score = 0;

    for (map<double, vector<int> >::iterator it = key_data.begin(); it != key_data.end(); ++it)
    {
        if (sample_count >= 2)
        {
            break;
        }

        #if DEBUG
            cout << "Current Avg. Hamming Distance: " << curr_key_sz << endl;
        #endif

        for (int j = 0; j < it->second.size(); j++)
        {
            ascii_string_pos = 0;
            curr_key_sz = it->second[j];

            #if DEBUG
                cout << "Current Key Size: " << curr_key_sz << endl;
            #endif

            // Create blocks of keysize length.
            while (ascii_string_pos < ascii_string.length())
            {
                keysize_set.push_back(ascii_string.substr(ascii_string_pos, curr_key_sz));
                ascii_string_pos += curr_key_sz;
            }

            /** Create Transposed blocks - The i'th position of the key will decode
             * the ith position of a block.
             */
            for (int col = 0; col < curr_key_sz; col++)
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

            /** Solve each transposed block for the i-th element of the key.
             */
            result = new char[keysize_set.size()];

            for (int l = 0; l < transposed_set.size(); l++)
            {
                transposed_block_hex_string.clear();

                _ascii_to_hex(transposed_set[l], transposed_block_hex_string);

                decode((char *)transposed_block_hex_string.c_str(), result, &key_c);
                possible_key += key_c;
            }

            // Clear all memory.
            delete[] result;
            possible_key.clear();
            keysize_set.clear();
            transposed_set.clear();
        }

        sample_count++;

        cout << endl;
    }

    key_data.clear();

    return 0;
}
