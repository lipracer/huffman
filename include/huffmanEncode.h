
#ifndef HUFFMANENCODE_H
#define HUFFMANENCODE_H

#include "llctype.h"
#include "heap.hpp"
#include "big_buf.hpp"
#include <string>
#include <functional>

namespace Huffman
{
    typedef unsigned int CodeVale;

    enum hf_status : int
    {
        file_open_fail = 0,
        heap_error,
        hfcode_too_long
    };

    struct TreeNode
    {
        size_t freq;
        u32 bValue;
        u8 charValue;
        TreeNode* parent;
    };

    template<typename T>
    struct compare1
    {
        bool operator()(T lt, T rt)
        {
            return lt->freq < rt->freq;
        }
    };

    template<typename T>
    struct compare2
    {
        bool operator()(T lt, T rt)
        {
            return lt->freq >= rt->freq;
        }
    };

    class huffmanEncode
    {
    public:
        enum valueEnum
        {
            MUCHAR_MAX = 255,
            NodeCount = (256 + 1) * 256 / 2
        };

        struct TableElment
        {
            CodeVale value;
            size_t valueLen;
        };

    public:
        huffmanEncode();
        huffmanEncode(u8 *src, size_t len);
        ~huffmanEncode();
        int InitRes(string filename);
        void ReleaseRes();
        
        void calcuFre();
        void calcuFreForBigFile();
        int createTree();
        int createTable();
        u64 writeCcompressData(u8* desBuf);
        int writeCcompressData(const char* filename);
        int writeToFile(string filename);

        void printTable();
    private:
        void TraverseData(const function<void(u8)>& func);
        inline void check_buf_overflow(u64 totalbit);

    private:
        u8 * m_buf;
        int64 m_len;
        TreeNode m_node[NodeCount];
        TreeNode* m_pnode[NodeCount];
        fstream m_fin;

    public:
        TableElment m_table[256];

    };

    
    //struct fileStruct
    //{
    //    char head[8];
    //    u64 originFileLen;
    //    u64 nBits;
    //    huffmanEncode::TableElment hf_table[256];
    //};

    int huffmanDecode(CodeVale* srcBuf, u64 totalBit, huffmanEncode::TableElment* huffmanTB, u8* destBuf);

    int huffmanDecodeFile(string destfilename, string srcfilename);
}
#endif
