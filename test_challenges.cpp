#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

#include "crypto_func.h"

using namespace std;

string TEST_STRING = "YELLOW SUBMARINE";
uint8_t TEST_BYTES[] = {
	0x59, 
	0x45, 
	0x4c, 
	0x4c, 
	0x4f, 
	0x57, 
	0x20, 
	0x53, 
	0x55, 
	0x42, 
	0x4d, 
	0x41, 
	0x52, 
	0x49, 
	0x4e, 
	0x45,
	0x04,
	0x04,
	0x04,
	0x04
};

TEST_GROUP(ChallengeTestGroup)
{

};

/**
 * Test PKCS#7 padding.
 */
TEST(ChallengeTestGroup, TEST_C9)
{
	uint8_t * bytes = new uint8_t[TEST_STRING.size()];

	memcpy(bytes, TEST_STRING.c_str(), TEST_STRING.size());

	uint8_t * bytes_padded = add_padding(bytes, TEST_STRING.size(), TEST_STRING.size() + 4);

	MEMCMP_EQUAL(TEST_BYTES, bytes_padded, TEST_STRING.size() + 4);

	delete[] bytes_padded;

	delete[] bytes;
}

/**
 * Test ECB mode encryption and decryption.
 */
TEST(ChallengeTestGroup, TEST_ENCRYPT)
{
	unsigned char * plaintext = (unsigned char *) "The quick brown fox jumps over the lazy dog";
	unsigned char * key = (unsigned char *) "key";
	unsigned char * ciphertext = new unsigned char[strlen((char *) plaintext)];

	int len = 0;

	int ciphertext_len = ecb_encrypt(plaintext, strlen((char *) plaintext), key, NULL, ciphertext);

	unsigned char * pt = new unsigned char[ciphertext_len];

	ecb_decrypt((char *) ciphertext, ciphertext_len, key, pt, &len);

	// Have to append the NULL character because OpenSSL won't do it automatically.
	*(pt + len) = '\0';

	MEMCMP_EQUAL(plaintext, pt, len);

	// delete[] ciphertext;
}

int main(int argc, const char * argv[])
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}