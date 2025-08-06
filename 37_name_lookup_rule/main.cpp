#include <iostream>
void g(double){std::cout<<"g(double)\n";}

//non-dependent name在definition時機，進行查找，不會推遲到template instantiate，
//即時template instantiate 後，有更好的match，也保持原始綁定的定義。
template <typename T>
struct S {
    void f()const {
     g(1);
    }
};
void g(int) {
    std::cout << "g(int)\n";
}

int main() {
    g(1);
    S<void> s;
    s.f();

    return 0;
}