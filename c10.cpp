#include <iostream>

#include "common.h"
#include "crypto_func.h"

int main(int argc, const char * argv[])
{
	string base64_string;
	string hex_string;
	string ascii_string;
    string plaintext;
    string key = "YELLOW SUBMARINE";

    // Create an IV of Zeroes
    unsigned char * iv = new unsigned char[AES_BLOCK_SIZE_BYTES];
    memset(iv, 0x0, AES_BLOCK_SIZE_BYTES);

	// Read file
    _read_file((char *) "10.txt", base64_string);

    // Convert text from base64 to hex
    _base64_to_hex(base64_string, hex_string);

    // Convert hex string to ASCII string
    _hex_to_ascii(hex_string, ascii_string);

    // decrypt
    cbc_decrypt((unsigned char *) ascii_string.c_str(), ascii_string.size(), iv, key, plaintext);

    cout << plaintext << endl;

    // Free memory
    delete[] iv;

	return 0;
}