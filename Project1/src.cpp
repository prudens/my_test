#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>

#include "sunday.h"

using namespace std;
int n;
void func ( const int& value )
{
    n += value;
}
int main(int, char**)
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
    */
    vector<int> v;
    sunday ( "ibeginsearchapattopattonstringpattonfromtext", "patton", &v );
    system ( "pause" );
	return 0;
}

