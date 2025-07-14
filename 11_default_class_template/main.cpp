#include <iostream>

template<typename T=int>
struct X {
};

struct Test {
    X<> x; //單純X是不ok(即使c++17也不行，不管你是什麼static等等都需要，gcc會過，但是是bug，clang與msvc不會過)
};

int main() {
    //如果單純的class template也可以有default value，但相較於function template有一些不同
    //在C++11你即使加了默認的class type，但在實體化時，需要添加<>以利compiler 推導，c++17不用
    /*
    #include <iostream>
template<typename T=int>
struct X{};
int main() {
   X<> x; //C++11OK
   X x2; //C++17OK
   return 0;
}
*/
//然而即使可以不添加<>，但若此class為其他class的member時也需要加<>，只允許在全局或function的scope中
    X x;
    return 0;
}
