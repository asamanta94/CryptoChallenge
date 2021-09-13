#include <cstdlib>
#include <iostream>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>

#include "crypto_func.h"

using namespace std;

uint8_t * add_padding(uint8_t * block, unsigned int block_length, unsigned int specified_block_length)
{
	if (!block)
	{
		return NULL;
	}

	if (block_length > specified_block_length)
	{
		return block;
	}

	uint8_t * padded_block = new uint8_t[specified_block_length];

	memcpy(padded_block, block, block_length);

	uint8_t padded_byte = specified_block_length - block_length;

	memset(padded_block + block_length, padded_byte, padded_byte);

	return padded_block;
}

unsigned char * pkcs7_padding(unsigned char * block, unsigned int block_length)
{
	unsigned int remaining_bytes = block_length % AES_BLOCK_SIZE;

	unsigned int len = (remaining_bytes == 0) ? (block_length + AES_BLOCK_SIZE) : block_length;

	return (unsigned char *) add_padding((uint8_t *) block, block_length, len);
}

void _handle_errors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int ecb_decrypt(unsigned char * ciphertext, int ciphertext_len, unsigned char * key, unsigned char * iv, unsigned char * plaintext)
{
    int len = 0;
    int plaintext_len = 0;

	EVP_CIPHER_CTX *ctx;

	// Create and initialize the context
    if(!(ctx = EVP_CIPHER_CTX_new())) {
    	_handle_errors();
        cout << "Couldn't create context" << endl;
    }

    // Decryption Initialization
    if(EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv) != 1)
    {
    	_handle_errors();
        cout << "Couldn't initialize for decryption" << endl;
    }

    // Decrypt text
    if(EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) != 1)
    {
    	_handle_errors();
        cout << "Couldn't decrypt" << endl;
    }
    plaintext_len = len;

    cout << "PT: " << plaintext << endl;
    cout << "LEN: " << plaintext_len << endl;
    cout << "LEN2: " << strlen((char *)plaintext) << endl;

    // Finalize Decryption
    if(EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1)
    {
    	_handle_errors();
        cout << "Couldn't finalize decryption" << endl;
    }
    plaintext_len += len;

    // Free memory
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

int ecb_encrypt(unsigned char * plaintext, int plaintext_len, unsigned char * key, unsigned char * iv, unsigned char * ciphertext)
{
	EVP_CIPHER_CTX *ctx;

	int len;

	int ciphertext_len;

	// Create and initialize the context
	if(!(ctx = EVP_CIPHER_CTX_new()))
	{
		_handle_errors();
	    cout << "Couldn't create context" << endl;
	}

	// Encryption Initialization
	if(EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv) != 1)
	{
		_handle_errors();
	    cout << "Couldn't initialize for encryption" << endl;
	}

	// Encrypt text
	if(EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) != 1)
	{
		_handle_errors();
	    cout << "Couldn't encrypt" << endl;
	}
	ciphertext_len = len;

	// Finalize encryption
	if(EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1)
	{
		_handle_errors();
		cout << "Couldn't finalize encryption" << endl;
	}
	ciphertext_len += len;

	// Clean up
	EVP_CIPHER_CTX_free(ctx);

	return ciphertext_len;
}

void cbc_encrypt(string& text, string& key)
{
	char * plaintext = (char *) text.c_str();

	unsigned char * mem = new unsigned char[text.size()];
}