#include <iostream>

template<typename T>
struct A {
    struct B{} ; //成員類
    template<typename U>
    struct C{};//成員類模版
};

template<>
struct A<void> {
    void f();
};
void A<void>::f() {std::puts("A<void>::f()");};

//特化成員類 A<char>的情況下B類的定義
template<>
struct A<char>::B {
    void f();
};
void A<char>::B::f() {
std::puts("A<char>::B::f()");
};

//特化成員類模版 A<int>的C的類模版的主模版
/*
* The key point is that the argument list after C must differ from the
primary template’s pattern, otherwise the declaration is ill-formed because
it would merely duplicate the primary
 */
template<>
template<typename U>
struct A<int>::C{ //這邊不能再使用 struct A<int>::C<U>是因為這樣表示其C需要偏特化，( error: class template partial specialization does not specialize any template argument; to define the primary template, remove the template argument list)
void f();
};


template<>
template<typename U>
void A<int>::C<U>::f() {
    std::puts("A<int>::C<U>::f()");
}

//這個chatgpt的寫法已經沒有B這個member，完全是一個全新的A<int>{}, {}裡面已經跟主template<typename T>A沒有相關連了
/*
template<>
struct A<int>{
    template<typename U>
    struct C {
        void f();
    };
    struct B{};
};
template<typename U>
void A<int>::C<U>::f() {
    std::puts("A<int>::C<U>::f()");
}
*/

//class內有function template
struct X {
    template<typename T>
    void f(T){};
};

template<>
void X::f<int>(int) {
    std::puts("X::f<int>()");
    return;
}

template <>
void X::f<double>(double) {
   std::puts("X::f<double>()");
}

//specialize class template's function template member

template<typename T>
struct Y {
    template<typename N>
    void f(N){}

    template<> //在class內部無法指定最外層的Y，因為namespace的關係，你的class的body不是namespace
    void f<int>(int) {
        std::puts("f<int>(int)");
    }
};

template<>
template<>
void Y<void>::f<int>(int) {
    std::puts("Y<void>::f<double>(double)");
}
//這邊要注意的是如過你已經有implicit instantiation了，
//你的class template內部的member template 還是可以explicit specialization,
//不受提前implicit instantiation的影響
Y<int>y;

template<>
template<>
void Y<int>::f<int>(int) {
    std::puts("Y<int>::f<int>(int)");
}

int main() {
    A<void> a;
    a.f();
    A<char>::B b;
    b.f();
    A<int>::C<int> c;
    //這個可以測試這兩者的差異
    //A<int>::B b2;
    X x;
    x.f(10);
    x.f(20.0);
    y.f<int>(10);

    return 0;
}