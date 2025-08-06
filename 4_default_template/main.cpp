#include <iostream>
#include <string>
#include <type_traits>
using namespace std::string_literals;

template<typename T=int>
void f() {
}
/*
template<typename T1, typename T2, typename RT=decltype(true?T1{}:T2{})>
RT max(const T1& a, const T2& b) {
    return a > b ? a : b;
}*/

//c++11 後置返回類型
/*
template<typename T1, typename T2>
auto max(const T1& a, const T2& b)->decltype(true? T1{}:T2{}) {
    return a > b ? a : b;
};

*/
//但可以更簡潔，因為T1跟T2的型別在compile type是可知的，所以可以直接用variable，但其跟前個寫法會有差別，因為這樣若我們加了const
//所以使用a, b 會是const T&，若是true?T1{}:T2{}則會是單純T
/*template<typename T1, typename T2>
auto max(const T1& a, const T2& b)->decltype(a > b ? a : b) {
    return a > b ? a : b;
};*/

//還可以更簡潔
/*
auto max(const auto& a, const auto& b)->decltype(a>b?a:b) {
    return a>b?a:b;
}*/
//超簡潔 c++14(引入return type deduction,c++11不行)，但auto是默認沒有const variable和reference，所以如果要使用的話
// decltype(auto) max(const auto& a, const auto &b)
auto max(const auto&a, const auto&b) {
    return a>b?a:b;
}


int main() {
    //f<double>();
    //f();
    max(1,1.2);
    /*
     * 這個會報錯，是因為std::string無法轉型成double，
     * 但有人就會想說用RT放在template參數前面，然後直接指名，
     * template<typename RT, typename T1, typename T2>
     * max<std::string>("1","2"s);
     * 但這樣其實沒有推導的過程
     */
    max("1","2"s);
    /*
     * decltype()是compile-time的function，而若搭配ternary operation時，
     * c++會審視 2nd 與3rd的operands，找出兩者之間的common type，有以下的規則可以follow
     * 1. Arithmetic vs. arithmetic → pick the wider arithmetic type (e.g. double).
     * 2. class + something convertible to class → pick the class type (e.g. std::string wins over const char*).
     * 3. class + something not convertible -> error
     * 所以下方的integer與double，double的廣度較高，所以是double
     * 所以operand 1 true, false根本沒有用，只是要達成expression 而已
     * decltype(true? int{}: double{})這也ok，但其有不求值語境(unevaluated operand)，所以即使是std::string{}此臨時物件有不會創造，其只關心type
     * 以下為其他unevaluated operand
     * sizeof(expr)
     * noexcept(expr)
     * std::declval<T>()
     */
    using T=decltype(true?1:1.2);
    using T2=decltype(false?1:1.2);

    std::cout<<std::is_same_v<T,T2><<std::endl;
    return 0;
}
