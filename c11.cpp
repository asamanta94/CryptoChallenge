#include <iostream>
#include <cstdlib>
#include <ctime>

#include "crypto_func.h"

using namespace std;

// Generate a random AES key
uint8_t * generate_random_aes_key()
{
	uint8_t * key = new uint8_t[AES_BLOCK_SIZE_BYTES];

	for (int i = 0; i < AES_BLOCK_SIZE_BYTES; i++)
	{
		// rand mod 255 because uint8_t can only hold 8 bits i.e. 0 - 255
		key[i] = static_cast<uint8_t>(rand() % 255);
	}

	return key;
}

int main(int argc, const char * argv[])
{
	return 0;
}