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

    EVP_CIPHER_CTX_set_padding(ctx, 0);

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

void cbc_decrypt(unsigned char * ciphertext, int clen, string& key)
{
	unsigned char * plaintext = new unsigned char[AES_BLOCK_SIZE];
	for (int i = 0; i < AES_BLOCK_SIZE; i++)
	{
		plaintext[i] = 0x0;
	}

	string out;

	unsigned char * iv = new unsigned char[AES_BLOCK_SIZE];
	for (int i = 0; i < (AES_BLOCK_SIZE); i++)
	{
		iv[i] = 0x0;
	}

	unsigned char * ct = new unsigned char[clen];
	for (int i = 0; i < clen; i++)
	{
		ct[i] = ciphertext[i];
	}

	unsigned char * lkey = new unsigned char[key.size()];
	for (int i = 0; i < key.size(); i++)
	{
		lkey[i] = key[i];
	}

	unsigned char * block = new unsigned char[AES_BLOCK_SIZE];
	for (int i = 0; i < (AES_BLOCK_SIZE); i++)
	{
		block[i] = ct[i];
	}

	for (int i = 0; i < (clen / (AES_BLOCK_SIZE)); i++)
	{
		int len = ecb_decrypt(ct + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE, lkey, iv, plaintext);

		for (int j = 0; j < len; j++)
		{
			out = out + ((char) (plaintext[j] ^ iv[j]));
		}

		memcpy(iv, ct + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE);
	}

	cout << out << endl;
}

unsigned char * cbc_encrypt(string& text, string& key)
{
	unsigned char * plaintext_padded = NULL;

	// Pad plaintext because OpenSSL AES uses PKCS padding and a block size of 16 bytes
	unsigned int plaintext_padded_len = pkcs7_padding((unsigned char *) text.c_str(), text.size(), &plaintext_padded);

	unsigned char * ptr = plaintext_padded;

	unsigned char * xor_pt = new unsigned char[AES_BLOCK_SIZE];

	unsigned char * prev_ciphertext = new unsigned char[AES_BLOCK_SIZE * 2];

	// Use initialization vector of all 0's
	for (int i = 0; i < (AES_BLOCK_SIZE * 2); i++)
	{
		prev_ciphertext[i] = 0x0;
	}

	// Allocate a ciphertext length twize the size of AES_BLOCK_SIZE, because OpenSSL follows PKCS#7 padding
	unsigned char * ciphertext_block = new unsigned char[AES_BLOCK_SIZE * 2];

	unsigned char * ciphertext = new unsigned char[plaintext_padded_len * 2];

	unsigned char * cptr = ciphertext;

	int clen = 0;

	for (int i = 0; i < (plaintext_padded_len / AES_BLOCK_SIZE); i++)
	{
		// XOR previous ciphertext block to current plaintext block
		for (int j = 0; j < AES_BLOCK_SIZE; j++)
		{
			xor_pt[j] = plaintext_padded[j + (AES_BLOCK_SIZE * i)];
		}

		// Encrypt block
		int len = ecb_encrypt(xor_pt, AES_BLOCK_SIZE, (unsigned char *) key.c_str(), prev_ciphertext, ciphertext_block);

		// Save current ciphertext block as previous ciphertext block
		memcpy(prev_ciphertext, ciphertext_block, len);

		// Append ciphertext block to ciphertext
		memcpy(cptr, ciphertext_block, len);

		// Increment pointer to next block
		ptr += AES_BLOCK_SIZE;

		cptr += len;
		clen += len;
	}

	delete[] plaintext_padded;

	// cbc_decrypt(ciphertext, clen, key);

	return ciphertext;
}