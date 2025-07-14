#include <iostream>


template <typename T>
const T::type& f(const T&) {
    return 0;
}
//這邊要注意一下，:: scope的operator，其行為為”“look inside that scope for this name”，
//此:: operator解析的name是不需要runtime決定的，都可以藉由compiler parse決定 ，::通常都是指到symbol address
// class/enum/alias
struct X {
    using type = int;
};


int main() {
    X x;
    f(x);
    return 0;
}