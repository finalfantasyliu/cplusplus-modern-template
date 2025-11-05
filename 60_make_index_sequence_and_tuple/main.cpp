#include <iostream>
#include <utility>
#include <tuple>
template <std::size_t ... I>
void f(std::index_sequence<I ...>) {
    int _[] {
        (std::cout<<I<<' ',0)...
    };
};
/*c++ 20後可以在lambda使用template
 * lambda 的 operator() 成為函式模板，
 * 可同時支援型別模板參數（class T）與非型別模板參數
 * （例如 std::size_t N，甚至 std::size_t... I 這種 pack）。語法是標準化的（C++20），可再加 requires 做約束。
* // 1) 以非型別參數包產生編譯期索引（結合 index_sequence）
[&]<std::size_t... I>(std::index_sequence<I...>) {
    ((std::cout << std::get<I>(t) << ' '), ...); // 用 fold 展開
}(std::make_index_sequence<std::tuple_size_v<Tup>>{});

// 2) 純型別模板的泛型 lambda + 約束
[]<class T>(T&& x) requires std::is_integral_v<std::decay_t<T>> {
    std::cout << x << '\n';
}(42);
 */

/*下面的程是的邏輯是這樣，
 * 1. 聲明一個接受任意數量的的不同行別的type pack
 * 2. 聲明一個可parameter pack丟進tuple，也就是說tuple這邊會集成數量可變的type，這邊其實對type展開，所以想像成當你丟一個tuple<int,double> tuple的進去，那個Args就是 int, double
 * 3. 聲明一個lambda function來逐步印出裡面的值，c++20可以支援template的lambda function，所以這邊是非模版形參std::size_t，然後直接將I展開，所以假設你丟1,2,3，他就會展開成，1,2,3
 * 4. 使用comma operator的副作用，印出裡面的值
 * 5. sizeof....(Args)計算argument的數量，也就是tuple<int,double>，所以是2
 *
 * make_index_sequence是一個helper function 幫你產生std::index_sequence<0,1,2,3,4>，目前看起來都是call到編譯器的實作，在此暫不細查，但這邊提供一個csdn的簡單實現
 * https://blog.csdn.net/dboyguan/article/details/51706357
 *
 */
template<typename ... Args>
void print(const std::tuple<Args...>& t) {
    [&]<std::size_t... I>(std::index_sequence<I ...>) {
int _[] {
    (std::cout<<std::get<I>(t)<<' ',0)...
};
    }(std::make_index_sequence<sizeof...(Args)>{});
}
int main() {
f(std::make_index_sequence<10>());
    std::cout<<std::endl;
    std::tuple<int, double>tuple{1,1.2};
    size_t a=10;
    std::cout<<std::get<0>(tuple)<<std::endl;
    print(tuple);
    return 0;
}