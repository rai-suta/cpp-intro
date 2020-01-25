auto output_all = []( auto first, auto last )
{
    for ( auto iter = first ; iter != last ; ++iter )
    {
        std::cout << *iter << "\n"s ;
    }
} ;


int main()
{
    std::filesystem::directory_iterator first("./"), last ;

    output_all( first, last ) ;
}