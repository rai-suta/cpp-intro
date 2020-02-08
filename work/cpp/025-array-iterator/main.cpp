// 025-array-iterator
// array のイテレーター

// arrayの開始イテレータを格納するクラス
template < typename Array >
struct array_iterator_begin
{
    Array & a;
    array_iterator_begin( Array & a )
        : a( a ) { }
        
    typename Array::reference operator *()
    { return a[0]; }
} ;

// arrayのイテレーターとなるクラス
template < typename Array >
struct array_iterator
{
  Array & a ;     // 保持するインスタンス
  std::size_t i ; // 現在のインデックス

  array_iterator( Array & a, std::size_t i )
    : a( a ), i(i) { }
  
  // いま参照している要素へのリファレンスを返す
  typename Array::reference operator *()
  { return a[i]; }

  // 次の要素を指す
  array_iterator & operator ++()  // >main0
  { ++i ; return *this ; }
  // 前の要素を指す
  array_iterator & operator --()
  { --i ; return *this ; }
  // 後置インクリメント
  array_iterator operator ++(int)
  {
    array_iterator copy = *this;
    ++*this;      // 前置インクリメントを呼び出す
    return copy;  // インクリメントする前のコピーを返す
  }
  // 後置デクリメント
  array_iterator operator --(int)
  {
    array_iterator copy = *this;
    --*this;
    return copy;
  }

  // 比較
  bool operator ==( array_iterator const & right )
  { return i == right.i ; }
  bool operator !=( array_iterator const & right )
  { return i != right.i ; }
  bool operator < ( array_iterator const & right ) const
  { return i < right.i ; }
  bool operator <= ( array_iterator const & right ) const
  { return i <= right.i ; }
  bool operator > ( array_iterator const & right ) const
  { return i > right.i ; }
  bool operator >= ( array_iterator const & right ) const
  { return i >= right.i ; }

  // 加算 >main2
  array_iterator & operator += ( std::size_t n )
  {
    i += n;
    return *this;
  }
  array_iterator operator + ( std::size_t n ) const
  {
    auto copy = *this;
    copy += n;
    return copy;
  }

  // 減算
  array_iterator & operator -= ( std::size_t n )
  {
    i -= n;
    return *this;
  }
  array_iterator operator - ( std::size_t n ) const
  {
    auto copy = *this;
    copy -= n;
    return copy;
  }

  // インデックス
  typename Array::reference operator [] ( std::size_t n ) const
  { return *( *this + n ); }

} ;

// コンテナの中身を変更できないイテレーター >main3
template < typename Array >
struct array_const_iterator
{
  Array const & a ;
  std::size_t i ;

  // コンストラクター
  array_const_iterator( Array const & a, std::size_t i )
    : a(a), i(i) { }

  // array_iteratorからの変換コンストラクター
  array_const_iterator( typename Array::iterator const & iter )
    : a( iter.a ), i( iter.i ) { }

  bool operator ==( array_const_iterator const & right )
  { return i == right.i ; }
  bool operator !=( array_const_iterator const & right )
  { return i != right.i ; }
  bool operator < ( array_const_iterator const & right ) const
  { return i < right.i ; }
  bool operator <= ( array_const_iterator const & right ) const
  { return i <= right.i ; }
  bool operator > ( array_const_iterator const & right ) const
  { return i > right.i ; }
  bool operator >= ( array_const_iterator const & right ) const
  { return i >= right.i ; }

  array_const_iterator & operator ++()
  { ++i ; return *this ; }
  array_const_iterator & operator --()
  { --i ; return *this ; }
  array_const_iterator operator ++(int)
  {
    array_const_iterator copy = *this;
    ++*this;      // 前置インクリメントを呼び出す
    return copy;  // インクリメントする前のコピーを返す
  }
  array_const_iterator operator --(int)
  {
    array_const_iterator copy = *this;
    --*this;
    return copy;
  }


  array_const_iterator & operator += ( std::size_t n )
  {
    i += n;
    return *this;
  }
  array_const_iterator operator + ( std::size_t n ) const
  {
    auto copy = *this;
    copy += n;
    return copy;
  }
  array_const_iterator & operator -= ( std::size_t n )
  {
    i -= n;
    return *this;
  }
  array_const_iterator operator - ( std::size_t n ) const
  {
    auto copy = *this;
    copy -= n;
    return copy;
  }

  typename Array::const_reference operator *() const
  { return a[i]; }
  typename Array::const_reference operator [] ( std::size_t n ) const
  { return *( *this + n ); }

};

template < typename T, std::size_t N >
struct array
{
  // ネストされた型名を宣言
  using value_type        = T ;
  using reference         = T & ;
  using const_reference   = T const & ;
  using size_type         = std::size_t ;
  
  size_type size() const;

  // イテレータを返すメンバ
  //using iterator = array_iterator ;
  //iterator begin() ;
  //iterator end() ;

  // 開始 iterator を返すための実装
  value_type storage[N] ;
  // 自分(array)格納できるarray_iterator_begin型を宣言
  //using iterator = array_iterator_begin<array>;
  using iterator       = array_iterator<array>;
  using const_iterator = array_const_iterator<array>;

  // 先頭要素のイテレーター
  iterator begin()
  { return iterator( *this, 0 ); }
  // 最後の次の要素へのイテレーター
  iterator end()
  { return iterator( *this, N ); }

  // const arrayのときにconst_iteratorを返す
  const_iterator begin() const
  { return const_iterator(*this, 0) ; }
  const_iterator end() const
  { return const_iterator(*this, N) ; }

  // 常にconst_iteratorを返す
  const_iterator cbegin() const
  { return const_iterator(*this, 0) ; }
  const_iterator cend() const
  { return const_iterator(*this, N) ; }

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
  
  reference back()  // main0
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
  
} ;

// 実行するmain関数
#define main3

#ifdef main0
int main()
{
  array<int, 5> a = {1,2,3,4,5};

  auto iter = a.begin();
  std::cout << *iter << std::endl; // 1
  ++iter;
  std::cout << *iter << std::endl; // 2
}
#endif

#ifdef main1
int main()
{
  array<int, 5> a = {1,2,3,4,5};

  std::for_each( std::begin(a), std::end(a),
    [](auto x){ std::cout << x ; } ) ;
}
#endif

#ifdef main2
int main()
{
  std::array<int, 5> a = {1,2,3,4,5} ;

  std::cout << a[3] << std::endl; // 4

  auto i = a.begin();

  std::cout << *(i + 3) << std::endl; // 4
}
#endif

#ifdef main3
int main()
{
  using array_5 = array<int, 5>;
  array_5 a = {1,2,3,4,5} ;

  // iterator
  auto i = a.begin() ;

  // iteratorからconst_iteratorへの変換
  array_5::const_iterator j = i ;
  
  std::cout << *j << std::endl;    // 1
  std::cout << j[2] << std::endl;  // 3

  std::for_each( a.cbegin(), a.cend(),
    [](auto x){ std::cout << x ; } ) ;
  std::cout << std::endl;
}
#endif
