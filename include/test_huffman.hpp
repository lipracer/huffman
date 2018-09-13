#ifndef _TEST_HUFFMAN_HPP_
#define _TEST_HUFFMAN_HPP_
#include <vector>
#include <iostream>

using namespace std;

void getTestBuf(char* &buf, int& len) 
{
    vector<char> dataSource;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < i; j++) 
        {
            dataSource.push_back(i);
        }
    }

    len = dataSource.size();
    buf = new char[len];

    for (int i = 0; i < len; i++)
    {
        buf[i] = dataSource[i];
    }
}



#endif // !_TEST_HUFFMAN_HPP_
