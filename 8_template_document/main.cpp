#include <iostream>
#include "test.h"
#include "test_template.h"

//可以使用clang++ -E 來查看preprocess 一些macro與include的文件，如下方的範例，
//其實可以替換成
//而當我們使用include test.h或test_template.h，compiler 會預期這些未找到function的definition，
//在靜態或動態連結時找到對應的function 的definition，而最終解析完成是linker做的事情。
//但如果使用template function，如下所示，單純的include但沒使用他，根本沒有instantiate，會導致compile error，
//因為他根本找不到他的定義，所以基本上通常會把definition同時放在header file，讓引用的file，能直接instantiate對應的function
//但可以使用explicit instantiate來達成分document的需求
/* test_template.h
 * template<typename T>
 * void f_t(T);
 *
 * test_template.cpp
 * template<typename T>
 * void f_t(T){
 *
 * }
 *
 * main.cpp
 * #include "test_template.h"
 * int main(){
 * f_t(1);//對他來說，f_t(T)，但因為沒有定義，他不能implicit轉換對應的function內容，沒法替換definition copy
 * }
 *
 *
 * 可透過explicit instantiation
 * extern template<typename T>f_t<int>(int);//這樣會通知compile不要產生function替換的 definition copy，去其他translateion unit找
 *
 */

/*
# 4 "./main.cpp" 2
int main() {
    int array[] = {
# 1 "./array.txt" 1
        1, 2, 3, 4, 5
# 7 "./main.cpp" 2
    };
    for (int i = 0; i < sizeof(array) / sizeof(int); ++i) {
        std::cout << array[i] << " ";
    }
    return 0;
}
*/

/*int main() {
int array[]={
#include "array.txt"
};
    /*
    for (int i = 0; i <sizeof(array)/sizeof(int); ++i) {
        std::cout << array[i] <<" ";

    }
    #1#
    return 0;
}*/

int main() {
    return 0;
}