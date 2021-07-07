#include <iostream>

#include "common.h"
#include "crypto_func.h"

using namespace std;

int main(int argc, const char * argv[])
{
	int plaintext_len = 0;

    unsigned char * key = (unsigned char *) "YELLOW SUBMARINE";
    unsigned char * plaintext = NULL;

	string base64_string;
	string hex_string;
	string ascii_string;

	// Read file
    _read_file((char *) "7.txt", base64_string);

    // Convert text from base64 to hex
    _base64_to_hex(base64_string, hex_string);

    // Convert hex string to ASCII string
    _hex_to_ascii(hex_string, ascii_string);

    // Allocate memory for plaintext
    plaintext = new unsigned char[ascii_string.length()];

    // Decrypt
    ecb_decrypt((char *) ascii_string.c_str(), key, plaintext, &plaintext_len);

    cout << plaintext << endl;

    delete[] plaintext;

	return 0;
}