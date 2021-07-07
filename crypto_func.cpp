#include <cstdlib>
#include <iostream>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "crypto_func.h"

using namespace std;

uint8_t * add_padding(uint8_t * block, unsigned int block_length, unsigned int specified_block_length)
{
	if (!block)
	{
		return NULL;
	}

	if (block_length >= specified_block_length)
	{
		return block;
	}

	uint8_t * padded_block = new uint8_t[specified_block_length];

	memcpy(padded_block, block, block_length);

	uint8_t padded_byte = specified_block_length - block_length;

	memset(padded_block + block_length, padded_byte, padded_byte);

	return padded_block;
}

void ecb_decrypt(string& ascii_string, unsigned char * key, unsigned char * plaintext, int * plaintext_len)
{
    int len = 0;

	EVP_CIPHER_CTX *ctx;

	// Create and initialize the context
    if(!(ctx = EVP_CIPHER_CTX_new()))
        cout << "Couldn't create context" << endl;

    // Decryption Initialization
    if(EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL) != 1)
        cout << "Couldn't initialize for decryption" << endl;

    // Decrypt text
    if(EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char *)ascii_string.c_str(), ascii_string.length()) != 1)
        cout << "Couldn't decrypt" << endl;
    *plaintext_len = len;

    // Finalize Decryption
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        cout << "Couldn't finalize decryption" << endl;
    *plaintext_len += len;

    // Free memory
    EVP_CIPHER_CTX_free(ctx);
}

void cbc(string& text, string& key)
{

}