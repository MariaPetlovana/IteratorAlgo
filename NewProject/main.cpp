#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

template<typename T>
class iterator
{
    private:
        const T* m_pointer;
    public:
        iterator(const T* point)
        {
            m_pointer = point;
        }
        iterator& operator ++ ()
        {
            ++m_pointer;
            return *this;
        }
        bool operator == (iterator const& iter) const
        {
            return m_pointer == iter->m_pointer;
        }
        bool operator != (T* end) const
        {
            return m_pointer != end;
        }
        bool operator != (iterator const& iter) const
        {
            return m_pointer != iter.m_pointer;
        }
        T const& operator * () const
        {
            return *(m_pointer);
        }
};

struct mod2
{
    bool operator()(int x)
    {
        return !(x & 1);
    }
};

struct square
{
    int operator()(int x)
    {
        return x * x;
    }
};

struct print
{
    void operator()(int x)
    {
        cout << x << endl;
        return;
    }
};

template<typename T, typename F>
bool all_of(T* begin, T* end, F f)
{
    while(begin != end)
    {
        if(!f(*begin)) return 0;
        ++begin;
    }
    return 1;
}

template<typename T, typename F>
bool any_of(T* begin, T* end, F f)
{
    while(begin != end)
    {
        if(f(*begin)) return 1;
        ++begin;
    }
    return 0;
}


template<typename T, typename F>
void foreach(T* begin, T* end, F f)
{
    while(begin != end)
    {
        f(*begin);
        ++begin;
    }
    return;
}

template<typename T, typename D, typename F>
void transform_iterator(T* begin, T* end, D result, F f)
{
    while(begin != end)
    {
        *result = f(*begin);
        ++begin;
        ++result;
    }
    return;
}

template<typename T, typename F>
T* partition(T* begin, T* end, F f)
{
    while(begin != end)
    {
        while(f(*begin))
        {
            if(begin == end) return begin;
            ++begin;
        }

        --end;

        while(!f(*end))
        {
            if(begin == end) return begin;
            --end;
        }

        T tmp = *begin;
        *begin = *end;
        *end = tmp;

        ++begin;
    }

    return begin;
}

int main()
{
    //example
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    long long arr2[10];
    if (all_of (arr, arr + 10, mod2() ) ) cout << "Hello world!" << endl;
    else cout << "dgdf" << endl;
    foreach(arr, arr + 10, print());

    foreach(arr, arr + 10, print());
    transform_iterator(arr, arr + 10, arr2, square());
    foreach(arr2, arr2 + 10, print());

    cout << endl;

    int* point = partition(arr, arr + 10, mod2());

    foreach(arr, point, print());
    cout << endl;
    foreach(point, arr + 10, print());
    cout << endl;

    iterator<int> iter(arr);
    for( ; iter != arr + 10; ++iter)
    {
        cout << *iter << endl;
    }
    return 0;
}
