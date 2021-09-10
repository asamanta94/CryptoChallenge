#include <iostream>

#include "common.h"

#define KEY "YELLOW SUBMARINE"

int main(int argc, const char * argv[])
{
	string base64_string;
	string hex_string;
	string ascii_string;

	// Read file
    _read_file((char *) "10.txt", base64_string);

    // Convert text from base64 to hex
    _base64_to_hex(base64_string, hex_string);

    // Convert hex string to ASCII string
    _hex_to_ascii(hex_string, ascii_string);

	return 0;
}