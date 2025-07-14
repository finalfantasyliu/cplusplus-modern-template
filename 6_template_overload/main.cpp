#include <iostream>
#include <string>

//template的function也可和一般function overload，編譯器會選擇合適的進行呼叫
template<typename T>
void test(T) {
    std::puts("template");
}
void test(int) {
    std::puts("int");
}

int main() {
    //overloading resolution->選擇最"匹配"與最"合適”的function
    test(1);//優先選擇非template的function
    test(1.0);//implicit instantiation
    test("1");
    return 0;
}