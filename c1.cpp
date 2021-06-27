#include <iostream>

#include "common.h"

using namespace std;

char usage[] = "./out/c1 <hex string>";

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        cout << usage << endl;
        return -1;
    }

    cout << _hex_to_base64(argv[1]) << endl;

    return 0;
}
