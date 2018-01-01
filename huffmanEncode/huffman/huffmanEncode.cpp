#include "huffmanEncode.h"


huffmanEncode::huffmanEncode()
{
}


huffmanEncode::~huffmanEncode()
{
}
void huffmanEncode::calcuFre(unsigned char *src, sizeType len)
{
	for (sizeType i = 0; i < len; ++i)
	{
		++_afrequency[*src++];
	}
}
