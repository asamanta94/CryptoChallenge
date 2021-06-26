#include <iostream>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "common.h"

using namespace std;

int main(int argc, const char * argv[])
{
	int plaintext_len = 0;
    int len = 0;

    unsigned char * key = (unsigned char *) "YELLOW SUBMARINE";
    unsigned char * plaintext = NULL;

	string base64_string;
	string hex_string;
	string ascii_string;

	EVP_CIPHER_CTX *ctx;

	// Read file
    _read_file((char *) "7.txt", base64_string);

    // Convert text from base64 to hex
    _base64_to_hex(base64_string, hex_string);

    // Convert hex string to ASCII string
    _hex_to_ascii(hex_string, ascii_string);

    plaintext = new unsigned char[ascii_string.length()];

    // Create and initialize the context
    if(!(ctx = EVP_CIPHER_CTX_new()))
        cout << "Error 1" << endl;

    // Decryption Initialization
    if(EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL) != 1)
        cout << "Error 2" << endl;

    // Decrypt text
    if(EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char *)ascii_string.c_str(), ascii_string.length()) != 1)
        cout << "Error 3" << endl;
    plaintext_len = len;

    // Finalize Decryption
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        cout << "Error 4" << endl;
    plaintext_len += len;

    // Free memory
    EVP_CIPHER_CTX_free(ctx);

    cout << plaintext << endl;

    delete[] plaintext;

	return 0;
}