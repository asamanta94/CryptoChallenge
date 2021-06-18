#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include "base64_to_hex.h"
#include "hamming_distance.h"

#define DEBUG 1

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

static inline int find_data(vector< pair<int, vector<int> > > &key_data, int d)
{
    for (int i = 0; i < key_data.size(); i++)
    {
        if (key_data[i].first == d)
        {
            return i;
        }
    }

    return -1;
}

bool sort_func(pair<int , vector<int> > &i, pair<int , vector<int> > &j)
{
    return (i.first < j.first);
}

int main(int argc, char * argv[])
{
    string base64_string;
    string hex_string;

    vector< pair<int, vector<int> > > key_data;

    // Read file
    read_file((char *) "6.txt", base64_string);

    // Convert text from base64 to hex
    base64_to_hex(base64_string, hex_string);

    for (int KEYSIZE = 2; KEYSIZE <= 40; KEYSIZE++)
    {
        string str_1 = hex_string.substr(0, KEYSIZE);

        string str_2 = hex_string.substr(KEYSIZE, KEYSIZE);

        int h_dist = hamming_distance(str_1, str_2);

        cout << str_1 << " " << str_2 << " " << h_dist << " " << (h_dist / KEYSIZE) << endl;

        int d = h_dist / KEYSIZE;

        int l = find_data(key_data, d);

        if (l == -1)
        {
            vector<int> keysizes;
            keysizes.push_back(KEYSIZE);

            key_data.push_back(make_pair(d, keysizes));
        }
        else
        {
            key_data[l].second.push_back(KEYSIZE);
        }
    }

    sort(key_data.begin(), key_data.end());

    #if DEBUG
        for (int i = 0; i < key_data.size(); i++)
        {
            cout << key_data[i].first << ": ";

            for (int j = 0; j < key_data[i].second.size(); j++)
            {
                cout << key_data[i].second[j] << " ";
            }

            cout << endl;
        }
    #endif

    // Now that you probably know the KEYSIZE: break the ciphertext into blocks of KEYSIZE length.
    for (int i = 0; i < key_data.size(); i++)
    {
        for (int j = 0; j < key_data[i].second.size(); j++)
        {
            int sz = key_data[i].second[j];
            int k = 0;

            while (k < hex_string.length())
            {
                cout << hex_string.substr(k, sz) << endl;
                k += sz;
            }
        }
    }

    return 0;
}
