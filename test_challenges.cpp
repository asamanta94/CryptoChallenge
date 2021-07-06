#include <iostream>
#include <vector>
#include <cstdlib>

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

int main(int argc, const char * argv[])
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}