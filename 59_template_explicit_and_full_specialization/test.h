//
// Created by finalfantasyliu on 2025/11/4.
//

#ifndef INC_59_TEMPLATE_EXPLICIT_AND_FULL_SPECIALIZATION_TEST_H
#define INC_59_TEMPLATE_EXPLICIT_AND_FULL_SPECIALIZATION_TEST_H
template<typename T>
void f(const T& t);

template<typename T>
struct X {
    int a{};
    void f();
};

//1st
template <class T>
class A {
protected:
    int a{};
};

template <class T>
class B : public A<T> {
public:
    void foo() {
        std::cout<<this->a<<std::endl;
    }
};

template <typename T>
class Foo {
public:
    void this_will_compile_right() {
    }
    /*
    void this_will_compile_error() {

    }
    */
    void fun() {
        std::cout << "Foo::fun" << std::endl;
    }
};





#endif //INC_59_TEMPLATE_EXPLICIT_AND_FULL_SPECIALIZATION_TEST_H