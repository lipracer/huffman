#include "huffmanEncode.h"




huffmanEncode::huffmanEncode()
{
    memset(m_node, 0, sizeof(m_node));
    for (int i = 0; i < UCHAR_MAX; ++i)
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
    LLHeap<TreeNode, compare1<TreeNode>> heap((TreeNode*)m_pnode, UCHAR_MAX);
    heap.pop_back();

}
