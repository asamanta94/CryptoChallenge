#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

#include "crypto_func.h"

using namespace std;

string TEST_STRING = "TEST_BYTES_STRING__";
unsigned char TEST_BYTES[] = {
	0x54, 0x45, 0x53, 0x54, 0x5f, 0x42, 0x59, 0x54, 0x45, 0x53, 0x5f, 0x53, 0x54, 0x52, 0x49, 0x4e,
	0x47, 0x5f, 0x5f, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d
};

TEST_GROUP(ChallengeTestGroup)
{

};

/**
 * Test PKCS#7 padding.
 */
TEST(ChallengeTestGroup, TEST_C9)
{
	unsigned char * bytes_padded = NULL;

	unsigned int bytes_padded_len = pkcs7_padding((unsigned char *) TEST_STRING.c_str(), TEST_STRING.size(), &bytes_padded);

	MEMCMP_EQUAL(TEST_BYTES, bytes_padded, TEST_STRING.size() + 13);

	delete[] bytes_padded;
}

int main(int argc, const char * argv[])
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}