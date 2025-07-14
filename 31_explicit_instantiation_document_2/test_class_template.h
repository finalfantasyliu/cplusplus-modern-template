// test_class_template.h
#ifndef TEST_CLASS_TEMPLATE_H
#define TEST_CLASS_TEMPLATE_H

template<typename T>
struct X2 {
    void f();
    void f2();
};

// Tell other TUs that the definition will be provided elsewhere

#endif