#include <iostream>
#include <type_traits>
#include <concepts>

/*mq 白沒有特別說明require claude 與require expression
*template<class T>
concept AddableSameType = requires(T a, T b) {
    { a + b } -> std::same_as<T>;   // compound requirement：型別約束
    { a + b } noexcept;             // compound requirement：不丟出
};
requires(){}這種的為require expression，而這種expression會回傳一個bool的常量，
template<typename T>
auto  sum(T &a , T& b) requires AddableSameType<T> 這邊的 requires接一個bool 常量，所以是requires claude
{
return a+b;
}
所以延伸
template<typename T>
auto sum (T &a, T& b) requires requires(T a , T b){ a+b}，這種寫法就是，第一個requires就是requires claude，第二個回傳bool constants所以是require expression
但這要的寫法會導致你後面的requires(T a, Tb ){a+ b}這個expression會與sum綁定，不能重用
*/

template<typename T>
concept Integral= std::is_integral_v<T>;

//這種方式是conjunction的constraint
template<typename T>
concept SignedIntegral=Integral<T> && std::is_signed_v<T>;

void s_f(const SignedIntegral auto &){

}
struct X {
int c{};
};
//要求T 它是sizeof 大於 1，並且支持一個函數調用
/*template<typename T>
requires (sizeof(T)>1) && requires (std::is_integral_v<T>) //這樣的寫法會是錯的，因為這邊再寫一次requires會認為要接一個 requires expression
void f(T) {

}*/
template<typename T>
requires (sizeof(T)>1 && std::is_integral_v<T>)
void f(T) {

}

template<typename T>
constexpr  bool get_value(){return true ;};
//用&&是conjunction，用||是disjunction
//這個get_value是編譯期bool constant
template<typename T>
requires(sizeof(T)>1 || get_value<T>())
void f1(T){};
int main() {
    std::cout << "Hello, World!" << std::endl;
    s_f(1);
    //s_f(1u);
    X x;
    f1(x);
    return 0;
}