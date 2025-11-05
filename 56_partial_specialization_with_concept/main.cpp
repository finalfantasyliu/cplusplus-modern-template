#include <iostream>
#include <concepts>
/*
| 寫法                                          | 主要機制                | 條件寫在哪                      | 成立時機                                          | 標準版本   | 備註                                                                      |
| ------------------------------------------- | ------------------- | -------------------------- | --------------------------------------------- | ------ | ----------------------------------------------------------------------- |
| A `std::void_t`                             | SFINAE              | 第二模板參數                     | `T::type` 可形成型別時，特化匹配                         | C++17+ | 經典 detection idiom。([en.cppreference.com][1])                           |
| B concept + constrained alias               | concept + 受約束 alias | 第二模板參數（alias `test<T>`）    | `has_type<T>` 成立 → `test<T>` 有效 → 特化匹配        | C++20  | alias template 允許 `requires`。([Stack Overflow][2])                      |
| C requires-clause on partial specialization | concept/constraints | `struct X<T> requires ...` | `has_type<T>` 成立 → 此特化可用，並參與 partial ordering | C++20  | constraints 參與偏序（subsumption）。([en.cppreference.com][3])                |
| D constrained type parameter                | 同 C（語法糖）            | `template<has_type T>`     | 同上                                            | C++20  | 等價於 `template<class T> requires has_type<T>`。([en.cppreference.com][3]) |

[1]: https://en.cppreference.com/w/cpp/types/void_t.html?utm_source=chatgpt.com "std::void_t - cppreference.com"
[2]: https://stackoverflow.com/questions/78718457/are-constrained-alias-templates-allowed?utm_source=chatgpt.com "are constrained alias templates allowed? - c++"
[3]: https://en.cppreference.com/w/cpp/language/constraints.html?utm_source=chatgpt.com "Constraints and concepts (since C++20)"

 *
 *
 */

/*
template<typename T, typename T2=void>
struct X {
    static void f(){std::puts("main template");}
};
template<typename T>
struct X<T, std::void_t<typename T::type>>
{
    using type=typename T::type;
    static void f(){std::puts("partial template");}
};*/


/*
template<class T>
concept has_type= requires { typename T::type;};

 *template<class T>
requires has_type<T>
using test=void;

template<typename T,typename T2=void>
struct X {
    static void f(){std::puts("main template");};
};

template<typename T>
struct X<T, test<T>>{
    using type = typename  T::type;
    static void f(){std::puts("partial speciallization template");};
};
*/

/*


template<class T>
concept has_type= requires { typename T::type;};
template<typename T>
struct X {
    static void f(){std::puts("main template");};
};

template<typename T>
requires has_type<T>
struct X <T> {
    static void f(){std::puts("specialization template");};
};

*/
template<class T>
concept has_type= requires { typename T::type;};
template<typename T>
struct X {
    static void f(){std::puts("main template");};
};
template<has_type T>
struct X <T> {
    using type=typename T::type;
    static void f(){std::puts("specialization template");};
};
struct Y {
    using type=void;
};
int main() {
    X<Y> x;
    x.f();
    return 0;
}