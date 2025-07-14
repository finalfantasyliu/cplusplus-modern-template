#include <iostream>
#include "test_class_template.h"
//class 的完整定義不包含member的完整定義

int main() {
    X2<int> x;
    x.f();//這邊沒有instantiate，所以找不倒是正常的
    x.f2();
    return 0;
}