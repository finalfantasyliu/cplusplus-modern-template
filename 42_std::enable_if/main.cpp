#include <iostream>
#include <type_traits>
/*這邊is_same_v會回傳boolean值，而std::enable_if_t來自於
* template <bool _Bp, class _Tp = void>
* using enable_if_t = typename enable_if<_Bp, _Tp>::type;
*
* template <bool, class _Tp = void>
* struct _LIBCPP_TEMPLATE_VIS enable_if {};
* template <class _Tp>
* struct _LIBCPP_TEMPLATE_VIS enable_if<true, _Tp> {
*  typedef _Tp type;
* };
* 所以只有true才會落到enable_if<true, _Tp>，而class _TP有給default value為void，若是false就是
* enable_if<false,void>沒有這個特化，算是SFINAE
*/
template<typename T, typename SFINAE=std::enable_if_t<std::is_same_v<T, int> > > //如何要求他的type為何
void f(T) {
}
/* 這是一元右折疊E operator ...
 * template<class Type, class ...Args>
 *  array(Types, Args...)->array<std::enable_if_t(std::is_same_v<Type,Args>&& ...),Type>, sizeof...(Args)+1>;
 */


int main() {
    f(1);
    //f(1u);
    return 0;
}
