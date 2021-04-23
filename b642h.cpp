#include <iostream>
#include "base64_to_hex.h"

using namespace std;

char usage[] = "./out/h2b64 <hex string>";

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        cout << usage << endl;
        return -1;
    }

    string hex_string;

    base64_to_hex(argv[1], hex_string);

    cout << hex_string << endl;

    return 0;
}
