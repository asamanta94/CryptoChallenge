#include <iostream>
#include <fstream>
#include "base64_to_hex.h"
#include "hamming_distance.h"

int KEYSIZE = 0;

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

int main(int argc, char * argv[])
{
    string base64_string;
    string hex_string;

    read_file((char *) "6.txt", base64_string);

    base64_to_hex(base64_string, hex_string);

    cout << hex_string << endl;

    return 0;
}
