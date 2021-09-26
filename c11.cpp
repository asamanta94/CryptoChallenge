#include <iostream>
#include <cstdlib>
#include <ctime>

#include "crypto_func.h"

using namespace std;

// Generate a random AES key
byte * generate_random_aes_key()
{
	byte * key = new byte[AES_BLOCK_SIZE_BYTES];

	for (int i = 0; i < AES_BLOCK_SIZE_BYTES; i++)
	{
		// rand mod 255 because uint8_t can only hold 8 bits i.e. 0 - 255
		key[i] = static_cast<byte>(rand() % 255);
	}

	return key;
}

// Generate a random IV
byte * generate_random_iv()
{
	byte * iv = new byte[AES_BLOCK_SIZE_BYTES];

	for (int i = 0; i < AES_BLOCK_SIZE_BYTES; i++)
	{
		// rand mod 255 because uint8_t can only hold 8 bits i.e. 0 - 255
		iv[i] = static_cast<byte>(rand() % 255);
	}

	return iv;
}

void modify_plaintext(string& plaintext)
{
}

// Encrypt
void random_encrypt(string& plaintext, uint8_t * key)
{
	uint8_t mode = static_cast<uint8_t>(rand() % 2);

	if (mode == MODE_ECB)
	{

	}
	else
	{
	}
}

int main(int argc, const char * argv[])
{

	return 0;
}