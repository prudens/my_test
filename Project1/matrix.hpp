#ifndef _HPP_MATRIX_
#define _HPP_MATRIX_
#include <memory>

int g_arr[64] = { 0 };
template<typename T1, typename T2, typename T3 >
bool Matrixmulti(
    T1  *Lhs,
    int nlCol,
    int nlRow,
    T2  *Rhs,
    int nrCol,
    int nrRow,
    T3  *Result )
{
    if ( nlRow != nrCol
         && Lhs == nullptr
         && Rhs == nullptr
         && Result == nullptr )
    {
        return false;
    }

    for ( int i = 0; i < nlCol; i++ )
        for ( int j = 0; j < nrRow; j++ )
            for ( int k = 0; k < nrCol; k++ )
            {
                Result[i * nrRow + j] 
                    += Lhs[i * nlRow + k] * Rhs[k * nrRow + j];
            }

    return true;
}

template< typename T>
bool MatrixSquare( T *Src, int nOrder, T *Result )
{
    return Matrixmulti(
        Src,
        nOrder,
        nOrder,
        Src,
        nOrder,
        nOrder,
        Result
        );
}


template< typename T >
bool Matrices( T *Src, int nOrder, int nPower, T *Result )
{
    if ( nPower == 2 )
    {
        return MatrixSquare( Src, nOrder, Result );
    }
    if ( nPower == 1 )
    {
        memcpy( Result, Src, nOrder * nOrder );
        return true;
    }

    if ( nPower <= 0 )
    {
        return false;
    }

    T* pTemp = new T[nOrder * nOrder];
    
    int nLen = sizeof( T ) * nOrder * nOrder;
    memset( pTemp, 0, nLen );
    if ( 0 == nPower % 2 )
    {
        if ( g_arr[nPower/2] )
        {
            memcpy( pTemp, (void*)g_arr[nPower / 2], nLen );
        }
        else
        {
            bool bRet = Matrices( Src, nOrder, nPower / 2, pTemp );
            if ( !bRet )
            {
                return false;
            }
            g_arr[nPower / 2] = (int)pTemp;
        }     
        return MatrixSquare( pTemp, nOrder, Result );
    }
    else
    {
        if ( g_arr[nPower - 1] )
        {
            memcpy( pTemp, (void*)g_arr[nPower - 1], nLen );
        }
        else
        {
            bool bRet = Matrices( Src, nOrder, nPower - 1, pTemp );
            if ( !bRet )
            {
                return false;
            }
            g_arr[nPower - 1] = (int)pTemp;
        }
        return Matrixmulti(
            pTemp,
            nOrder,
            nOrder,
            Src,
            nOrder,
            nOrder,
            Result );
    }
    return true;
}

uint64_t Fibonacci( int n )
{
    typedef uint64_t Value_type;
    Value_type m[2][2] = { 1, 1, 1, 0 };
    Value_type init[2][1] = { 1, 0 };
    Value_type *result = new Value_type[2];
    Value_type temp[2][2] = {0};
    if ( n < 0 || n > 93 )
    {
        return -1;
    }
    if ( n < 2 )
    {
        return init[1-n][0];
    }
    memset( result, 0, sizeof(Value_type)* 2 );
#ifdef Recursion
    bool bRet = Matrices( (Value_type*)m, 2, n - 1, (Value_type*)temp );
    if ( !bRet )
    {
        return -1;
    }
    bRet = Matrixmulti( (Value_type*)temp, 2, 2, (Value_type*)init, 2, 1, (Value_type*)result );
    if ( !bRet )
    {
        return -1;
    }

    return *result;

#else

    g_arr[0] = (int)m;
    int k = n-1;
    for ( int i = 1; (1 << i) <= k; i++ )
    {
        if ( !g_arr[i] )
        {
            Value_type* pTemp = new Value_type[4];
            memset( pTemp, 0, sizeof(Value_type)* 4 );

            MatrixSquare( (Value_type*)g_arr[i - 1], 2, pTemp );
            g_arr[i] = (int)pTemp;
        }
    }

    bool begin = false;
    n--;
    for ( int i = 0; (1<<i) <= n; i++ )
    {
        if ( (1 << i) & n ) //第i位是否为0
        {
            if ( begin == false )
            {
                begin = true;
                memcpy( temp, (void*)g_arr[i], sizeof(Value_type) * 4 );
            }
            else
            {
                Value_type temp1[2][2] = { 0 }; 
                Matrixmulti( (Value_type*)temp, 2, 2, (Value_type*)g_arr[i], 2, 2, (Value_type*)temp1 );
                memcpy( temp, temp1, sizeof(Value_type) * 4 );
            }
        }
    }

    int bRet = Matrixmulti( (Value_type*)temp, 2, 2, (Value_type*)init, 2, 1, (Value_type*)result );
    if ( !bRet )
    {
        return -1;
    }

    return *result;
#endif
}
#endif
