#include <iostream>

#include "single_byte_xor.h"

using namespace std;

int main(int argc, char * argv[])
{
    char * answer = new char[strlen(argv[1]) / 2];
    char key = 0;
    decode((char *) argv[1], answer, &key);
    cout << "Text: " << answer << endl;
    return 0;
}
