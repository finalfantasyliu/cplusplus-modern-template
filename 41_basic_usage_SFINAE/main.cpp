#include <iostream>

/* 若要確保T有overloading operator +可以使用下面這種作法，但不是很雅觀
 *1. template<typename T,typename T2=decltype(T{}+T{})>
 *    auto add(const T& t1, const T&t2){
 *    return t1+t2;}
 * 但有人會覺得若不要寫不是也可以讓他編譯錯誤而得知沒有operator +，但這邊可以發現編譯的錯誤是嘗試實體化錯誤，而不是match不上的邏輯，
 * in instantiation of function template specialization 'add<X>' requested here
 * 而要使用的原因乃編譯器實體化一個template function 是需要開銷的(編譯多個檔案的時候，花費時間更久)，並且當編譯器實體化時，若你模版很複雜，你很難了解錯誤訊息是啥
 * keyword：避免function overloading、編譯實體化耗時與報錯
 */
template<typename T>
auto add (const T& t1, const T&t2)->decltype(t1+t2){
    std::puts("SFINAE +");
    return t1+t2;
}
struct X{};
int main() {
    add(1,2);
    //add(X{},X{}); //Substitution failed: expression t1 + t2 is ill-formed
    return 0;
}