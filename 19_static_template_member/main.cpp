#include <iostream>
struct X {
    //static const int n=10; //這不是個definition，還是一個declaration
    static const int n=10;
};
//讀取compile期間的const variable，不是"ODR"使用，因為他是compiler time的constant
/*ODR-use (informal definition)
An object is odr-used if its value is read (unless it is a compile time constant) or written, its address is taken, or a reference is bound to it,

A reference is odr-used if it is used and its referent is not known at compile time,

A function is odr-used if a function call to it is made or its address is taken.

If an entity is odr-used, its definition must exist somewhere in the program; a violation of that is usually a link-time error.*/
//如果要符合ODR-used，就需要在類外definition，或是你加 inline，或是constexpr(包含inline的定義)，但這兩個都要c++17
const int  X::n;
struct S
{
    static const int x = 0; // static data member
    // a definition outside of class is required if it is odr-used
};
const int S::x;
const int& f(const int& r){return r;};
bool b=true;
//三元運算符需驗兩個expression的合法性，所以即使你的true，只會跑取值的部分，右邊的f(S::x)還是會驗證其合法性
int n = b ? (1, S::x) // S::x is not odr-used here
          : f(S::x);  // S::x is odr-used here: a definition is required

struct limits {
    template<typename T>
    inline static const T min{};//記得有了上述的認知，這個也只是declaration不是definition
};
/* 這樣寫也行
 * struct limits{
 *. template<typename T>
 *    constexpr static const T{}
 * }
 */

/*template<typename T>
T limits::min={};
*/


int main() {
    int b=X::n;
    std::cout<<&X::n<<'\n';
     auto p=&limits::min<int>;
    return 0;
}