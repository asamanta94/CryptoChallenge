#include <cstdlib>
#include <iostream>

#include "crypto_func.h"

uint8_t * add_padding(uint8_t * block, unsigned int block_length, unsigned int specified_block_length)
{
	if (!block)
	{
		return NULL;
	}

	if (block_length >= specified_block_length)
	{
		return block;
	}

	block = static_cast<uint8_t *>(realloc(block, specified_block_length));

	uint8_t padded_byte = specified_block_length - block_length;

	for (int i = block_length; i < specified_block_length; i++)
	{
		*(block + i) = padded_byte;
	}

	return block;
}