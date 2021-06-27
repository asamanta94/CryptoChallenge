#include <iostream>
#include <fstream>

#include "common.h"

using namespace std;

string usage = "./c5 <file name>";

string repeat_key_xor(string text, string key)
{
    int key_length = key.length();
    int counter = 0;

    string encrypted_text;

    char c_text;
    char c_key;
    char c_encrypt;

    for (int i = 0; i < text.length(); i++)
    {
        c_text = text[i];
        c_key = key[counter];

        // XOR
        c_encrypt = c_text ^ c_key;

        encrypted_text += _int_to_hex((c_encrypt & 0xF0) >> 4);
        encrypted_text += _int_to_hex(c_encrypt & 0x0F);

        counter++;
        if (counter == key_length)
        {
            counter = 0;
        }
    }

    return encrypted_text;
}

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
        text += '\n';
    }

    text.pop_back();

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
