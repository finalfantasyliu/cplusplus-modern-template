#include <iostream>
#include <type_traits>
/* std::void_t
 * template<class ...>
 * using void_t = void
 */

/* 如果要寫一個template function add，要求其class需要有operator + 的overloading，也要有alias type，還有member  value,f
 * template<typename T,typename T2=void_t<typename T::type, decltype(T{}.value), decltype(T{}.f())>
 * auto add( T & t1, T &t2)->decltype(t1+t2){
 * return t1+t2
 * }
 */
struct X {
    using type=int;
    int value=0;
    void f(){};
    X(){};
    X& operator +(X &rhs) {
        return *this;
    }
};
template<typename T1, typename T2=std::void_t<typename T1::type, decltype(&T1::value), decltype(&T1::f)>>
auto add( T1& t1, T1& t2)->decltype(t1+t2) {
    return t1+t2;
}
struct Y {
    int value=10;
};
int main() {
    X a,b;
  auto &r= add(a,b);
    Y c;
    auto p = &Y::value;
    //這種寫法是pointer to member
    c.*p=42;
    //using type=std::void_t<int,double,char, std::string>;//這個最後都是void，只是std::void_t為你SFINAE提供的工具variable
    return 0;
}