#ifndef CRYPTO_FUNC_H
#define CRYPTO_FUNC_H

#define AES_BLOCK_SIZE_BYTES	16

using namespace std;

uint8_t * add_padding(uint8_t * block, unsigned int block_length, unsigned int specified_block_length);

unsigned int pkcs7_padding(unsigned char * block, unsigned int block_length, unsigned char ** padded_block);

int ecb_decrypt(unsigned char * ciphertext, int ciphertext_len, unsigned char * key, unsigned char * iv, unsigned char * plaintext, bool disable_padding);

int ecb_encrypt(unsigned char * plaintext, int plaintext_len, unsigned char * key, unsigned char * iv, unsigned char * ciphertext, bool disable_padding);

int cbc_encrypt(string& plaintext, string& key, unsigned char * iv, unsigned char ** ciphertext);

void cbc_decrypt(unsigned char * ciphertext, int clen, unsigned char * iv, string& key, string& out);

#endif