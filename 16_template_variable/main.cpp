#include <iostream>
//variable template就是template的global variable template，
//但沒有instantiate就沒法使用，所有specifier都可添加const static...
//也可以有初始值
template<typename T>
T v;

int main() {
    int a(1);
    //這兩種寫法都不能通過編譯，因為variable template 本質上就是variable，
    //v<int>(1), v<double>{2.0}
    //所以直接給()compiler會認為是function call或是轉型如int()，但你的variable不是function，也不是行別
    //而使用{}更不行，因為{}只能是type的初始化，需要variable name 不是 variable type
    v<int> = 1; //如果有constexpr 相當於constexpr int v，但記得要空格，不然會認為是>=
    v<double> = 2.0;
    v<int> =3;
    //v<double>{2.0}; //同一個函數模版生成的不同類型函數，彼此之間沒有相關性
    std::cout << &v<int> <<": "<<v<int> << std::endl;
    std::cout << &v<double> <<": "<<v<double> << std::endl;
    std::cout<< &v<int> <<": "<<v<int> <<std::endl; //這邊的 v<int>就會是一開始的v<int>=1，所以這邊就已經是3了，
    //你直接用nm 也可以看出來只有一個int v的symbol
    /*➜  cmake-build-debug nm 16_template_variable
0000000100003f80 s GCC_except_table3
                 U __Unwind_Resume
0000000100008008 D __Z1vIdE
0000000100008000 D __Z1vIiE
0000000100003ef8 t __ZNKSt3__15ctypeIcE5widenB8ne190107Ec
                 U __ZNKSt3__16locale9use_facetERNS0_2idE
                 U __ZNKSt3__18ios_base6getlocEv
0000000100003e4c t __ZNKSt3__19basic_iosIcNS_11char_trait*/



    return 0;
}
