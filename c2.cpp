#include <iostream>

#include "common.h"

using namespace std;

char usage[] = "./out/c2 <s1> <s2>";

char * fixed_xor(char * s1, char * s2)
{
    char * i_s1 = s1;
    char * i_s2 = s2;
    char * result = NULL;
    char * i_result = NULL;

    unsigned int s_len = 0;
    unsigned int res = 0;

    if (!s1 || !s2)
    {
        cout << "NULL strings not allowed." << endl;
        exit(-1);
    }

    s_len = strlen(s1);

    if (s_len != strlen(s2))
    {
        cout << "Hex strings are not equal length." << endl;
        exit(-1);
    }

    result = new char[s_len];
    i_result = result;

    while((*i_s1) != '\0')
    {
        res = _hex_to_int(*i_s1) ^ _hex_to_int(*i_s2);

        *i_result = _int_to_hex(res);

        i_result++;
        i_s1++;
        i_s2++;
    }

    return result;
}

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
