#include <iostream>

template<typename T>
struct Test {
    Test(T v): t{v} {
    }

private:
    T t;
};

//模版名稱(可放實際推導類型a，或是讓編譯器推導)->模版名稱<想要讓a被推導的類型>
Test(int) -> Test<std::size_t>;

template<typename T, size_t N>
struct array {
    T arr[N];
};

template<typename T>
auto sum(T t) {
    return t;
}

//這邊要算1，因為其推導N時，你的T t 已經被抽出來了，他屬於你size_t非類型模版的第一個推導參數，把他想成若你要進行實作加總sum()功能
/* template <typename T, typename ... Args>
template<typename T, typename ... Args>
auto sum(T t, Args...args) {
    if (sizeof...(Args)>0) {
        return t+sum(args...);
    }else {
        return t;
    }
}
所以像是array(int , int , int ...)
 */
template<typename T, typename... Args>
array(T t, Args... args) -> array<T, 1 + sizeof...
                                     (Args)>;

int main() {
    //auto a = sum(1, 2, 3, 4, 5);
    //std::cout << a << std::endl;
    ::array arr{1, 2, 3};
    std::cout << arr.arr[0] << std::endl;
    return 0;
}
