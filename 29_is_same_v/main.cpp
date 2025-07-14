#include <iostream>
// std::is_same_v
#include <type_traits>
std::is_same
template<class,class>
struct is_same {
    static constexpr bool value = false;
};
template<class Ty>
struct is_same<Ty,Ty> {
    static constexpr bool value = true;
};
int main() {

    std::cout<<std::boolalpha<< is_same<int,int>::value<<std::endl;
    std::cout<<i
    return 0;
}