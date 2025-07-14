#include <iostream>
//一些為相同特徵的，但還想保有彈性的type，可以使用partial specialization，例如 int* double* char*這類的，其都屬於pointer 類型
//只需要int, double, char...etc有其靈活性就可以用partial specialization
//切記function template 不能partial specialization

template<typename T>
const char *s = "?";

template<typename T>
const char *s<T *> = "pointer"; //對於pointer進行partial作partial initialization

/*template<typename T>
const char *s <T * const> ="const pointer";*/

//這是數組偏特化，但這邊有個要注意的地方，T是保有靈活性的地方，但[]是沒辦法有變化的
//因此 int[] 與 int[1]是兩種不同類型。
template<typename T>
const char *s<T[]> = "array";

template<typename T, typename T2>
const char* s1;
//這也是一種偏特化，因為主要變化為T2
template<typename T2>
const char* s1<int, T2> = "T == int";

template<typename T, typename T2>
void f(T, T2) {
    std::cout << "f(T, T2)" <<std::endl;
}
//這只是function overloading 不是partial specialization，你可以重c++ insights去觀察
//如是partial 的initialization應該要是屬於同一個primary template去發展出來，但下面顯示其是有2的primary template
//template<typename T, typename T2> 與 template<typename T2>
//而compiler實際編譯時，也不會同時instantiate 兩種 f<int, double> 與 f<double>， 只會選擇合適的
/*
#include <iostream>

template<typename T>
const char * s = "?";

template<>
const char * s<int *> = "pointer";
template<>
const char * s<void *> = "pointer";
template<>
const char * s<double *> = "pointer";
template<>
const char * s<int[1]> = "?";
template<>
const char * s<double[]> = "array";
template<>
const char * s<int[]> = "array";

template<>
const char * s<type_parameter_0_0 *> = "pointer";

template<>
const char * s<type-parameter-0-0[]> = "array";


template<>
const char * s1<int, type_parameter_0_0> = "T == int";

template<typename T, typename T2>
void f(T, T2)
{
    std::operator<<(std::cout, "f(T, T2)").operator<<(std::endl);
}

#ifdef INSIGHTS_USE_TEMPLATE
template<>
void f<int, double>(int, double);
#endif


/* First instantiated from: insights.cpp:42 #1#
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void f<double, double>(double, double)
{
    std::operator<<(std::cout, "f(T, T2)").operator<<(std::endl);
}
#endif


template<typename T2>
void f(int, T2)
{
    std::operator<<(std::cout, "f(int, T2)").operator<<(std::endl);
}

/* First instantiated from: insights.cpp:41 #1#
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void f<double>(int, double)
{
    std::operator<<(std::cout, "f(int, T2)").operator<<(std::endl);
}
#endif


int main()
{
    std::operator<<(std::cout, s<int *>).operator<<(std::endl);
    std::operator<<(std::cout, s<void *>).operator<<(std::endl);
    std::operator<<(std::cout, s<double *>).operator<<(std::endl);
    std::operator<<(std::cout, "=====================\n");
    std::operator<<(std::cout, s<int[1]>).operator<<(std::endl);
    std::operator<<(std::cout, s<double[]>).operator<<(std::endl);
    std::operator<<(std::cout, s<int[]>).operator<<(std::endl);
    f(1, 2.0);
    f(1.0, 2.0);
    return 0;
}*/


template<typename T2>
void f(int, T2) {
    std::cout << "f(int, T2)" <<std::endl;
}

int main() {
    std::cout << s<int * const> << std::endl;
    std::cout << s<void *> << std::endl;
    std::cout << s<double *> << std::endl;
    std::cout << "=====================\n";
    std::cout << s<int[1]> << std::endl;
    std::cout << s<double[]> << std::endl;
    std::cout << s<int[]> << std::endl;
    f(1,2.0);
    f(1.0,2.0);

    return 0;
}
