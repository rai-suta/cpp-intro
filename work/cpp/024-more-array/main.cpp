// cpp-intro/024-more-array.md
// arrayをさらに実装

template < typename T, std::size_t N >
struct array
{
    // ネストされた型名を宣言
    using value_type        = T ;
    using reference         = T & ;
    using const_reference   = T const & ;
    using size_type         = std::size_t ;

    value_type storage[N] ;
    
    size_type size() const;

    // メンバー関数のconst修飾
    reference operator [] ( size_type i )
    {
        return storage[i] ;
    }
    const_reference operator [] ( size_type i ) const
    {
        return storage[i] ;
    }
    
    // 先頭と末尾の要素 : front/back
    reference front()
    { return storage[0] ; }
    const_reference front() const
    { return storage[0] ; }
    
    reference back()
    { return storage[N-1] ; }
    const_reference back() const
    { return storage[N-1] ; }
    
    // 全要素に値を代入 : fill
    void fill( T const & u )
    {
        for ( std::size_t i = 0 ; i != N ; ++i )
        {
            storage[i] = u ;
        }
    }
    /*
    これは動かない。begin() / end() と イテレータに対応していないため。
    void fill( T const & u )
    {
        std::fill( begin(), end(), u ) ;
    }
    */
} ;

template < typename T, std::size_t N >
typename array<T, N>::size_type array<T, N>::size() const
{
    return N;
}

template < typename Container >
void print( Container const & c )
{
    for ( std::size_t i = 0 ; i != c.size() ; ++i )
    {
        std::cout << c[i] ;
    }
}

int main()
{
    using std::cout;
    using std::endl;
    auto newline = []{ cout << ""s << endl; } ;
    auto puts = [](auto s){ cout << s << endl; };
    
    array<int, 5> a = {1,2,3,4,5} ;
    print( a ) ; newline();
    puts(a.size());
    
    newline();
    
    // 先頭と末尾の要素 : front/back
    int & f = a.front();
    int & b = a.back();
    cout << "[" << f << " .. " << b << "]" << endl;
    
    // 全要素に値を代入 : fill
    a.fill(10);
    print( a );
    
    newline();
}
