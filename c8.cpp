#include <iostream>
#include <vector>

#include "common.h"

#define BLOCK_SIZE 					16
#define HEX_BLOCK_SIZE BLOCK_SIZE * 2

/**
 * Check if text is encoded with AES ECB.
 */
bool is_ecb(string& line)
{
	bool ecb = false;

	char * line_char = (char *)line.c_str();

	/** Check if some or any 32 byte block is the same.
	 * 32 bytes because it's a hex string i.e. 2 hex values
	 * will make one byte and we need 32 of those hex values to
	 * make a 16 - byte block - which we're assuming in the key size. 
	 */
	for (int i = 0; i < line.size(); i += HEX_BLOCK_SIZE)
	{
		for (int j = i + HEX_BLOCK_SIZE; j < line.size(); j += HEX_BLOCK_SIZE)
		{
			if (!memcmp(line_char + i, line_char + j, HEX_BLOCK_SIZE))
			{
				ecb = true;
				break;
			}
		}
	}

	return ecb;
}

int main(int argc, const char * argv[])
{
	vector<string> lines;

	// Read lines of the file
	_read_file_lines((char *) "8.txt", lines);

	for (int i = 0; i < lines.size(); i++)
	{
		if (is_ecb(lines[i]))
		{
			cout << "ECB encryption detected: " << lines[i] << endl;
		}
	}

	// Clear memory
	lines.clear();

	return 0;
}