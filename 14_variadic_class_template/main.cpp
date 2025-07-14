#include <iostream>
#include <tuple>

template<typename... Args>
struct X {
    X(Args... args): value{args...} {
    };
    std::tuple<Args...> value;
};
//這邊實際展開如下所示


/*
#include <iostream>
#include <tuple>

template<typename... Args>
struct X {
    inline X(Args... args)
        : value(args...) {
    }

    std::tuple<Args...> value;
};

/* First instantiated from: insights.cpp:11 #2#
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct X<int, const char *, char, int>
{
    inline X(int __args0, const char * __args1, char __args2, int __args3)
    : value{std::tuple<int, const char *, char, int>(__args0, __args1, __args2, __args3)}
    {
    }

    std::tuple<int, const char *, char, int> value;
};

#endif

int main() {
    X<int, const char *, char, int> x = X<int, const char *, char, int>{1, "2", '3', 4};
    std::operator<<(std::operator<<(std::cout, std::get<1>(x.value)), '\n');
    return 0;
}

template<typename... Args>
X(Args... args) -> X<Args...>;

/* First instantiated from: insights.cpp:11 #1#
#ifdef INSIGHTS_USE_TEMPLATE
template<>
X(int __args0, const char * __args1, char __args2, int __args3) -> X<int, const char *, char, int>;
#endif
*/



int main() {
    std::tuple<int, double> t{1, 1.2};
    std::get<int>(t); //這邊最好是用index取得，因為可能有都是int的情形
    X x{1, "2", '3', 4};
    std::cout << std::get<1>(x.value) << std::endl;
    return 0;
}
