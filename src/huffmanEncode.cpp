#include "huffmanEncode.h"

huffmanEncode::huffmanEncode()
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

void huffmanEncode::calcuFre(u8 *src, size_t len)
{
    u8 *end = src + len;
    
    for (u8 *cur = src; cur!=end;)
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

    for (; ; )
    {
        mheap.pop_back();
        mheap.pop_back();
        
        TreeNode& lnode = m_node[mheap.size()+1];
        TreeNode& rnode = m_node[mheap.size()];
        
        lnode.bValue = 0;
        rnode.bValue = 1;
        lnode.parent = m_node + validPos;
        rnode.parent = m_node + validPos;
        m_node[validPos].freq = lnode.freq + rnode.freq;
        
        TreeNode* nNode = m_node + validPos;
        mheap.push_back(nNode);
        
        ++validPos;
        
        if(mheap.size() < 2)
        {
            break;
        }
    }
}

int huffmanEncode::createTable() 
{
    TreeNode *pCurNode = nullptr;
    
    for (size_t i = 0; i < 256; i++)
    {
        pCurNode = m_node + i;
        if (!pCurNode->parent)
        {
            continue;
        }
        CodeVale codeValue = 0;
        int curBitPos = 0;
        do
        {
            codeValue = codeValue | pCurNode->bValue << curBitPos++;
            ++m_table[i].valueLen;
            pCurNode = pCurNode->parent;
        } while (!pCurNode);

    }
    return 0;
}
