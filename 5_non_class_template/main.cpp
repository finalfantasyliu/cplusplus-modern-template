#include <iostream>
#include <string>
/*
 * 通常這種non-type template parameter的寫法，
 * 是為了在編譯期就取得對應的數值，例如std::array的std::array<T, N>中的N就是這個形式，
 * 或是要取得mask值，例如下方
 * template <std::size_t Bits>
 * struct BitMask{
 * static constexpr std::unsigned long long mask=(Bits==64?~0ull:((1ull<<Bits)-1))
 * };
 */
template <std::size_t N=66>
void f() {
    std::cout<<N<<std::endl;
}

int main() {
    f<100>();
    f();
    return 0;
}