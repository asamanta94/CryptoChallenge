#ifndef CRYPTO_FUNC_H
#define CRYPTO_FUNC_H

using namespace std;

uint8_t * add_padding(uint8_t * block, unsigned int block_length, unsigned int specified_block_length);

unsigned int pkcs7_padding(unsigned char * block, unsigned int block_length, unsigned char ** padded_block);

int ecb_decrypt(unsigned char * ciphertext, int ciphertext_len, unsigned char * key, unsigned char * iv, unsigned char * plaintext);

int ecb_encrypt(unsigned char * plaintext, int plaintext_len, unsigned char * key, unsigned char * iv, unsigned char * ciphertext);

unsigned char * cbc_encrypt(string& text, string& key);

#endif