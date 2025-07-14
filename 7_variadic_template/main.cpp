#include <iostream>
#include <numeric>
#include <string>
// 需要sum() 支援(1,2,3.5,x,n...)，其需要可以使用多個參數，多種類型
// type parameter pack
/*
void f(const char *, int, double) {
    std::puts("值");
}

void f(const char **, int *, double *) {
    puts("&");
}

template<typename... Args> //這是一個類型的組合
void sum(Args... args) {
    //這裡相當於 const char* arg0, int arg1, doulbe arg2
    f(args...); //相當於f(arg0,arg1,arg2);
    f(&args...); //相當於f(&arg0,&arg1,&arg2);
}
*/
//... 前面的東西是個模式，需要展開成模式實例，他展開的終止點為你形參包的element消耗完。

// args是函數形參包，Args是類型形參包
// args是全部傳入的參數，Args我們所有參數的 ”類型”
// 要使用他，需要用形參包展開

template<typename... Args>
void print(const Args &... args) {
    //const char(&args0)[5],const int & args1, const double &args2
    int _[]{(std::cout << args << ' ', 0)...};
    //std::cout<<sizeof(_)/sizeof(int)<<std::endl;可以寫成下方
    std::cout << sizeof ...(args) << std::endl;
    //這邊可以發現數組那個0其實沒什麼意義，只是為了初始化數組，相當於 int _{0,0,0}，這邊表示形餐包展開時，只是把模式依序複製到表達式中
    //那這邊可以執行的原因乃comma operator，comma operator 只會取最後括號的數值，而在此數值前的其他expression會執行，但不會被採用
    //(std::cout<<arg0<<' ',0),(std::cout<<arg1<<' '<<0),(std::cout<<arg2<<' ',0)
    //(std::cout<<args<<' ',0)
}

//const T(&array)[N] 為一個const & array的類型 ex: const int & [10]
//而這個N可以直接被推導不用給值，乃array的element數量為其array 數據類型的一部分
//所以expansion後為array[0], array[1]...
template<typename T, std::size_t N, typename... Args>
void f(const T (&array)[N], Args... index) {
    print(array[index]...);
    //printf(array[你指定的index第一筆]),array[你指定數組的第二筆]) ...)
}

template<typename T>
auto add(T a, T b) {
    return a + b;
}

template<typename T, typename U, typename... Args>
auto sum2(T a, U b, Args... args) {
    auto partial = add(a, b);
    if constexpr (sizeof...(args) > 0) {
        return partial = sum2(partial, args...);
    } else {
        return partial;
    }
}

template<typename... Ts>
void debug_args(const Ts &... ts) {
    std::cout << "  [";
    // binary left‐fold over comma: prints each ts << ' '
    ((std::cout << ts << ' '), ...);
    std::cout << "]\n";
}

template<typename... Ts>
void debug_inst() {
    // On GCC/Clang:
    std::cout << __PRETTY_FUNCTION__ << "\n";
    // On MSVC, you’d use __FUNCSIG__ instead.
}
//如果用這樣的寫法，sum(args...)會被推導成sum<int>，而不是sum<int, int>
//因此sum<int>實體化的function是用另一個static result，所以你永遠不會得到正確的答案
//
template<typename T, typename... Args>
T sum(T a, Args... args) {
    debug_inst<T, Args...>();
    static T result = 0;

    std::cout << "a :" << a << std::endl;
    result = add(a, result);
    std::cout << "Enter sum with a=" << a
            << "  args_pack_size=" << sizeof...(args) << "\n";
    debug_args(args...);

    if constexpr (sizeof...(args) > 0) {
        return sum(args...);
    } else {
        T temp = result;
        result = 0;
        return temp;
    }
}
//作者寫法
template<typename ...Args, typename RT=std::common_type_t<Args...>>
auto sum3(const Args &...args) {
    RT _[]{args...};
    //這邊的accumulate為此
    //template <class _Tp, size_t _Np>
    /*
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX14
            _Tp *
                    begin(_Tp(&__array)[_Np]) {
        return __array;
    }

    template
    <
    class _Tp
    ,
    size_t _Np
    >
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX14
            _Tp *
            end(_Tp (&__array)[_Np]) {
        return __array + _Np;
    }
    */
    return std::accumulate(std::begin(_), std::end(_), RT{});
}

/*
void printa(const char *word,double,double) {
    std::puts("wahaha");
}
template<typename ... Args>
void printSomething(Args ...args) {
   printa(args...);
}
*/
int main() {
    //c++ 的 variadic function只能用template
    //print("luse", 1, 1.2);
    /*int array[10]{1,2,3,4,5,6,7,8,9,10};
    f(array,1,3,5);
    int array3[]{(1,2),(2,3)};
    f(array3,0,1);*/
    //printSomething("luse",1.0,1.0);
    auto result2 = sum2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    std::cout << result2 << std::endl;
    auto result = sum<int>(1, 2);
    std::cout << result << std::endl;
    auto result3 = sum3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    std::cout<<"result "<<result3<<std::endl;
    return 0;
}
