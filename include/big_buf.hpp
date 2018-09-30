#ifndef _BIG_HPP_HPP_
#define _BIG_HPP_HPP_
#include <fstream>

#define MaxBufSize 1024

using namespace std;

class RFileBigBuf
{
    typedef unsigned long long int BufSize;
public:
    RFileBigBuf() :m_buf(nullptr), m_buf_len(0), m_buf_cur_pos(0)
    {


    }
    ~RFileBigBuf() { m_fin.close(); }
    int init_buf(const char* filename)
    {
        m_fin.open(filename, ios::binary | ios::in);
        if (m_fin.is_open())
        {

            m_fin.seekg(0, fstream::end);
            m_buf_len = (int)m_fin.tellg();
            m_fin.seekg(0, fstream::beg);

            int new_buf_len = m_buf_len > MaxBufSize ? m_buf_len : MaxBufSize;

            m_buf = new u8[new_buf_len];
            m_fin.read((char*)m_buf, new_buf_len);
            return 0;
        }
        return -1;
    }
    u8 operator*() 
    {
        return *m_buf;
    }
    u8* operator++(int)
    {
        if ((BufSize)(m_buf_cur_pos - m_buf_len) >= MaxBufSize)
        {
            m_buf = m_buf_cur_pos;
            m_fin.read((char*)m_buf, MaxBufSize);

        }
        return m_buf_cur_pos++;
    }
private:
    u8* m_buf;
    u8* m_buf_cur_pos;
    BufSize m_buf_len;
    
    fstream m_fin;
};


class WBigBuf
{

};


#endif