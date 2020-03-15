// 031-iterator-operations

//
/// 出力イテレーター
//
struct cout_iterator
{
// --- ボイラープレートコード (言語仕様上必要だが、機能を持たないコード)
  // iterator_traits 用定義
  using difference_type   = void ;
  using value_type        = void ;
  using reference         = void ;
  using pointer           = void ;
  using iterator_category = std::output_iterator_tag ;

  // 出力イテレータではサポートしない operator
  cout_iterator & operator *() { return *this ; }
  cout_iterator & operator ++() { return *this ; }
  cout_iterator & operator ++(int) { return *this ; }
// --- ボイラープレートコード

  // イテレータへの出力
  template < typename T >
  cout_iterator & operator =( T const & x )
  {
    std::cout << x ;
    return *this ;
  }
} ;

//
/// 前方イテレーター
//
// このイテレーターは`T`型の整数を保持し、`operator *`でリファレンスを返し、`operator ++`でインクリメントする。
template < typename T >
struct iota_iterator
{
// --- ボイラープレートコード (言語仕様上必要だが、機能を持たないコード)
  // iterator_traits 用定義
  using difference_type   = std::ptrdiff_t ;
  using value_type        = T ;
  using reference         = T & ;
  using pointer           = T * ;
  using iterator_category = std::forward_iterator_tag ;

  T value ;

  iota_iterator( value_type value = 0 )
    : value(value)
  { }

  reference       operator *() noexcept
  { return value ; }
  const reference operator *() const noexcept
  { return value ; }

  // インクリメント
  iota_iterator & operator ++() noexcept
  {
    ++value ;
    return *this ;
  }
  iota_iterator   operator ++(int) noexcept
  {
    auto temp = *this ;
    ++*this ;
    return temp ;
  }

  // 比較演算子
  bool operator == ( iota_iterator const & i ) const noexcept
  {
    return value == i.value ;
  }
  bool operator != ( iota_iterator const & i ) const noexcept
  {
    return !(*this == i) ;
  }
} ;

// 前方リンクリスト
template < typename T >
struct forward_link_list
{
  T value ;
  forward_link_list * next ;
  struct iterator ;
} ;

template < typename T >
struct forward_link_list<T>::iterator
{
  forward_link_list<T> * ptr ;

  T & operator * () noexcept
  { return ptr->value ; }
  
  iterator & operator ++() noexcept
  {
    ptr = ptr->next ;
    return *this;
  }
} ;

template < typename T >
forward_link_list<T> & next( forward_link_list<T> & list ) noexcept
{
  return *list.next ;
}

// 前方イテレーターが入力/出力イテレーターと違う点は、マルチパス保証があることだ。
// イテレーターのコピーを使い回して複数回同じ要素をたどることができる。
template < typename ForwardIterator >
void forward_iterator_is_multi_pass( ForwardIterator first, ForwardIterator last )
{
  using vector_type = std::vector< typename ForwardIterator::value_type > ;

  vector_type v1 ;
  for ( auto iter = first ; iter != last ; ++iter )
    v1.push_back( *iter ) ;

  vector_type v2 ;
  for ( auto iter = first ; iter != last ; ++iter )
    v2.push_back( *iter ) ;

  // マルチパス保証があれば常にtrue
  bool b = v1 == v2 ;
  std::cout << "multi pass " << (b ? "OK"s : "NG"s) << std::endl ;
}

//
/// 入力イテレーター
//
template < typename T >
struct cin_iterator
{
// --- ボイラープレートコード (言語仕様上必要だが、機能を持たないコード)
  // iterator_traits 用定義
  using difference_type   = std::ptrdiff_t ;
  using value_type        = T ;
  using reference         = T & ;
  using const_reference   = const T & ;
  using pointer           = T * ;
  using iterator_category = std::input_iterator_tag ;
// --- ボイラープレートコード (言語仕様上必要だが、機能を持たないコード)

  // コンストラクター
  cin_iterator( bool fail = false )
    : fail(fail)
  { ++*this ; }

  // キャッシュした値を返す
  const_reference operator *() const
  //const reference operator *() const  // error: binding 'const value_type {aka const int}' to reference of type 'cin_iterator<int>::reference {aka int&}' discards qualifiers
  //const T & operator *() const
  { return value ; }

  // 新しい値をキャッシュする
  cin_iterator & operator ++()
  {
    if ( !fail )
    {
      std::cin >> value ;
      fail = std::cin.fail();
    }
    return *this;
  }

  // 後置インクリメント
  cin_iterator operator ++(int)
  {
    auto old = *this ;
    ++*this;
    return old ;
  }

  bool fail ;
  value_type value ;
} ;

// 入力イテレーターは同値比較が出来る
template < typename  T >
bool operator ==( cin_iterator<T> const & l, cin_iterator<T> const & r)
{ return l.fail == r.fail ; }

template < typename T >
bool operator !=( cin_iterator<T> const & l, cin_iterator<T> const & r)
{ return !(l == r) ; }

int main()
{
  /// 出力イテレーター
  std::cout << "<output iterator>"s << std::endl;
  {
    std::vector<int> v = {1, 2, 3, 4, 5} ;
    cout_iterator out ;

    std::copy( std::begin(v), std::end(v), out ) ;
  }
  std::cout << "<EOL>" << std::endl;

  std::cout << std::endl;

  /// 前方イテレーター
  std::cout << "<iota iterator>"s << std::endl ;
  {
    iota_iterator iter(0) ;
    *iter ; // 0
    *++iter ; // 1
    *++iter ; // 2

    iota_iterator first(0), last(10) ;

    // 0123456789と出力される
    std::for_each( first, last,
        [](auto i){ std::cout << i ;}
    ) ;
    std::cout << "<EOL>"s << std::endl;

    std::vector<int> v ;
    std::copy( first, last, std::back_inserter(v) ) ;
    // vは{0,1,2,3,4,5,6,7,8,9}
    
    forward_iterator_is_multi_pass( first, last ) ;

    forward_link_list<int> list3{ 3, nullptr };
    forward_link_list<int> list2{ 2, &list3 };
    forward_link_list<int> list1{ 1, &list2 };
    forward_link_list<int> list0{ 0, &list1 };
    forward_link_list<int>::iterator iter_fll{ &list0 };
    do {
      std::cout << *iter_fll ;
    } while( (++iter_fll).ptr );
  }
  std::cout << "<EOL>" << std::endl;

  std::cout << std::endl;

  /// 入力イテレーター
  std::cout << "<input iterator>"s << std::endl;
  {
    std::cout << " (e.g. <- 1 2 3 q)" << std::endl;
    std::cout << " input <- "s;
    cin_iterator<int> input, fail(true) ;
    std::vector<int> buffer ;

    std::copy( input, fail, std::back_inserter(buffer) ) ;

    auto iter = buffer.begin();
    std::cout << " buffer = ";
    while (iter != buffer.end()) {
      std::cout << *(iter++) << ",";
    }
  }
  std::cout << "<EOL>" << std::endl;
}
