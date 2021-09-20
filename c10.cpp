#include <iostream>

#include "common.h"
#include "crypto_func.h"

#define AES_BLOCK_SIZE_BYTES	16

string TEST_PLAINTEXT = "The quick brown fox jumps over the lazy dog";
string TEST_KEY = "key";

int main(int argc, const char * argv[])
{
	string base64_string;
	string hex_string;
	string ascii_string;
    string key = "YELLOW SUBMARINE";

	// Read file
    _read_file((char *) "10.txt", base64_string);

    // Convert text from base64 to hex
    _base64_to_hex(base64_string, hex_string);

    // Convert hex string to ASCII string
    _hex_to_ascii(hex_string, ascii_string);

    // Create an IV of Zeroes
    unsigned char * iv = new unsigned char[AES_BLOCK_SIZE_BYTES];
    for (int i = 0; i < AES_BLOCK_SIZE_BYTES; i++)
    {
    	iv[i] = 0x0;
    }

    unsigned char * ct = cbc_encrypt(TEST_PLAINTEXT, TEST_KEY);

    string out;

    cbc_decrypt(ct, strlen((char *) ct), TEST_KEY, out);

    cout << out << endl;

    string out2;

    cbc_decrypt((unsigned char *) ascii_string.c_str(), ascii_string.size(), key, out2);

	return 0;
}