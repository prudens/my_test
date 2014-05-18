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

        // 取下一组第一个字节，看看在匹配串的位置，不存在的都是plen+1
        i += next[ori[i + plen]];
    }
}

/* 内部递归函数，实现统计和打印递增数
*  以12345为例，nBase:表示高位数123，
*  那么nDigit表示低位位数2，而iStart表示4
*  时间复杂度为O( C(n,9) )
*/
static int _Count_Digit ( int nBase, int nDigit, int iStart )
{  
    if ( nDigit == 0 ) // 已经是最后一位数，输出nBase
    {
        cout << nBase << endl;
        return 1;
    }

    int t = nBase * 10;
    int total = 0;
    for ( int s = iStart; s < 10; s++ )
    {
        total += _Count_Digit ( t + s, nDigit - 1, s + 1 );
    }
    return total;
}

int Count_IncreasingDigit ( int nDigit )
{
    if ( nDigit > 9 ) nDigit = 9;
    if ( nDigit < 1 ) nDigit = 1;
   
    // 开始计算的数，只有1位数则包含0，
    // 否则从1开始，比如0，1，2...12,13
    int iStart = 1;
    if ( nDigit == 1 )
    {
        iStart = 0;
    }
    return _Count_Digit ( 0, nDigit, iStart );
}
