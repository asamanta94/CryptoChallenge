#include <iostream>

#include "repeat_key_xor.h"
#include "common.h"

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
