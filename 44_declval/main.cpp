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
/*這樣的寫法還有一個問題，就是需要使用者的class要支持default constructor(T{})，當沒有則會找不到match
*template<typename T, typename SFINAE = std::void_t<decltype(T{}+T{}),typename T::type, decltype(&T::value), decltype(
    &T::f)> >
 *
 */
/* std::declval
 * template<class T>
 * typename std::add_rvalue_reference<T>::type declval() noexcept;
 * 將任意類型T轉成引用類型，使得decltype 說明符的操作數中不並經過constructor就可使用其對應的member function
 * decltype只適用於不求值語境，不要求有定義，不能實際調用他，返回的是 T&&
* "另外 declval<Foo>() 它回傳的是一個 rvalue reference"

https://home.gamer.com.tw/creationDetail.php?sn=5646520#:~:text=%E5%8F%A6%E5%A4%96%20declval%3CFoo%3E()%20%E5%AE%83%E5%9B%9E%E5%82%B3%E7%9A%84%E6%98%AF%E4%B8%80%E5%80%8B%20rvalue%20reference

 */
template<typename T, typename SFINAE = std::void_t<decltype(std::declval<T>()+std::declval<T>()),typename T::type, decltype(&T::value), decltype(
    &T::f)> >
auto add(const T &t1, const T &t2) {
    return t1 + t2;
}

struct Test {
    Test(int v):value{v}{};
    int value;
    int operator+(const Test &t) const {
        return this->value + t.value;
    }

    using type = void;

    void f() const {
    }
};

int main() {
Test t{1};
    int i =0;

    add(t,t);
    return 0;
}
