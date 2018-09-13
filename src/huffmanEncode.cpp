#include "huffmanEncode.h"
#include <bitset>
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
    
    LLHeap<TreeNode*, compare1<TreeNode*>> mheap(m_pnode, MUCHAR_MAX);

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
        if (!pCurNode->parent)
        {
            continue;
        }
        u32 curBitPos = 0;
        do
        {
            m_table[i].value = (m_table[i].value | (pCurNode->bValue << curBitPos++));
            ++m_table[i].valueLen;
            pCurNode = pCurNode->parent;
        } while (pCurNode->parent);

    }
    return 0;
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
    printf("diff len:%d compress:%0.2f%\n", m_len - int(allBitLent / 8), (allBitLent / 8 / m_len));
}
