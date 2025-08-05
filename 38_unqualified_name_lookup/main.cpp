#include <iostream>
void f() {
    std::cout<<"全局\n";
}

template<class T>
struct X {
    void f()const {std::cout<<"X\n";}
};
template<class T>
struct Y:X<T> {
    void t1() const {
        this->f(); //這邊是unqualified name所以會推遲到template instantiate時才會判定使用哪個definition
    }
    void t2()const {
        f(); //這個也是unqualified name，但沒有相依，
    }
};
struct X1 {
    void f()const{std::cout<<"X1\n";}
};

struct Y1:X1 {
    void t1()const {
        this->f();
    }
    void t2() {
        f();
    }
};

int main() {

    Y<void> y;
    y.t1();
    y.t2();


    Y1 y1;
    y1.t1();
    y1.t2();
    return 0 ;
}