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
        i += next[ori[i + plen]]; // ȡ��һ���һ���ֽڣ�������ƥ�䴮��λ�ã������ڵĶ���plen+1
    }
}
