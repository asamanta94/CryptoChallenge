#include <cstdlib>
#include <iostream>
#include <string>

#include "common.h"
#include "crypto_func.h"

using namespace std;

char usage[] = "./c9 <string> <specified length>";

int main(int argc, const char * argv[])
{
	if (argc != 3)
	{
		cout << usage << endl;
		return -1;
	}

	unsigned int block_length = strlen(argv[1]);
	unsigned int specified_block_length = atoi(argv[2]);

	uint8_t * block = new uint8_t[block_length];

	memcpy(block, argv[1], block_length);

	block = add_padding(block, block_length, specified_block_length);

	_print_bytes(block, specified_block_length);

	delete[] block;

	return 0;
}