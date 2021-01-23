#include "hamming_distance.h"

string usage = "./c6_hamm <str1> <str2>";

int main(int argc, char * argv[])
{
    if (argc != 3)
    {
        cout << usage << endl;
        return -1;
    }

    cout << hamming_distance(argv[1], argv[2]) << endl;
    cout << hamming_distance("this is a test", "wokka wokka!!!") << endl;

    return 0;
}
