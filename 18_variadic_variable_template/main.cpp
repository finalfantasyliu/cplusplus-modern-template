#include <iostream>
template<typename ... Args>
std::size_t N=sizeof...(Args);
//這個是比較實際應用的variadic template variable
template<std::size_t ... value>
constexpr std::size_t array[]{value...};
int main() {
    std::cout<<N<int, void, double> <<std::endl;
    for (const auto&i:array<1,2,3,4,5>) {
        std::cout<<i<<std::endl;
    }
    std::cout<<std::is_same_v<decltype(array<1,2,3,4,5>), const std::size_t [5]><<std::endl;;
    return 0;
}