#include "huffmanEncode.h"




huffmanEncode::huffmanEncode()
{
    memset(m_node, 0, sizeof(m_node));
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


void huffmanEncode::createTree()
{
    int validPos = 256;
    
    LLHeap<TreeNode*, compare1<TreeNode*>> mheap(m_pnode, MUCHAR_MAX);
    
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
