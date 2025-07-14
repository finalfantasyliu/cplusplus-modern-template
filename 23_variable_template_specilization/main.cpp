#include <iostream>
/*template<typename T>
constexpr const char *s="??";

template<>
constexpr const char *s<void> ="void";

template<>
constexpr const char *s<int> ="int";
*/
template<typename T>
constexpr bool is_void_t=false;

template<>
constexpr bool is_void_t<void> =true;

int main() {
    //std::cout<<s<void><<std::endl;
    std::cout<<std::boolalpha<<is_void_t<void><<std::endl;
    return 0;
}