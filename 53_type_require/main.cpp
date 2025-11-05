#include <iostream>
//類型要求

template<typename T>
struct S{};

template<typename T>
using Ref=T&;

template<typename T>
concept C = requires
{
    //嵌套類型就兩種，要嗎類中類，或是類中alias
    typename T::X2; //要求嵌套類型
    typename T::type; //要求嵌套的類型
    typename S<T>; //這邊要求S這個template的特化，可以帶入你的T
    typename Ref<T>;//要求alias的template可以使用
};

struct X {
    using X2 = int;
    using type=int;
};

struct Y {
    struct X2 {
    };
};

int main() {
    std::cout << std::boolalpha << C<X> << std::endl;
    std::cout << std::boolalpha << C<Y> << std::endl;
    return 0;
}
