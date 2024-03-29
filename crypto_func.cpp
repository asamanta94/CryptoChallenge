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

unsigned int pkcs7_padding(unsigned char * block, unsigned int block_length, unsigned char ** padded_block)
{
	unsigned int mod = (block_length % AES_BLOCK_SIZE);

	unsigned int len = (mod == 0) ? (block_length + AES_BLOCK_SIZE) : (block_length + AES_BLOCK_SIZE - mod);

	(*padded_block) = add_padding((uint8_t *) block, block_length, len);

	return len;
}

void _handle_errors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int ecb_decrypt(unsigned char * ciphertext, int ciphertext_len, unsigned char * key, unsigned char * iv, unsigned char * plaintext, bool disable_padding)
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

    if (disable_padding)
	{
		EVP_CIPHER_CTX_set_padding(ctx, 0);
	}

    // Decrypt text
    if(EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) != 1)
    {
    	_handle_errors();
        cout << "Couldn't decrypt" << endl;
    }
    plaintext_len = len;

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

int ecb_encrypt(unsigned char * plaintext, int plaintext_len, unsigned char * key, unsigned char * iv, unsigned char * ciphertext, bool disable_padding)
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

	if (disable_padding)
	{
		EVP_CIPHER_CTX_set_padding(ctx, 0);
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

void cbc_decrypt(unsigned char * ciphertext, int clen, unsigned char * iv, string& key, string& out)
{
	unsigned char * plaintext = new unsigned char[AES_BLOCK_SIZE];

	// Key needs to be padded here - for this task, pad according to PKCS#7 padding instead of 0 padding
	unsigned char * key_padded = NULL;
	unsigned int key_padded_len = pkcs7_padding((unsigned char *) key.c_str(), key.size(), &key_padded);

	for (int i = 0; i < (clen / (AES_BLOCK_SIZE)); i++)
	{
		int len = ecb_decrypt(ciphertext + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE, key_padded, NULL, plaintext, true);

		for (int j = 0; j < len; j++)
		{
			out = out + ((char) (plaintext[j] ^ iv[j]));
		}

		memcpy(iv, ciphertext + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE);
	}

	// Unpad the text
	out.erase(out.length() - ((int) out[out.length() - 1]), out.length());

	// Free all allocated memory
	delete[] key_padded;
	delete[] plaintext;
}

int cbc_encrypt(string& plaintext, string& key, unsigned char * iv, unsigned char ** ciphertext)
{
	unsigned char * plaintext_padded = NULL;

	unsigned char * key_padded = NULL;

	// Pad plaintext & key because OpenSSL AES uses PKCS padding and a block size of 16 bytes on both the key and the plaintext
	unsigned int plaintext_padded_len = pkcs7_padding((unsigned char *) plaintext.c_str(), plaintext.size(), &plaintext_padded);

	unsigned int key_padded_len = pkcs7_padding((unsigned char *) key.c_str(), key.size(), &key_padded);

	// Allocate a ciphertext length twize the size of AES_BLOCK_SIZE, because OpenSSL follows PKCS#7 padding
	unsigned char * ciphertext_block = new unsigned char[AES_BLOCK_SIZE];

	// Copy initialization vector to previous ciphertext block
	memcpy(ciphertext_block, iv, AES_BLOCK_SIZE);

	// Allocate memory for ciphertext
	*ciphertext = new unsigned char[plaintext_padded_len];

	int clen = 0;

	for (int i = 0; i < (plaintext_padded_len / AES_BLOCK_SIZE); i++)
	{
		// XOR previous ciphertext block to current plaintext block
		for (int j = 0; j < AES_BLOCK_SIZE; j++)
		{
			plaintext_padded[j + (AES_BLOCK_SIZE * i)] ^= ciphertext_block[j];
		}

		// Encrypt block
		int len = ecb_encrypt(plaintext_padded + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE, key_padded, NULL, ciphertext_block, true);

		// Append ciphertext block to ciphertext
		memcpy((*ciphertext) + clen, ciphertext_block, len);

		clen += len;
	}

	// Free all memory used for encryption
	delete[] plaintext_padded;
	delete[] key_padded;
	delete[] ciphertext_block;

	return clen;
}