#include "sunday.h"
void sunday ( const char* ori, const char* pat, vector<int> * res )
{
    int i = 0;
    int j = 0;
    int olen = strlen ( ori );
    int plen = strlen ( pat );
    const int max_size = 255;
    int * next = new int[max_size];
    for ( i = 0; i < max_size; ++i ) // ��ʼ��
    {
        next[i] = plen + 1;
    }
    for ( i = 0; i < plen; ++i )
    {
        next[pat[i]] = plen - i;  // ����ƫ�����������ͬ���ַ��ǰ����ҵ�Ϊ׼�������ǵ�ǰ����ͬ�ַ���ƫ������
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

        // ȡ��һ���һ���ֽڣ�������ƥ�䴮��λ�ã������ڵĶ���plen+1
        i += next[ori[i + plen]];
    }
}

/* �ڲ��ݹ麯����ʵ��ͳ�ƺʹ�ӡ������
*  ��12345Ϊ����nBase:��ʾ��λ��123��
*  ��ônDigit��ʾ��λλ��2����iStart��ʾ4
*  ʱ�临�Ӷ�ΪO( C(n,9) )
*/
static int _Count_Digit ( int nBase, int nDigit, int iStart )
{  
    if ( nDigit == 0 ) // �Ѿ������һλ�������nBase
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
   
    // ��ʼ���������ֻ��1λ�������0��
    // �����1��ʼ������0��1��2...12,13
    int iStart = 1;
    if ( nDigit == 1 )
    {
        iStart = 0;
    }
    return _Count_Digit ( 0, nDigit, iStart );
}
