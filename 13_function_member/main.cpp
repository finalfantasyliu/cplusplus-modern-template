#include <iostream>
 template<typename T>
struct Class_template {
     void f(T) { //這個不算成員函數模版，這個是跟class一起實體化，並不獨立
     }
     template<typename... Args> //這個才是成員函數模版，不依賴class的實體化
     void f1(Args&&...args) {
     }
 };

int main() {
    Class_template<int>t; //這樣的f()也一起實體化為f(int)
    t.f1(1,3,4,5);
    return 0;
}