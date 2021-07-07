#ifndef CRYPTO_FUNC_H
#define CRYPTO_FUNC_H

using namespace std;

uint8_t * add_padding(uint8_t * block, unsigned int block_length, unsigned int specified_block_length);

void ecb_decrypt(string& ascii_string, unsigned char * key, unsigned char * plaintext, int * plaintext_len);

#endif