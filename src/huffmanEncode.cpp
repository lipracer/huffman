#include <bitset>
#include <fstream>

#include "huffmanEncode.h"
#include "bit_tool.hpp"

using namespace std;
namespace Huffman {

    huffmanEncode::huffmanEncode() 
    {
        memset(m_node, 0, sizeof(m_node));
        memset(m_table, 0, sizeof(m_table));
        for (int i = 0; i < 256; ++i)
        {
            m_pnode[i] = m_node + i;
        }
    }

    huffmanEncode::huffmanEncode(u8 *src, size_t len) : huffmanEncode()
    {
        m_buf = src;
        m_len = len;
    }


    huffmanEncode::~huffmanEncode()
    {
        //delete buf
    }

    int huffmanEncode::InitRes(string filename)
    {
        int err_code = 0;
        m_fin.open(filename, ios::binary | ios::in);
        if (m_fin.is_open())
        {

            m_fin.seekg(0, fstream::end);
            m_len = m_fin.tellg();
            m_fin.seekg(0, fstream::beg);
            m_buf = new u8[MaxBufSize];

        }
        else
        {
            m_len = 0;
            m_buf = nullptr;
            err_code = hf_status::file_open_fail;
        }
        return err_code;
    }

    void huffmanEncode::ReleaseRes() 
    {
        delete m_buf;
        m_fin.close();
    }

    void huffmanEncode::TraverseData(const function<void(u8)>& func)
    {
        int64 remain_count = m_len;
        while (remain_count / MaxBufSize)
        {
            remain_count = remain_count - MaxBufSize;
            m_fin.read((char*)m_buf, MaxBufSize);

            for (size_t i = 0; i < MaxBufSize; i++)
            {
                func(*(m_buf+i));
            }
        }
        m_fin.read((char*)m_buf, remain_count);
        for (size_t i = 0; i < remain_count; i++)
        {
            func(*(m_buf + i));
        }
    }

    void huffmanEncode::calcuFreForBigFile()
    {
        auto func = [this](u8 data)->void 
        {
            m_node[data].freq++;
        };
        TraverseData(func);
    }
    
    inline void huffmanEncode::check_buf_overflow(u64 totalbit)
    {
        static u64 writed_count = 0;
        static u64 max_bit_size = MaxBufSize << 3;//MaxBufSize * 8
        if(totalbit > max_bit_size) //totalbit == max_bit_size no process encode len less eccodevalue size
        {
            writed_count += max_bit_size;
            //write to file
            //TODO
            //
            //
            *((CodeVale*)m_buf) = *((CodeVale*)(m_buf + MaxBufSize));
            memset(m_buf, 0, MaxBufSize + sizeof(CodeVale));
        }
    }

    int huffmanEncode::writeCcompressData(const char* filename)
    {
        //u8 *desBuf = new u8[MaxBufSize + sizeof(CodeVale)];
        u8 *desBuf = new u8[m_len];
        //memset(desBuf, 0, MaxBufSize + sizeof(CodeVale));
        memset(desBuf, 0, m_len);
        int64 totalBits = 0;

        fstream fout(filename, ios::binary | ios::out);

        fout << "HFLL";
        fout.write((char*)&m_len, 8);
        fout.write((char*)&totalBits, 8);
        fout.write((char*)m_table, sizeof(m_table));

        auto func = [this, desBuf, &totalBits, &fout](u8 data)->void
        {
            TableElment& tbElement = m_table[data];
            size_t nT_ = (totalBits / 32) * 4;
            //nT_ = nT_ % MaxBufSize;
            size_t nOverflow = totalBits % (sizeof(CodeVale) * 8);

            writeNBitToBuf((CodeVale*)(desBuf + nT_), nOverflow, tbElement.value, tbElement.valueLen);
            totalBits += tbElement.valueLen;

            //check_buf_overflow(totalBits);
            //if ((nT_ == 1020) && (nOverflow + tbElement.valueLen >= 32))
            //{                    
            //    fout.write((char*)desBuf, MaxBufSize);

            //    CodeVale temp_ = *(desBuf + MaxBufSize);
            //    memset(desBuf, 0, (MaxBufSize + sizeof(CodeVale)));

            //    *(CodeVale*)desBuf = temp_;
            //}
           
        };
        m_fin.seekg(0, fstream::beg);
        TraverseData(func);

        //write remain data

        //u64 remainBits = totalBits % (MaxBufSize << 3);
        //u64 nBytes = remainBits / 8;
        //if (0 != remainBits % 8)
        //{
        //    ++nBytes;
        //}

        u64 nBytes = totalBits / 8;
        if (0 != totalBits % 8)
        {
            ++nBytes;
        }

        fout.write((char*)desBuf, nBytes);
        fout.flush();
        fout.close();
        delete desBuf;

        fout.open(filename, ios::binary | ios::out | ios::in);
        fout.seekp(12, fstream::beg);
        fout.write((char*)&totalBits, 8);
        //fout.write("12345678", 8);
        fout.close();

        return 0;
    }

    void huffmanEncode::calcuFre()
    {
        u64 len =  m_len;
        u8 *cur = m_buf;
        while (0 != len--)
        {
            m_node[*cur++].freq++;
        }
    }

    int huffmanEncode::createTree()
    {
        int validPos = 256;

        LLHeap<TreeNode*, compare1<TreeNode*>> mheap(m_pnode, MUCHAR_MAX + 1);

        TreeNode* firstNoZero = nullptr;
        do
        {
            firstNoZero = mheap.getExtremum();
            if (!mheap.size())
            {
                return -1;
            }
        } while (!firstNoZero->freq);
        mheap.push_back(firstNoZero);

        int lastPosHeap = 0;
        for (; ; )
        {
            mheap.pop_back();
            mheap.pop_back();

            lastPosHeap = mheap.size();
            TreeNode* lnode = m_pnode[lastPosHeap + 1];
            TreeNode* rnode = m_pnode[lastPosHeap];

            lnode->bValue = 0;
            rnode->bValue = 1;
            lnode->parent = m_node + validPos;
            rnode->parent = m_node + validPos;

            m_node[validPos].freq = lnode->freq + rnode->freq;

            TreeNode* nNode = m_node + validPos;

            if (mheap.size() == 0)
            {
                break;
            }

            mheap.push_back(nNode);
            lastPosHeap = mheap.size();
            //m_pnode[lastPosHeap] = nNode;

            ++validPos;

        }
        return 0;
    }

    int huffmanEncode::createTable()
    {
        TreeNode *pCurNode = nullptr;

        for (u32 i = 0; i < 256; i++)
        {
            pCurNode = m_node + i;
            if (nullptr != pCurNode->parent)
            {
                do
                {
                    m_table[i].value = ((m_table[i].value << 1) | pCurNode->bValue);
                    ++m_table[i].valueLen;
                    pCurNode = pCurNode->parent;
                    if (m_table[i].valueLen > sizeof(CodeVale) * 8)
                    {
                        //assert(false);
                    }
                } while (pCurNode->parent);
            }
        }
        return 0;
    }

    u64 huffmanEncode::writeCcompressData(u8* desBuf)
    {
        CodeVale encodeValue = 0;

        u64 totalBits = 0;
        u8* cur = m_buf;
        size_t nT_ = 0;
        size_t nOverflow = 0;
        for (size_t i = 0; i < m_len; ++i)
        {
            TableElment& tbElement = m_table[*cur++];
            nT_ = (totalBits / 32) * 4;
            nOverflow = totalBits % (sizeof(CodeVale)*8);
            writeNBitToBuf((CodeVale*)(desBuf + nT_), nOverflow, tbElement.value, tbElement.valueLen);
            totalBits += tbElement.valueLen;
        }
        return totalBits;
    }

    int huffmanEncode::writeToFile(string filename)
    {
        int retCode = 0;
        fstream fout(filename, ios::binary | ios::out);

        if (fout.is_open())
        {
            u8 *dest = new u8[m_len];
            memset(dest, 0, m_len);

            u64 totalBits = writeCcompressData(dest);

            fout << "HFLL";
            fout.write((char*)&m_len, 8);
            fout.write((char*)&totalBits, 8);
            fout.write((char*)m_table, sizeof(m_table));
            
            u64 nBytes = totalBits / 8;
            if (0 != totalBits % 8)
            {
                ++nBytes;
            }

            fout.write((char*)dest, nBytes);

            delete dest;
            fout.close();
        }
        else
        {
            retCode = -1;
        }
        return retCode;

    }

    void huffmanEncode::printTable()
    {
        double allBitLent = 0;
        for (int i = 0; i < 256; i++)
        {
            bitset<32> bits(m_table[i].value);
            for (int j = 0; j < 32; j++)
            {
                cout << bits[j];
            }
            allBitLent += m_table[i].valueLen * m_node[i].freq;
            cout << " " << m_table[i].valueLen << endl;
        }
        //Average
        cout << "encode length:" << int(allBitLent / 8) << " origin len:" << m_len << endl;
        printf("diff len:%d compress:%0.2f%%\n", m_len - int(allBitLent / 8), (allBitLent / 8 / m_len));
    }

    inline bool cmpCodeValueISEq(CodeVale lvalue, CodeVale rvalue, size_t len)
    {
        CodeVale tmp = -1;
        tmp = (tmp >> (sizeof(CodeVale)*8 - len));
        
        CodeVale tmp1 = (tmp & lvalue);
        CodeVale tmp2 = (tmp & rvalue);
        return  (tmp1 == tmp2);
        //return 0 == (lvalue_ << (sizeof(CodeVale) - len)) ^ (rvalue_ << (sizeof(CodeVale) - len));
    }

    int huffmanDecode(CodeVale* srcBuf, u64 totalBit, huffmanEncode::TableElment* huffmanTB, u8* destBuf)
    {
        CodeVale encodeVale = 0;
        u64 nStartBit = 0;
        u8* destBuf_ = destBuf;
        do {
            encodeVale = getNBitFromBuf(srcBuf, nStartBit);
            size_t i = 0;
            for (; i < 256; i++)
            {
                if (0 != huffmanTB[i].valueLen)
                {
                    if (cmpCodeValueISEq(encodeVale, huffmanTB[i].value, huffmanTB[i].valueLen))
                    {
                        nStartBit += huffmanTB[i].valueLen;
                        *destBuf_++ = i;
                        //cout << "origin:" << i << endl;
                        break;
                    }
                }
            }
            if (256 == i)
            {
                cout << "decode error!" << endl;
                return -1;
            }
            //if (nStartBit %(1024*8) == 0)
            //{
            //    printf("%0.3fKB ", ((nStartBit / 8.0f) / 1024));
            //}
        } while (nStartBit < totalBit);

        return 0;
    }

    int huffmanDecodeFile(string destfilename, string srcfilename)
    {
        int retCode = 0;
        fstream fin(srcfilename, ios::binary | ios::in);

        if (fin.is_open())
        {
            fin.seekg(0, fstream::end);
            u64 file_len = fin.tellg();

            //if (file_len <= sizeof(huffmanEncode::TableElment) * 256 + 8 + 8 + 4)
            //{
            //    fin.close();
            //    throw exception("not huffman encode file!");
            //}

            fin.seekg(4, fstream::beg);

            u64 originFileLen = 0;
            u64 nBits = 0;
            huffmanEncode::TableElment hf_table[256] = { 0 };

            fin.read((char*)&originFileLen, sizeof(u64));
            fin.read((char*)&nBits, sizeof(u64));
            fin.read((char*)hf_table, sizeof(hf_table));

            u64 nByte = nBits / 8;
            if (0 != nBits % 8)
            {
                ++nByte;
            }
            u8 *srcBuf = new u8[nByte];
            u8 *destBuf = new u8[originFileLen+100];

            memset(srcBuf, 0, nByte);
            memset(destBuf, 0, originFileLen + 100);

            fin.read((char*)srcBuf, nByte);

            huffmanDecode((Huffman::CodeVale*)srcBuf, nBits, (huffmanEncode::TableElment*)hf_table, destBuf);


            fstream fout(destfilename, ios::binary | ios::out);
            fout.write((char*)destBuf, originFileLen);

            fin.close();
            fout.close();

            delete srcBuf;
            delete destBuf;
            
        }

        return retCode;
    }
}
