#include <iostream>

template<typename T, typename T2=typename T::type>
void f(int) {
    std::puts("int");
}

template<typename T, typename T2=decltype(T{} + T{})>
void f(double) {
    std::puts("double");
}

struct X {
    using type = int;
};

//template有兩次substitution，
/* 1. 在template的parameter推導前，先帶入指定的parameter，ex f<int>()
 * 2. 在template的parameter推導後，對推導的parameter進行替換，但若你直接f<int>是不會走到這一步的，除非你有其他parameter，例如有default的parameter
*代换的实参写出时ill-formed（并带有必要的诊断）的任何场合，都是代换失败。ex X{}+X{}

”对显式指定的模板实参进行代换“这里的显式指定，就比如 f<int>() 就是显式指明了。我知道你肯定有疑问：我都显式指明了，那下面还推导啥？对，如果模板函数 f 只有一个模板形参，而你显式指明了，的确第二次代换没用，因为根本没啥好推导的。

两次代换都有作用，是在于有多个模板形参，显式指定一些，又根据传入参数推导一些。
 */
int main() {
    //現在T=int，但顯然T沒有::type的成員type，所以編譯器會直接報錯，屬於substitution failed，因為他找不到其他template可以使用
    // candidate template ignored: substitution failure [with T = int]: type 'int' cannot be used prior to '::' because it has no members
    // 3 | template <typename T,typename T2=typename T::type>
    //但倘若新添加一個f(double)，這時函式重載決議就可以找到了
    f<int>(1);
    //這時是X X::int，所以符合
    f<X>(1);
    //理論上他要走decltype(X{}+X{})，但X{}+X{}本身不合法，因為他推導不出來，所以選了例外個候選人
    //但如果是decltype(int{}+int{})記得是合法的歐
    f<X>(1.2);
    return 0;
}
