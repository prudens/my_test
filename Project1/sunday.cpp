#include "sunday.h"
void sunday ( const char* ori, const char* pat, vector<int> * res )
{
    int i = 0;
    int j = 0;
    int olen = strlen ( ori );
    int plen = strlen ( pat );
    const int max_size = 255;
    int * next = new int[max_size];
    for ( i = 0; i < max_size; ++i ) // 初始化
    {
        next[i] = plen + 1;
    }
    for ( i = 0; i < plen; ++i )
    {
        next[pat[i]] = plen - i;  // 计算偏移量如果有相同的字符那按最右的为准，即覆盖掉前面相同字符的偏移量。
    }
    i = 0;
    while ( i <= olen - plen )
    {
        while ( j < plen )
        {
            if ( ori[i + j] != pat[j] )
            {
                break;
            }
            ++j;
        }
        if ( j == plen )
        {
            ( *res ).push_back ( i );
        }
        j = 0;
        i += next[ori[i + plen]]; // 取下一组第一个字节，看看在匹配串的位置，不存在的都是plen+1
    }
}
