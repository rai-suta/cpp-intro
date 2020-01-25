/*
auto output_all = []( auto first, auto last )
{
    for ( auto iter = first ; iter != last ; ++iter )
    {
        std::cout << *iter << "\n"s ;
    }
} ;
*/

auto output_all = []( auto first, auto last, auto output_iter )
{
    for ( auto iter = first ; iter != last ; ++iter, ++output_iter )
    {
        *output_iter = *iter ;
    }
} ;

int main()
{
    std::vector<int> v = {1,2,3,4,5} ;
    
    output_all( std::begin(v), std::end(v),
                std::ostream_iterator<int>(std::cout) ) ;
}
