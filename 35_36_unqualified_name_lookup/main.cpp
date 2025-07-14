#include <iostream>
#include <vector>
//這邊要注意一下，:: scope的operator，其行為為”“look inside that scope for this name”，
//此:: operator解析的name是不需要runtime決定的，都可以藉由compiler parse決定 ，::通常都是指到symbol address
// class/enum/alias
/* 在這邊會出現編譯錯誤(但在clang可以被編譯)，乃templae(alias template)的declaration與definition，不是當前instantiate的class的member時，也就是取決於某個template的member時
 * ，不會被視為是class，除非使用typenmae，或是此類型已經使用typedef或通過用作基類名。
 * type不是當前instantiate的member，當前的是f()，取決於T，也就是說你的type會因為T的行為而改變，例如我把type改成double就變掉了，所以不會被認為是type
 * https://www.cppmore.com/2022/01/09/typename-is-not-required-in-cpp20/
 */
template <typename T>
 const typename T::type& f(const T&) {
    return 0;
}

struct X {
    using type = int;
};


int p=1;

template<typename T>
void foo(const std::vector<T>& v) {
    typename std::vector<T>::const_iterator it = v.begin();

    // 下列內容沒有 'typename' 會被解析成 unqualified name 的 variable，
    // 因此會變成const_iterator 乘以 p，gcc可編，clang編譯器直接要你加typename，這個const_itertator不管在哪個實作都是個type
    // 但假設你沒有加typename，編譯器預設會認為是expression，p有值，但他乘上一個沒有具體定義的東西，會被編譯器丟棄掉
     std::vector<T>::const_iterator * p;


    typedef typename std::vector<T>::const_iterator iter_t;
    iter_t * p2; //iter_t 也也是unqualified name,但已經確認是type了，因為加了typename
}


int main() {
    X x;
    f(x);
    std::vector<int> v;
    foo(v);
    return 0;
}