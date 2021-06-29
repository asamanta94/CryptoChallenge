#include <cstdlib>
#include <iostream>
#include <string>

#include "common.h"

using namespace std;

char usage[] = "./c9 <string> <specified length>";

uint8_t * add_padding(uint8_t * block, unsigned int block_length, unsigned int specified_length)
{
	if (!block)
	{
		return NULL;
	}

	if (block_length >= specified_length)
	{
		return block;
	}

	block = static_cast<uint8_t *>(realloc(block, specified_length));

	uint8_t padded_byte = specified_length - block_length;

	for (int i = block_length; i < specified_length; i++)
	{
		*(block + i) = padded_byte;
	}

	return block;
}

int main(int argc, const char * argv[])
{
	if (argc != 3)
	{
		cout << usage << endl;
		return -1;
	}

	uint8_t * block = new uint8_t[strlen(argv[1])];

	memcpy(block, argv[1], strlen(argv[1]));

	block = add_padding(block, strlen(argv[1]), atoi(argv[2]));

	_print_bytes(block, atoi(argv[2]));

	return 0;
}