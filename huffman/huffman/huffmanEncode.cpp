#include "huffmanEncode.h"

 bool compare1(TreeNode *lt, TreeNode *rt)
 {
     return lt->freq < rt->freq;
 }
 bool compare2(TreeNode *lt, TreeNode *rt)
 {
     return lt->freq >= rt->freq;
 }


huffmanEncode::huffmanEncode()
{

}


huffmanEncode::~huffmanEncode()
{

}

void huffmanEncode::calcuFre(u8 *src, size_t len)
{
	for (size_t i = 0; i < UCHAR_MAX; ++i)
	{
		_apNode[i] = _bTree+i;
	}

	for (size_t i = 0; i < len; ++i)
	{
		_bTree[*src].chrValue = *src;
		++_bTree[*src++];
	}
}


void huffmanEncode::createTree()
{
	LLHeap<TreeNode*> mheap(_apNode, UCHAR_MAX);

	int min1 = -1, min2 = -1;



	for(;;)
	{

		do{
			min1 = mheap.getExtremum();
		}
		while(0 == _bTree[min1].freq);//怎么去掉这个判断？？？？？？？？？

		min2 = mheap.getExtremum();

		_bTree[min1].bValue = 0;
		_bTree[min2].bValue = 1;

		TreeNode node;
		node.freq = _bTree[min1].freq + _bTree[min2].freq;

		_bTree.push_back(node);

		_bTree[min1].parent = _bTree.size() - 1;
		_bTree[min2].parent = _bTree.size() - 1;

		if(0 == mheap.size())
		{
			break;
		}

		mheap.push_back(_bTree.size() - 1);
	}


}