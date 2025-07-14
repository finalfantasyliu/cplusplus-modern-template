#include <iostream>
#include <array>
/*
template<typename T,std::size_t N=10>
struct X {

};
*/
//如果你有兩個template typename 參數，沒使用到的要給予default型別，不然在推導one-arg的時候，會是too few template argument for the class template 'X'
template<typename T,typename T2=void>
struct X {
    T t;
    T2 c;
};

//記得要用homebrew載的apple 的clang實際上還是停留在clang16，不然deduce不出來，除非你寫個deduction guide
/*
you write                 compiler rewrites              actual construction
┌────────────────────────┐    ┌────────────────────────┐    ┌────────────────────────────┐
│   X x{ 1 };            │ ⇒  │   X<int> x{ 1 };       │ ⇒ │ aggregate-init t with 1     │
└────────────────────────┘    └────────────────────────┘    └────────────────────────────┘
^  (CTAD via guide)          ^  (deduced type)            ^  (real object built)
其中的 X(T)像是個inialized member lists, 假設使用X x{1},他會去找符合1個template struct 的規則
*L
*/
template<typename T>
X(T)->X<T>;
template<typename T,typename T2>
X(T, T2)->X<T,T2>;
//其實std::array的寫法也像是這樣，但std::array多了一個deduction guide可以自動讓編譯器推導
/*
* #if _LIBCPP_STD_VER >= 17
template<class _Tp, class... _Args,
         class = enable_if_t<__all<_IsSame<_Tp, _Args>::value...>::value>
         >
array(_Tp, _Args...)
  -> array<_Tp, 1 + sizeof...(_Args)>;
#endif
 */
template<typename Ty , std::size_t N>
struct array
    Ty arr[N];
};

int main() {
    //X<int>x ;
    //c++17 可以使用class template deduction，CTAD
    std::array<int,3> a = {1,2,3};
   X x{1,2};
    return 0;
}