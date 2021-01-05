#include <iostream>
#include <fstream>

#include "repeat_key_xor.h"

using namespace std;

string usage = "./c5 <file name>";

void encrypt(char * file_name)
{
    ifstream in_file(file_name);
    if (!in_file.is_open())
    {
        cout << "Couldn't open file: " << file_name << "." << endl;
        return;
    }

    string line;
    string text;

    while (getline(in_file, line))
    {
        text += line;
    }

    cout << repeat_key_xor(text, "ICE") << endl;

    in_file.close();
}

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        cout << usage << endl;
        return -1;
    }

    encrypt((char *) argv[1]);

    return 0;
}
