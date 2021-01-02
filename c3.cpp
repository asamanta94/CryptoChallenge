#include <iostream>

#include "single_byte_xor.h"

using namespace std;

int main(int argc, char * argv[])
{
    char * answer = new char[strlen(argv[1]) / 2];
    decode((char *) argv[1], answer);
    cout << answer << endl;
    return 0;
}
