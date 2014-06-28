#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <time.h>
using namespace std;

template<typename T>
class B{
public:
	template<typename U> struct MyStruct
	{
	public:
		template<typename Y>struct My_
		{
			typedef typename Y::size_type size_type;
		};
		typedef typename My_<U>::size_type size_type;
	};
	typedef typename MyStruct<T>::size_type size_type;
};
template<typename T>
class MyClass
{
public:
    typedef typename T::template MyStruct<T>::
		template My_<T>::size_type size_type;
	size_type Getval(){return size_type(-1);}
};

template<typename T>
struct  stringcmp :
	public binary_function<T,T,bool>
{
public:
	bool operator ()(const T& ps1,const T& ps2)const{
		return *ps1 < *ps2; 
	}
};


class A
{
	friend ostream& operator<<(ostream&, const A&);
public:
	A() = default;
	A(const A &){ }
	A(const string &s, int i):sval(s + "fuck"),ival(i + 2){ }
private:
	string sval;
	int ival = 2;
};
ostream& operator<<(ostream& os, const A &object)
{
	return os << object.sval << " " << object.ival;
}


string reverse_words( const char* pSrc )
{
    string strDest; 
    if ( pSrc == NULL )
    {
        return (strDest);
    }
   strDest.reserve( strlen( pSrc ) );
   const char *p = pSrc;
    
    while ( *p )
    {
        if ( *p == ' ')
        {
            strDest += *p;
            p++;
        }
        else
        {
            while ( *p && *p != ' ' )
            {
                p++;
            }
            const char *pStart = p-1;
            while ( *pStart && *pStart != ' ' )
            {
                strDest += *pStart--;
            }
        }
    }
    return (strDest);
}

// #define XNAME(X,Y)\
//     X(__stdcall,Y)
// 
// #define TEST(X,Y)\
//     template<class _Ret, class... _Types> \
// struct Test<_Ret( X * )( _Types... )> \
// {	/* base class for function pointer predicates */ \
// };
// 
// XNAME(TEST, )
// TEST( X, Y )( __stdcall, Y )

//#undef XNAME


// #define _IS_FUNPTR1(CALL_OPT, X1) \
//     template<class _Ret, \
// class... _Types> \
// struct _Is_funptr1<_Ret( CALL_OPT * )( _Types... )> \
//     : true_type \
// {	/* base class for function pointer predicates */ \
// };
// 
// _NON_MEMBER_CALL(_IS_FUNPTR1, )
// #undef _IS_FUNPTR1
#include "sort.h"
int main ( int, char** )
{
   string str = std::move(reverse_words( "Hello world" ));
    cout << reverse_words( "Hello" )<<endl;
    cout << reverse_words( " " )<<endl;
    cout << reverse_words(NULL)<<endl;
    cout << reverse_words( "   Hello world  a" )<<endl;
    cout << reverse_words( "I love programming" ) << endl;


    Init();
    Fun1( true );


	system("pause");
    
	return 0;
}