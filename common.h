#ifndef COMMON_H
#define COMMON_H

using namespace std;

uint8_t _hex_to_int(char c);

char _int_to_hex(unsigned int i);

void _hex_to_ascii(string& hex_str, string& char_str);

void _ascii_to_hex(string& char_str, string& hex_str);

void _hex_to_bytes(char * hex_str, uint8_t * bytes);

#endif
