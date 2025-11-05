#include <iostream>
#include <string>
template<typename T>
concept Addable=requires(T a, T b)
{
  a+b;
};
//這個&&不是universal reference，要universal reference必須是在function template
//在requires中型別已在進入requires expression固定型別了，所以這邊rvalue reference，進到scope裡時是l value，然後為了轉成r value，所以用std::forward<T>進行轉換
template<typename T, class U>
concept Swapable=requires(T &t, U  &u)
{
    swap(std::forward<T>(t),std::forward<U>(u));
    swap(std::forward<U>(u),std::forward<T>(t));
};
template<typename T>
requires (Addable<T> && Swapable<T,T>)
struct Test{};
//而若沒有const 這個qualifier會出錯，因為右值無法接受沒有const的reference，
//因為修改一個即將被銷毀的物件不符合語意，而且他已經被削毀了，你可能會指向一個後續會分配記憶體的區塊
//導致程式操作不安全
namespace test_complex {
    struct X {
        X operator+(const X& )const {
            return *this;
        }
    };
    void swap(  const X& x,  const X& y){};

}
void take_cref(const std::string &);
void take_lref(std::string &);
int main() {
   // take_cref(std::string{});
//    take_lref(std::string{});
    Test<test_complex::X> t2;
    return 0;
}