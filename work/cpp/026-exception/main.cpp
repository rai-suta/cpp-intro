// 026-exception
// 傲慢なエラー処理：例外

struct Object
{
  std::string name ;
  // Constructor
  Object( std::string const & name ) : name(name)
  { std::cout << name << " is constructed.\n"s ; }

  // Destructor
  ~Object()
  { std::cout << name << " is destructed.\n"s ; }
} ;

void f()
{
  Object obj("f"s); // f is constructed
  throw 0;
  // f is destructed
}

void g()
{
  Object obj("g"s) ; // g is constructed
  f() ;
  // g is destructed
}

int main()
{
  Object obj("main"s);

  try {
    g() ;
  } catch( int e )
  {
    std::cout << "caught.\n"s;
  }
}
