#include <iostream>
template<typename T>
concept C2= requires(T x)
{
    //{表達式}->return value
    //expression *x必須合法
    //類型T::inner必須存在
    //std::convertible_to可以合法，直接表示就是 *x可以implicit convert to T::inner
    //記得operator針對一元的* expression，只能是prefix，這種x*是不能用的
  {*x}->std::convertible_to<typename  T::inner> ;
    //x+1 expression必須合法
    //x+1 return值必須是回傳int
    {x+1}->std::same_as<int>;
    {x*1}->std::convertible_to<T>;
    //destructor 預設就是noexcept
    {x.~T()} noexcept;
    {x.f()} noexcept;

};

struct X {
    //~X()noexcept(false){}; 這樣就會是false
    //一般含function 預設就是會拋出exception
    void f() noexcept;
    int operator *() const {return 0;}
    int operator +(int)const {
        return 0;
    }
    X operator* (int )const {
        return *this;
    }
    using inner=int;
};



int main() {
    //所以這就相當等於int->int
    std::cout<<std::boolalpha<<C2<X><<std::endl;
    return 0;
}