int main()
{
    std::vector<int> v = { 8, 3, 7, 4, 2, 9, 3 } ;
    std::size_t size = v.size() ;

    // この部分を繰り返す？ 
    { // これ全体が1つのブロック文
        std::size_t min = 0 ;

        for ( std::size_t index = 1 ; index != size ; ++index )
        {
            if ( v.at(index) < v.at(min) )
                min = index ;
        }

        // 出力
        std::cout << v.at(min) << " "s ;

        // 先頭と交換
    }
}