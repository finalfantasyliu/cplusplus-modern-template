#include <iostream>
#include <string>
using namespace std::string_literals;
template<typename T>
T max(const T&a ,const T&b) {
    return a > b ? a : b;
}
namespace c1 {
    namespace c2 {
        struct cc{};
        void f(const cc&o) {
            std::cout<<"Using c1::c2::f"<<std::endl;
        }

    }
    void f(const c2::cc&o) {
        std::cout<<"Using c1::f"<<std::endl;
    }
}
void f(c1::c2::cc&o) {
    std::cout<<"Using ::f"<<std::endl;
}
namespace f1 {
    void  f(const c1::c2::cc&o) {
        std::cout<<"Using f1::f1"<<std::endl;
    }
    namespace f2 {
        void  f( c1::c2::cc&o) {
            std::cout<<"Using f2::f2"<<std::endl;
        }
        //using ::f;
        void g() {
            c1::c2::cc o;
            const c1::c2::cc c;
            //這邊就會ADL的關係，而無法選定該使用哪個f function，因為adl會依function的argument找，但現在都是const c1::c2::cc，因此compiler會給你Ambiguous call
            //即使你將global f的argument設為non const(perfect match)，也會因為name hiding而無法使用
            //ADL的查找規則，會依最近namespace可以使用的function查找，這邊會是f1::f2::f，並已此其argument所使用相依的namespace作為第二個方案，會是c1::c2::f()
            //這時若要使用他，並需使用作用域標示符::，讓global的f作為候選名單之一
            //{f1::f2::f,::f, c1::c2::f}, ::f是最佳的match

            //這時在引入一個變化，把c1::c2::f的const &cc改為非const，這時你會發現using ::f變成ambiguous call，因為他和c1::c2::f的function call 一致，compiler不知選誰
            //但可以發現其可以使用c1::c2::f的call，乃第一個lookup 會終止在f1::f2::f，所以::f永遠不會變看到，第二個look up 去判斷argument型別的作用域，為c1::c2，所以為c1::c2::f
            //所以最終會選best match (c1::c2::f)
            //f(o);
            //這邊因為第一次lookup會找最近的，所以是c1::c2::f
            f(c);
        }
    }

}
//這邊是個萬能引用(universal reference)，即接受左值expression時，deduce為l reference,若是右值expression，則為r value reference
template<typename T>
void f(T&&t) {

}
//Reference Collapsing 為rvalue reference collapse成rvalue reference，其他都是lvalue reference
template<typename Ty>
constexpr Ty&& forward(Ty& Arg) noexcept {
    return static_cast<Ty&&>(Arg);
}
int main() {
    f1::f2::g();
max(1,2);
    max<double>(1,1.2);//no deduction
    max(static_cast<double>(1),1.2);
    //max<std::string>("luse"s,"1");// 這邊會有ADL(Argument-Dependent Lookup)，詳細可以看上述，因此會跟std::max一致，產生ambiguous call
    //可以透過::max來解決
    ::max<std::string>("lues"s,"1");
    int a=10;
    f(a); //f<int &> 參數會是int&
    f(10); //f<int> 參數會是int &&
    ::forward<int>(a); //這個沒有折疊，因為只是單純的int，所以為int&&
    ::forward<int&>(a); //這個為左值引用，左值引用+右值引用&&還是左值引用
    ::forward<int&&>(a); //這個為右值引用，右值引用＋右值引用為右值引用



    return 0;
}