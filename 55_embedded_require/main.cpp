#include <iostream>
#include <concepts>
#include<type_traits>

template<typename T>
concept C3 = requires(T a)
{
    //只要requires 後面的expression return true/false即可(compile time)
    requires std::is_same_v<T, int> ; //要求T是int
    requires std::same_as<T, int>;
    requires requires { a + a; };
    //單純這樣寫，只是判定表達式合不合法
    //sizeof(a) > 4;
    //這樣才是約束
    requires sizeof(a)>4;
};

int main() {
    std::cout << C3<int> << std::endl;
    std::cout << sizeof(double) << std::endl;
    return 0;
}
