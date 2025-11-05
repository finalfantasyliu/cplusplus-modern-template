#include <iostream>
#include "test.h"
//這篇算是一個full specialization 與 explicit template的總結
int main() {
    //這邊如果你沒有全特化與顯示特化，編譯器會無法實體化，因為function template只有在實體化後才有symbol
    f(15);
    X<int> x;
    //class template只要管member是否有定義，不會管member function是否有定義，除非有使用到它，
    //若要使用除非使用全特化或是顯示實例化
    x.f();
    Foo<int> foo;
    foo.fun();
    foo.this_will_compile_right();
    return 0;
}