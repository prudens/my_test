#ifndef _SORT_H_
#define _SORT_H_
#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <time.h>
void sort_demo()
{
    ifstream datafile( "E:\\CPPDemo\\ins.txt" );
    string data( ( istreambuf_iterator<char>( datafile ) ),
                 ( istreambuf_iterator<char>() ) );

    cout << data << endl;
    for each ( auto elem in data )
    {
        cout << elem << endl;
    }



    set<string*, stringcmp<string*>> s;
    s.insert( new string( "cccc" ) );
    s.insert( new string( "dddd" ) );
    s.insert( new string( "aaaa" ) );
    s.insert( new string( "bbbb" ) );

    for ( auto i = s.begin(); i != s.end(); i++ )
    {
        cout << **i << endl;
    }

    transform( s.begin(), s.end(),
               ostream_iterator<string>( cout, "\n" ),
               [&] ( string*p ) { return*p; } );

    srand( ( (unsigned int)time( NULL ) ) );
    vector<int> v;
    for ( int i = 0; i < 100; i++ )
    {
        v.push_back( rand() % 100 );
    }


    cout << "未排序" << endl;
    for each ( auto i in v )
    {
        cout << i << '\t';
    }
    cout << endl;


    auto v1 = v;
    partial_sort( v1.begin(), v1.begin() + 25, v1.end() );//前n个元素排序
    cout << "前25个元素排序" << endl;
    for each ( auto i in v1 )
    {
        cout << i << '\t';
    }
    cout << endl;

    auto v2 = v;
    stable_sort( v2.begin(), v2.end() );
    cout << "stable_sort稳定排序" << endl;
    for each ( auto i in v2 )
    {
        cout << i << '\t';
    }
    cout << endl;

    auto v3 = v;
    //	nth_element(v.begin(),v.begin()+5,v.end());
    nth_element( v3.begin(), v3.begin() + 75, v3.end(),
                 [] ( const int&lhs, const int&rhs )->bool { return lhs < rhs; } );
    cout << "nth_element提取前75个元素到begin，但内部不排序" << endl;
    for each ( auto i in v )
    {
        cout << i << '\t';
    }
    cout << endl;

    auto v4 = v;
    partition( v4.begin(), v4.end(), [] ( const int& value )->bool
    {
        return value > 80;
    } );
    cout << "partition排序：将符合要求的元素提取到前面来" << endl;
    for each ( auto i in v )
    {
        cout << i << '\t';
    }
    cout << endl;

    sort( v.begin(), v.end() ); // 全排序
    cout << "sort全排序" << endl;
    for each ( auto i in v )
    {
        cout << i << '\t';
    }
    cout << endl;
}
#include <windows.h>
CRITICAL_SECTION  cs;
int g_value;
void Init()
{
    ::InitializeCriticalSection( &cs );
    g_value = 1;
}
void Fun2();
void Fun1( bool bCallFun2 )
{
    ::EnterCriticalSection( &cs );
    g_value = 2;
    if( bCallFun2 ) Fun2();
    ::LeaveCriticalSection( &cs );

}

void Fun2()
{
    Fun1( false );
}

#endif