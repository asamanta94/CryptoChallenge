#include <iostream>
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

    file_text.pop_back();

    in_file.close();
}

int main(int argc, char * argv[])
{
    return 0;
}
