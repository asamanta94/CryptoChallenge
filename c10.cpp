#include <iostream>

#include "common.h"
#include "crypto_func.h"

#define AES_BLOCK_SIZE_BYTES	16

int main(int argc, const char * argv[])
{
	string base64_string;
	string hex_string;
	string ascii_string;

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

    int plaintext_len = 0;
    unsigned char * pt = new unsigned char[AES_BLOCK_SIZE_BYTES];
    unsigned char * key = new unsigned char[AES_BLOCK_SIZE_BYTES];
    unsigned char * mem = new unsigned char[AES_BLOCK_SIZE_BYTES];

    memcpy(key, "YELLOW SUBMARINE", AES_BLOCK_SIZE_BYTES);

    for (int i = 0; i < AES_BLOCK_SIZE_BYTES; i++)
    {
    	mem[i] = ascii_string[i];
    }

    plaintext_len = ecb_decrypt(mem, strlen((char *)mem), key, NULL, pt);

    delete[] iv;
    delete[] mem;
    delete[] pt;

	return 0;
}