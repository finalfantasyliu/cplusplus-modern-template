#include <iostream>
/*
| 名詞                  | 是什麼                                       |           產出/型別 | 寫在什麼地方                                                | 作用 / 說明                                                                        |
| ------------------- | ----------------------------------------- | --------------: | ----------------------------------------------------- | ------------------------------------------------------------------------------ |
| constraint          | 對模板適用性的**布林條件**（總稱）                       |          `bool` | 不是一個獨立語法元件；由 requires-expression、概念名、或常量布林表達式**組成**   | 用來判定「關聯約束是否滿足」，影響能否選上/實例化。([eel.is][1])                                        |
| concept             | **命名**一個 constraint 的宣告                   | `bool`（概念名可當謂詞） | `template<…> concept Name = <constraint-expression>;` | 可在型別位 `template<Name T>` 或在 requires-clause/其他條件中使用。([en.cppreference.com][2]) |
| requires-expression | 以 `requires (…) { … }` 記述「需求序列」           | `bool`（prvalue） | 表達式出現處（概念定義裡最常見）                                      | 用 **簡單/型別/複合/巢狀**需求檢查語法/語意是否成立；可引入**區域參數**，不具鏈結/生命期。([en.cppreference.com][3]) |
| requires-clause     | 在宣告上加的 `requires <constraint-expression>` |               — | 模板參數列之後或函式宣告尾端                                        | 指定此宣告的**關聯約束**；是**簽名的一部分**但**不是型別**；重載決議需先滿足約束。([mooshak.dcc.fc.up.pt][4])     |

[1]: https://eel.is/c%2B%2Bdraft/temp?utm_source=chatgpt.com "[temp]"
[2]: https://en.cppreference.com/w/cpp/language/constraints.html?utm_source=chatgpt.com "Constraints and concepts (since C++20)"
[3]: https://en.cppreference.com/w/cpp/language/requires.html?utm_source=chatgpt.com "requires expression (since C++20)"
[4]: https://mooshak.dcc.fc.up.pt/~oni-judge/doc/cppreference/reference/en/cpp/language/constraints.html?utm_source=chatgpt.com "Constraints and concepts (since C++20) - cppreference.com"
*/
/*
 1) concept：給一個 constraint 取名字
template<class T>
concept Addable = requires(T x) { x + x; };   // ← requires-expression 產生 bool 條件

// 2) requires-clause：把「約束」掛在宣告上
template<class T>
T add(T a, T b) requires Addable<T> {         // ← requires-clause（關聯約束）
    return a + b;
}

// 3) 約束也可以不用概念名，直接寫布林條件
template<class T> 這種常量的沒有{}的算一個require claude
T twice(T x) requires (sizeof(T) > 1) {       // ← constraint 可是任意常量布林表達式
    return x + x;
}
可以连用 requires requires 的情况，都是因为第一个 requires 期待一个可以编译期产生 bool 值的表达式；而 requires 表达式就是产生描述约束的 bool 类型的纯右值表达式。
 */
int main() {
    return 0;
}