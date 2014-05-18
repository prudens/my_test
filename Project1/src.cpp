#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>

#include "sunday.h"
#include <windows.h>
#include "matrix.hpp"
#include "major.hpp"
using namespace std;
int n;
void func ( const int& value )
{
    n += value;
}
int main( int, char** )
{
    /*
    vector<int> v{ 1, 2, 3, 2, 1, 2, 3, 4, 5, 6, 4, 3, 2, 1, 2, 3 };
    cout << count ( v.begin (), v.end (), 2 );
    cout << count_if ( v.begin (), v.end (),
    [] ( const int&value )->bool { return value > 3; } );

    cout << *min_element ( v.begin (), v.end () ) << endl;
    cout << *max_element ( v.begin (), v.end () ) << endl;
    cout << accumulate ( v.begin (), v.end (), 0 ) << endl;
    cout << accumulate ( v.begin (), v.end (), 1,
    multiplies<int>() ) << endl;

    int nTotal = 0;
    for_each ( v.begin ( ), v.end ( ), [=] ( const int&value )mutable ->void
    {
    nTotal += value;
    } );
    cout << nTotal << endl;

    for_each ( v.begin (), v.end (), func );

    vector<int> v;
    sunday ( "ibeginsearchapattopattonstringpattonfromtext", "patton", &v );

    int nTotal = Count_IncreasingDigit ( 5 );
    cout << "输入位数" << 5 << "得到递增数字共计" << nTotal << endl;
    system ( "pause" );
    */
//     int lhs[3][2] = { 1, 2, 2, 1 };
//     int rhs[2][1] = { 1, 2 };
//     int value[3][1];
//     Matrixmulti( lhs, 2, 2, rhs, 2, 1, value );
//     for ( int i = 0; i < 3; i++ )
//     {
//         for ( int j = 0; j < 1; j++ )
//         {
//             cout << value[i][j]<<'\t';
//         }
//         cout << endl;
//     }

//     DWORD nt = GetTickCount();
//     for ( int i = 0; i < 94; i++ )
//     {
//         cout << Fibonacci( i ) << '\t';
//     }
//     cout << GetTickCount() - nt << endl;

//     DWORD n = GetTickCount();
//     for ( int i = 0; i < 94; i++ )
//     {
//         uint64_t pre = 0;
//         uint64_t cur = 1;
//         uint64_t next = 0;
//         uint64_t cnt = 1;
//         while ( cnt<=i )
//         {
//             next = cur + pre;
//             pre = cur;
//             cur = next;
//             cnt++;
//             if ( cnt % 10 == 0 )
//                 printf( "F%llu=%llu\n", cnt, cur );
//             if ( cur + pre < cur )
//                 break;
//         }
//         printf( "F%llu=%llu  F%llu=%llu\n", cnt - 1, pre, cnt, cur );
//     }
// 
// 
//     cout << GetTickCount( ) - n << endl;


    vector<int> vt;
    for ( int i = 0; i < 10; i++ )
    {
        vt.push_back( i );
        vt.push_back( 5 );
    }
    cout<<Major( vt.begin(), vt.end() )<<endl;

    int p[10] = { 3, 3, 3, 3, 3, 1, 1, 1, 1, 1 };
    cout << Major_third( p, p + 10 ) << endl;
    system( "pause" );
	return 0;
}

