# 名詞解釋
## dependent name
`當你的當前template的defintion中的變數或expression依賴著type T而改變者就稱dependent name，如下所示`
```c++
//這個有可能是X::int，或是Y::double，但編譯器不知道這是不是type 有可能只是variable，
//所以你要添加typename
template <typename T>
 const typename T::type& f(const T&) { /
    return 0;
}

struct X {
    using type = int;
};
```

```c++
int p=1;

template<typename T>
void foo(const std::vector<T>& v) {
    typename std::vector<T>::const_iterator it = v.begin();

    // 下列內容沒有 'typename' 會被解析成 qualified name 的 variable，
    // 因此會變成const_iterator 乘以 p，gcc可編，clang編譯器直接要你加typename，這個const_itertator不管在哪個實作都是個type
    // 但假設你沒有加typename，編譯器預設會認為是expression，p有值，但他乘上一個沒有具體定義的東西，會被編譯器丟棄掉
     std::vector<T>::const_iterator * p;

    typedef typename std::vector<T>::const_iterator iter_t;
    iter_t * p2; //iter_t 也也是unqualified name,但已經確認是type了，因為加了typename
}
```

## non-dependent name
`基本上沒有依賴著template中的T決定其type這為non-dependent name，基本上不會等template instantiatie後才決定`
```c++
void g(double) { std::cout << "g(double)\n"; }

template<typename T>
struct S {
    void f() const { g(1); }   // 這個g已經知道其definition了，也不依賴著T
};

```
#備註：在某些情況non-dependent name會因為一些原因導致definition改變(ill-formed NDR[no diagnostic required])
1. incomplete type-> complete type (`a type used in a non-dependent name is incomplete at the point of definition but complete at the point of instantiation`)
    ```c++
   struct Foo;               // 前向宣告，不完整

    template<typename T>
    void bar() {
    Foo x;                // 非待決名 Foo；此時 incomplete → OK
    }

    struct Foo { int i; };    // 之後完成定義

    int main() { bar<int>(); }
   ```
2.  using-declaration 來自 pack expansion，展開後變空(c++ 17以上) (`
    lookup for a name in the template definition found a using-declaration, but the lookup in the corresponding scope in the instantiation does not find any declarations because the using-declaration was a pack expansion and the corresponding pack is empty`)
    ```c++
    template<typename... Ts>
    struct A {
    using Ts::g...;       // 若 Ts 為空 pack，這行不留下任何宣告
    void f() { g(); }     //理論上為non-dependent name，但在因應Ts::g...這個class scope的關西，會依賴他(dependent context)，所以會變成ill-formed的形式，
    };

    struct B { static void g(); };

    A<B> a1;  // Ts = B → g 可見，這邊也會報錯，因為在class裡面使用using將class的static member帶入當前的class，必須要是base class，也就是A:Ts... 
    A<>  a2;  // Ts = ❶ 空 → g 消失；f 裡的 g 失去目標（ill-formed NDR）
    ```
    下面才正確寫法，
    ```c++
    template<typename ... Ts>
    struct A:Ts...{
    using Ts::g...;
    void f(){(Ts::g(),...)};//這變得Ts完全變dependent context了
    }
    //備註: 
    /*根據 C++23 §7.3.4 [namespace.udecl]/15（舊版條款號可能不同）：
    class定義中的 using-declaration
      只能 指向
      * (a) 這個類別的基底類別成員，或
      * (b) 導入基底類別的構造函式、析構函式、轉換函式等特殊成員。
    */
    ```
3. an instantiation uses a default argument or default template argument that had not been defined at the point of definition
    ```
   struct X;                        // 不完整

    template<typename T = X>
    struct S {
    void f() { sizeof(T); }      // 非待決名 T；此處不完整
    };

    struct X { int i; };             // 之後補完

    S<> s;   // 實例化時 sizeof(T) 需要完整型別 → 變臉
   ```
 4. a constant expression at the point of instantiation uses the value of a const object of integral or unscoped enum type, the value of a constexpr object, the value of a reference, or the definition of a constexpr function(since C++11), and that object/reference/function(since C++11) was not defined at the point of definition
    ```c++
    template<int N>
    struct C {
    static_assert(N == 4, "");   // N 用的是常量 k
    };

    extern const int k;              // 只宣告，未定義
    const int k = 4;                 // 之後才定義，假設這是外部的TU定義

    C<k> c;   // POI 需要 k 的數值＝4，但定義時並不知道 
    ```
 5. the template uses a non-dependent class template specialization or variable template specialization(since C++14) at the point of instantiation, and this template it uses is either instantiated from a partial specialization that was not defined at the point of definition or names an explicit specialization that was not declared at the point of definition
 
    ```c++
    //寫在同一個TU，會看不到效果
        template<typename T> struct Vec { static const int id = 0; };
        template<> struct Vec<int>  { static const int id = 1; };

        template<typename T>
        void foo() {                  // Vec<char>::id 是 non-dependent！
        int x = Vec<char>::id;    // ← 在此就決定要用 Vec<char>
        }

        template<> struct Vec<char> { // 特化太晚宣告 → IFNDR，compiler會直接出現另外的錯誤，因為他會implicit instantiation
        static const int id = 2;
        }

    int main() { foo<int>(); }
    ```
    vec.cpp
    ```c++
    #pragma once
    #include <iostream>

    template<typename T> struct Vec { static const int id = 0; };
    template<> struct Vec<int>  { static const int id = 1; };

    template<typename T>
    void foo()                    // Vec<char>::id 與 T 無關 → non-dependent
    {
    std::cout << Vec<char>::id << '\n';   // 在此隱式實例化 Vec<char>
    }
    ```
    use.cpp
    ```c++
    #include "vec.hpp"
    int main() { foo<long>(); }   // 只看到主樣板 → id==0
    ```
    spec.cpp
    ```c++
    #include "vec.hpp"
    template<> struct Vec<char> { static const int id = 2; };
    ```
## Qualified vs Unqualified name
Qualified只有三種才是qualified name，並起要在::，都是由左至右解析 A::B::C
- class member (including static and non-static functions, types, templates, etc),
- namespace member (including another namespace),
- enumerator.
| Code fragment                         | Qualified? | Reason                                                                                                                                  |
| ------------------------------------- |------------|-----------------------------------------------------------------------------------------------------------------------------------------|
| `Y<T>::t2` (the function name itself) | **Yes**    | Scope operator `::` precedes `t2`.                                                                                                      |
| Inside that body, the call `f();`     | **No**     | Just `f`, no `::` or `this->`.                                                                                                          |
| `this->f();`                          | **No**     | `this->` explicitly says “look in the object’s class”.但因為不是::右邊所以不算qualified name，他只是指向基底類別，但基底類別又依賴T，所以可能變成dependent name推遲到第二階段lookup |
| `Base<T>::f();`                       | **Yes**    | Contains `::`.                                                                                                                          |

## Two-phase lookup
```pqsql
                     ┌──── Phase 1 ────┐          ┌──── Phase 2 ────┐
                     │   (定義時)       │          │  (實例化時)      │
┌─────────────┐      │                 │          │                 │
│ template<T> │──────┼─────────────────┼──────────┼─────────────────┼──► 時間
└─────────────┘      │  非 dependent   │          │  ✱ dependent    │
                     │  ═══════════════│          │  ═══════════════│
                     │  ① 普通查找      │          │ ①'' 普通查找     │
                     │  (qualified +   │          │  (僅剩待決)       │
                     │   unqualified)  │          │                 │
                     │                 │          │ ② ADL *一次*     │
                     │                 │          │                 │
                     │ ② ADL *一次*     │          │                 │
                     └─────────────────┘          └─────────────────┘
                      ↑            ↑               ↑
       ----------  決定 "什麼名字在 Phase 1 就被鎖定"  ----------

LEGEND
┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈
• **dependent name**  → 属於右邊 ✱ 區塊，延後到 Phase 2 才解析  
• **unqualified name**→ 只有「普通查找+ADL」能找到它  
• **qualified name**  → 完全靠「普通查找」，不跑 ADL  

```

## ADL
| 步驟             | 作用                                                                                                                         
| -------------- | --------------------------------------------------------------------------------------------------------------------------- 
| **① 一般未限定查找**  | 由最內層作用域往外層尋找第一個同名函式，遇到就停止。([0x2B\|\~0x2B][1])                                                                               |    
| **② ADL 補充候選** | 針對每個實參型別 `Ti`，把它的「**關聯命名空間／關聯類別**」中的同名函式全部加入候選集合。若 `Ti` 是基本型別，則沒有關聯命名空間，ADL 不生效。([en.cppreference.com][2], [zhengyi.me][3]) |    
| **③ 重載決議**     | 對 ① + ② 的所有候選，同時執行重載解析與可行性檢查，選出最佳匹配。([quuxplusone.github.io][4])                                                            |    

[1]: https://www.gonwan.com/2014/12/12/two-phase-lookup-in-c-templates/?utm_source=chatgpt.com "Two-phase Lookup in C++ Templates | 0x2B"
[2]: https://en.cppreference.com/w/cpp/language/adl.html?utm_source=chatgpt.com "Argument-dependent lookup"
[3]: https://zhengyi.me/2018/05/22/what-is-argument-dependent-lookup/?utm_source=chatgpt.com "什么是Argument Dependent Lookup | yi's weblog"
[4]: https://quuxplusone.github.io/blog/2019/04/26/what-is-adl/?utm_source=chatgpt.com "What is ADL? – Arthur O'Dwyer – Stuff mostly about C++"
https://blog.csdn.net/qq_17550379/article/details/80007769
```c++
#include <iostream>
namespace c1{
    namespace c2
    {
        struct cc{};
        void f(cc& o){std::cout<<"from c1::c2::f"<<std::endl;};
    }
    void f(const c1::c2::cc& o){std::cout<<"from c1::f"<<std::endl;};
}
void f(c1::c2::cc& o){
    std::cout<<"from global f"<<std::endl;
}
namespace f1{

    void f(const c1::c2::cc& o){std::cout<<"from f1::f"<<std::endl;};//因為一般查找以被擋住了
    namespace f2{
        void f(const c1::c2::cc& o){std::cout<<"from f1::f2::f"<<std::endl;}
        void g(){
            c1::c2::cc o;
            const c1::c2::cc c(o);
            f(o); //這邊被namespace hiding 了，所以你global的f用不到，這時ADL會納入關聯namespace argument的function納入考量
            f(c); //這邊因為在當前namespace的scope以找到，ADL納入關聯的namespace argument的function，但cv qualifier優先，所以一邊查找的f1::f2::f()會被使用 
        }
    }
    void f(const c1::c2::cc & o){} //這邊就不用考慮了，因為在f1::f2::g()的時候，這個function未定義
}

int main(){
    f1::f2::g();
    return 0;
}
```