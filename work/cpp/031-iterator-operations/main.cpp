// 031-iterator-operations

// 出力イテレータの例
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

// 入力イテレーターの例
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

template < typename  T >
bool operator ==( cin_iterator<T> const & l, cin_iterator<T> const & r)
{ return l.fail == r.fail ; }

template < typename T >
bool operator !=( cin_iterator<T> const & l, cin_iterator<T> const & r)
{ return !(l == r) ; }

int main()
{
  std::vector<int> v = {1, 2, 3, 4, 5} ;
  cout_iterator out ;

  std::copy( std::begin(v), std::end(v), out ) ;

  cin_iterator<int> input, fail(true) ;
  std::vector<int> buffer ;
  input++;
  std::cout << *input << std::endl;

  // 'input' イテレータから 'buffer' へ push_back する
  //std::copy( input, fail, std::back_inserter(buffer) ) ;
}

