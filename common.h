#ifndef COMMON_H
#define COMMON_H

using namespace std;

uint8_t _hex_to_int(char c);

char _int_to_hex(unsigned int i);

void _hex_to_ascii(string& hex_str, string& char_str);

void _ascii_to_hex(string& char_str, string& hex_str);

void _hex_to_bytes(char * hex_str, uint8_t * bytes);

void _print_bytes(uint8_t * arr, size_t len);

unsigned long long _hamming_distance(uint8_t * arr_1, size_t len_1, uint8_t * arr_2, size_t len_2);

unsigned int _hamming_distance_str(string& str1, string& str2);

void _read_file(char * file_name, string &file_text);

void _base64_to_hex(string& base64_string, string &hex_string);

char * _hex_to_base64(char * text);

unsigned int _base64_to_int(char c);

#endif
