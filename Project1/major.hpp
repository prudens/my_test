#ifndef HPP_MAJOR
#define HPP_MAJOR

// 这是大多数算法的实现，先决条件是容器里面有一个元素
// 超过容器个数的一半，否则返回值不准。
template <class InputIterator>
typename iterator_traits<InputIterator>::value_type
Major( InputIterator first, InputIterator end )
{
    if ( first == end )
    {
        return 0;
    }
    
    typename iterator_traits<InputIterator>::difference_type n = 1;
    InputIterator itor = first++;
    for ( ; first != end; first++ )
    {
        *first == *itor ? n++ : n--;
        if ( n == 0 )
        {
            itor = first;
            n++;
        }
    }
    return *itor;
}

// 这是大多数算法的实现，先决条件是容器里面有一个元素
// 超过容器个数的三分之一，否则返回值不准。
template <class InputIterator>
typename iterator_traits<InputIterator>::value_type
Major_third( InputIterator first, InputIterator end )
{
    if ( first == end )
    {
        return 0;
    }

    typedef typename iterator_traits<InputIterator>
        ::difference_type diff_type;
    diff_type n1, n2, n3;
    n1 = n2 = n3 = 0;
    InputIterator Itor1, Itor2, Itor3;
    Itor1 = Itor2 = Itor3 = end;

    for ( ; first != end; ++first )
    {
        bool bExist = true;
        if ( n1 && *first == *Itor1 ) n1++;
        else if ( n2 && *first == *Itor2 ) n2++;
        else if ( n3 && *first == *Itor3 ) n3++;
        else bExist = false;

        if ( n1 && n2 && n3 )
        {
            if ( --n1 == 0 ) Itor1 = end;
            if ( --n2 == 0 ) Itor2 = end;
            if ( --n3 == 0 ) Itor3 = end;
        }
        else
        {
            if ( 0 == n1 )
            {
                Itor1 = first;
                ++n1;
            }
            else if ( 0 == n2 )
            {
                Itor2 = first;
                ++n2;
            }
            else if ( 0 == n3 )
            {
                Itor3 = first;
                ++n3;
            }
        }
    }

    if ( n1 >= n2 && n1 >= n3 ) return *Itor1;
    if ( n2 >= n1 && n2 >= n3 ) return *Itor2;
    if ( n3 >= n1 && n3 >= n2 ) return *Itor3;
    return 0;
}

#endif