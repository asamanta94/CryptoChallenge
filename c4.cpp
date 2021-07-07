#include <iostream>
#include <fstream>

#include "single_byte_xor.h"

using namespace std;

void c4(char * file_name)
{
    ifstream in_file(file_name);
    if (!in_file.is_open())
    {
        cout << "Couldn't open file: " << file_name << "." << endl;
        return;
    }

    string line;
    char * result = new char[60 / 2];
    char * answer = new char[60 / 2];
    char key;

    unsigned long long score = 0, max_score = 0;

    while (getline(in_file, line))
    {
        score = decode((char *)line.c_str(), result, &key);
        if (score > max_score)
        {
            max_score = score;
            strcpy(answer, result);
        }
    }

    cout << answer << endl;

    in_file.close();
}

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        cout << "l" << endl;
        return -1;
    }

    c4(argv[1]);

    return 0;
}
