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


#define FILE_SRC "C:\\Users\\Lerlove\\Desktop\\huffman\\star.bmp"
#define FILE_COM "C:\\Users\\Lerlove\\Desktop\\huffman\\_star.bmp"
#define FILE_DES "C:\\Users\\Lerlove\\Desktop\\huffman\\__star.bmp"

using namespace std;
using namespace Huffman;

int parseCmdLine(int argc, char** argvs)
{
    int ret = 0;
    if(argc >= 3)
    {
        if(!strcmp("-c", argvs[1]))
        {
            //printf("curpath:%s file%s\n", argvs[0], argvs[2]);
            u8* buf = nullptr;
            int len = 0;
            
            fstream fin(argvs[2], ios::binary | ios::in);
            if (fin.is_open())
            {
        
                fin.seekg(0, fstream::end);
                len = (int)fin.tellg();
                fin.seekg(0, fstream::beg);
        
                buf = new u8[len];
                fin.read((char*)buf, len);
                fin.close();
                
                huffmanEncode he(buf, len);
                he.calcuFre();
                he.createTree();
                he.createTable();
                he.writeToFile(argvs[3]);
                
                delete buf;
            }
        }
        else if(!strcmp("-u", argvs[1]))
        {
            //printf("curpath:%s file%s %s\n", argvs[0], argvs[2], argvs[3]);
            huffmanDecodeFile(argvs[3], argvs[2]);
        }
        else
        {
            ret = -1;
        }
    }
    else
    {
        ret = -1;
    }
    return ret;;
}

int main(int argc, char** argvs)
{
    //parseCmdLine(argc, argvs);
    //u8* buf = nullptr;
    //int len = 0;
    //fstream fin(FILE_SRC, ios::binary | ios::in);
    //if (fin.is_open())
    //{

    //    fin.seekg(0, fstream::end);
    //    len = (int)fin.tellg();
    //    fin.seekg(0, fstream::beg);

    //    buf = new u8[len];
    //    fin.read((char*)buf, len);
    //    fin.close();

    //    huffmanEncode he(buf, len);
    //    he.calcuFre();
    //    he.createTree();
    //    he.createTable();
    //    he.writeToFile(FILE_COM);

    //    delete buf;
    //}

    huffmanEncode he;
    if (!he.InitRes(FILE_SRC))
    {
        he.calcuFreForBigFile();
        he.createTree();
        he.createTable();

        he.writeCcompressData(FILE_COM);

        he.ReleaseRes();
    }

    huffmanDecodeFile(FILE_DES, FILE_COM);

    system("pause");
    return 0;
}
