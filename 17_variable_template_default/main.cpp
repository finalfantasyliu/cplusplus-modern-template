#include <iostream>
template<typename T=int>
constexpr T v{};
//也可以用非template型別參數
template<std::size_t N>
constexpr std::size_t d=N;
int main() {
    int b=v<>;//這邊需要添加<>，這樣編譯器才會覺得他是template variable

}