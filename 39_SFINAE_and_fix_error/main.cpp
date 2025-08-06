#include <iostream>

template<typename T>
struct B {
    using type = typename T::type;
};

template<typename T>
void foo(double) {
    std::puts("SFINAE");
}

template<
    class T,
   // class U=typename T::type, //如果T沒有type就是SFINAE
    class V=typename B<T>::type>//這邊會有fix error，因為B<void>會instantiated導致side-effect
///Users/finalfantasyliu/Desktop/cplusplus-modern-template/39_SFINAE_and_fix_error/main.cpp:16:22: note: in instantiation of template class 'B<void>' requested here
   //16 |     class V=typename B<T>::type>
void foo(int) {
    std::puts("SFINAE T::type B<T>::type");
}
//hard error為對於template的parameter代換的時候，對於其表達式與類型求值導致的錯誤，就是hard error，像是instantiate template的specilization或是implicit instantiate member function ，上述的B<void>::type 就是對B<void> instantiation
/* 發生位置
是否屬於 immediate context
處理方式
函式簽名、template 參數類型、decltype 裡
是
SFINAE（候選移除、不報錯）
函式體內、在代換中引入副作用
否
硬錯（編譯失敗、報錯）

 *
 *
 */
int main() {
    //void就沒有type所以失敗
    /* class void
     * class U=typename void::type
     * class V=B<void>::type
     */
    foo<void>(1);
    struct C {
        using type = int;
    };
    foo<C>(1);

    //foo<B<C>>(1);
}
