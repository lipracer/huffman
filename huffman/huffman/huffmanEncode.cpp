#include "huffmanEncode.h"


huffmanEncode::huffmanEncode()
{
}


huffmanEncode::~huffmanEncode()
{

}

void huffmanEncode::calcuFre(u8 *src, size_t len)
{
	for (size_t i = 0; i < len; ++i)
	{
		++_afrequency[*src++];
	}
}
