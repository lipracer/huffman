//
//  main.cpp
//  test_huffman
//
//  Created by multimedia on 2018/9/11.
//  Copyright © 2018年 ___multiMedia___. All rights reserved.
//

#include <cstdio>
#include <cstdlib>

#include <random>
#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>
#include <bitset>

#include "test_heap.hpp"
#include "test_huffman.hpp"
#include "huffmanEncode.h"

using namespace std;

int main()
{
    // insert code here...
    //test_heap();

    u8* buf = nullptr;
    int len = 0;

    getTestBuf(buf, len);

#if true
    fstream fin("C:\\Users\\Lerlove\\Desktop\\huffman\\Design.pdf", ios::binary | ios::in);

    if (fin.is_open()) 
    {
 
        fin.seekg(0, ios::_Seekend);
        len = fin.tellg();
        fin.seekg(0, ios::_Seekbeg);

        buf = new u8[len];
        fin.read((char*)buf, len);
        fin.close();
    }
#endif


    huffmanEncode he(buf, len);
    he.calcuFre();
    he.createTree();

    try {
        he.createTable();
        //he.printTable();

        u8 *dest = new u8[len];
        memset(dest, 0, len);
        size_t totalBits = he.writeCcompressData(dest);
        

        u8 *dest_origin = new u8[len];
        memset(dest_origin, 0, len);
        huffmanDecode((CodeVale*)dest, totalBits, he.m_table, dest_origin);

        delete dest;

#if true
        fstream fout("C:\\Users\\Lerlove\\Desktop\\huffman\\Design_.pdf", ios::binary | ios::out);

        if (fout.is_open())
        {
            fout.write((char*)dest_origin, len);
            fout.close();
        }
        
#endif
        delete dest_origin;

    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    delete buf;
    system("pause");
    return 0;
}
