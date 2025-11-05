#include <iostream>
#include <type_traits>
#include <concepts>

//requires expression 為產生constraint的 bool constant(pure rvalue)
//只要{}內部在替換T時的語法是合法的就return true，不合法就false
/* 基本語法
 *  requires {}
 *  requires(parameter list){ requirements}
 */

//這要加typename，不然T::type不會認為是type，編譯器會認為可能是class function, class member
//所以切記你的需求是啥，如果是typename T::type那他就會是type，若單純的是T::type，那就會是class member(視為variable)
template<typename T>
void f(T) {
    constexpr bool v=requires{T::type;};
    std::cout<<std::boolalpha<<v<<std::endl;
}
struct X {
    using type=int;
};
struct Y {
    static constexpr int type=0;
};
int main() {
    f(1);
    f(X{});
    f(Y{});
    return 0;
}