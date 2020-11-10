#include <iostream>

#include "fixed_xor.h"

using namespace std;

char usage[] = "./out/fxor <s1> <s2>";

int main(int argc, char * argv[])
{
    if (argc != 3)
    {
        cout << usage << endl;
        return -1;
    }

    cout << fixed_xor(argv[1], argv[2]) << endl;

    return 0;
}
