#include <bitset>

#include "huffmanEncode.h"
#include "bit_tool.hpp"

using namespace std;

huffmanEncode::huffmanEncode(u8 *src, size_t len):m_buf(src), m_len(len)
{
    memset(m_node, 0, sizeof(m_node));
    memset(m_table, 0, sizeof(m_table));
    for (int i = 0; i < 256; ++i)
    {
        m_pnode[i] =  m_node + i;
    }
}


huffmanEncode::~huffmanEncode()
{

}

void huffmanEncode::calcuFre()
{
    u8 *end = m_buf + m_len;
    
    for (u8 *cur = m_buf; cur!=end;)
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
    } 
    while (!firstNoZero->freq);
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
                    throw exception("encode value too long!");
                }
            } while (pCurNode->parent);
        }
    }
    return 0;
}

size_t huffmanEncode::writeCcompressData(u8* desBuf)
{
    CodeVale encodeValue = 0;

    size_t totalBits = 0;

    for (size_t i = 0; i < m_len; ++i)
    {
        TableElment& tbElement = m_table[*(m_buf+i)];
        totalBits = writeNBitToBuf((CodeVale*)desBuf, totalBits, tbElement.value, tbElement.valueLen);
    }
    return totalBits;
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
    cout << "encode length:" << int(allBitLent/8) <<" origin len:" << m_len << endl;
    printf("diff len:%d compress:%0.2f%%\n", m_len - int(allBitLent / 8), (allBitLent / 8 / m_len));
}

inline bool cmpCodeValueISEq(CodeVale lvalue, CodeVale rvalue, size_t len)
{
    bitset<sizeof(CodeVale)*8> lbs(lvalue);
    bitset<sizeof(CodeVale)*8> rbs(rvalue);
    size_t i = 0;
    for (; i < len; i++)
    {
        if (lbs[i] != rbs[i])
        {
            break;
        }
    }
    return (i == len);
}

int huffmanDecode(CodeVale* srcBuf, size_t totalBit, huffmanEncode::TableElment* huffmanTB, u8* destBuf)
{
    CodeVale encodeVale = 0;
    size_t nStartBit = 0;

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
                    *destBuf++ = i;
                    //cout << "origin:" << i << endl;
                    break;
                }
            }
        }
        if (256 == i) 
        {
            cout << "decode error!" << endl;
            return - 1;
        }
        //if (nStartBit %(1024*8) == 0)
        //{
        //    printf("%0.3fKB ", ((nStartBit / 8.0f) / 1024));
        //}
    } while (nStartBit < totalBit);

    return 0;
}
