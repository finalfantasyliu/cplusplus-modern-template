#include <iostream>

//特化必須在導致implicit instantiation使用之前，需在每個translation unit中先define
/*template <typename T>
void f(const T& ) {

}
template <>
void f<int>(const int&) {

}
void f2() {
    f(1);
}*/
//這個若沒在f2之前define，會出現implicit instantiation，所以會報錯
/*template <>
void f<int>(const int&) {

}*/

//只有聲明沒有定義的template specialization 可以相其他不完整類型一樣使用(ex: pointer and reference)
template <class T>
class X;
template<>
class X<int>;
X<int>* p;
//X<int> x; //Type X<int> is incomplete
//void a; //Type void is incomplete
//void *a; 這個就可以
/* function template與variable template的specialization是否為 inline/constexpr/constinit/consteval
 * 只與explicit specialization有關，主template的declaration是否有待specifier對其沒有影響，template declaration出現的屬性在explicit specialization也沒有效果
 *
 */
template<typename T>
int f(T) {
  return 6;
}
template<>
constexpr int f<int>(int) {
    return 6;
}
template<typename T>
constexpr int g(T){return 6;}

template<>
int g<int>(int) {
    return 6;
}
int main() {
    //這個constexpr只與其explicit specialization有關，跟主模版 int f(T)沒有關
    constexpr auto n=f<int>(0);
    //這個就會error了
    //constexpr auto m=f<double>(0);

    //這個就可以顯示你已經有explicit的specialization，只會看其explicit的specifier，跟主template的 constexpr int g(T){return 6;}沒有關係
    //constexpr auto o=g<int>(0);

    constexpr auto o=g<double>(0);
    return 0;
}