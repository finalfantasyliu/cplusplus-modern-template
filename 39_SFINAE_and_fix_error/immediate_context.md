# Immediate Context（立即语境）

在 C++ 模板元编程中，**SFINAE**（Substitution Failure Is Not An Error）机制的行为依赖于 **立即语境（immediate context）** 的精确定义。只有在此语境中发生的替换失败，才会被视为“软错误”（SFINAE）：候选会被移除，但编译不会失败；而在此之外的错误通常是**硬错误（hard error）**，会导致编译失败。

---

## 标准定义与权威说明

- **cppreference / C++ 标准**
  > “Only the failures in the *types* and *expressions* in the *immediate context* of the function type or its template parameter types ... are SFINAE errors. If the evaluation of a substituted type/expression causes a *side-effect* ... errors in those side-effects are treated as hard errors.”  
  [oai_citation:0‡Stack Overflow](https://stackoverflow.com/questions/15260685/what-exactly-is-the-immediate-context-mentioned-in-the-c11-standard-for-whic?utm_source=chatgpt.com) [oai_citation:1‡CPP參考](https://en.cppreference.com/w/cpp/language/sfinae.html?utm_source=chatgpt.com)

- **Stack Overflow（Jonathan Wakely 的解释）**
  > “If you consider all the templates and implicitly-defined functions that are needed to determine the result of the template argument substitution … any errors occurring in that first step are not in the immediate context, and result in hard errors. … If all those instantiations … can be done without error, then any further errors that occur during substitution … are not errors, but result in deduction failures.”  
  [oai_citation:2‡Stack Overflow](https://stackoverflow.com/questions/15260685/what-exactly-is-the-immediate-context-mentioned-in-the-c11-standard-for-whic?utm_source=chatgpt.com)

- **C++ Stories 及 Medium 说明**
  > “SFINAE only applies to substitution failures in the immediate context of the template’s signature. Errors inside the function body or in a nested template instantiation are typically hard errors that halt compilation.”  
  [oai_citation:3‡C++ Stories](https://www.cppstories.com/2022/sfinea-immediate-context/?utm_source=chatgpt.com) [oai_citation:4‡Medium](https://medium.com/%40sachinklocham/sfinae-in-c-compile-time-function-selection-made-simple-6f73b8043250?utm_source=chatgpt.com)

---

## 示例对比

```cpp
// A. 在签名处使用（立即语境）：SFINAE 适用
template<typename T,
         typename = decltype(std::declval<T&>() += 1)>
void add_one(T&) { /* ... */ }

// B. 函数体内使用（非立即语境）：可能硬错误
template<typename T>
void add_one_body(T& v) {
    v += 1;  // 如果 T 不支持 +=，这里会成为硬错误
}
```
-	add_one<int>：合法，decltype(int& += 1) 成功 → 被选中（SFINAE）。
-	add_one<std::string>：std::string& += 1 不合法，但发生在立即语境内 → SFINAE：候选被移出，不报错。
-	add_one_body<std::string>：失败发生在函数体内 → 硬错误，编译失败。


## 补充说明
-	Immediate Context 包含哪些？
-	函数模板签名部分，包括返回类型、参数类型、默认模板参数
-	C++20 起也包括 explicit 说明符中的类型与表达式
￼ ￼ ￼ ￼ ￼
-	什么不是 Immediate Context？
  - 函数体内部的表达式
  -	隐式模板实例化或成员函数的生成
  -	其他副作用性过程
以上情况发生错误时，会产生硬错误。

       | 出错发生位置                 | 是否属于 Immediate Context？ | 错误类型                       |
       | ---------------------- | ----------------------- | -------------------------- |
       | 函数签名 / 模板参数 / 返回类型     | 是                       | **SFINAE**（软错误）：候选移除，无编译失败 |
       | 函数体内 / 隐式实例化 / 其他副作用场景 | 否                       | **硬错误**：ill‑formed，编译失败    |


---

## 总结

“Immediate Context” 是 SFINAE 的核心概念，用来区分：
-	在模板签名里的替换失败 → 软错误（SFINAE）
-	在模板签名外的错误 → 硬错误（编译失败）