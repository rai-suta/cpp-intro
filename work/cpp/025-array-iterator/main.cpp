// 025-array-iterator
// array のイテレーター

// イテレーターを表現するクラス
struct array_iterator { } ;

template < typename T, std::size_t N >
struct array
{
    // ネストされた型名を宣言
    using value_type        = T ;
    using reference         = T & ;
    using const_reference   = T const & ;
    using size_type         = std::size_t ;
    using iterator          = array_iterator ;

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
    
    // イテレータを返すメンバー
    iterator begin() ;
    iterator end() ;
} ;

template < typename Array >
struct array_iterator_begin
{
    Array & a;
    array_iterator_begin( Array & a )
        : a( a ) { }
        
    typename Array::reference operator *()
    { return a[0] ; }
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

    puts("[025-array-iterator]");
}