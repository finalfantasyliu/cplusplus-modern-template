#include <iostream>
//最外層的()，是fold expression的語法一部分
//一元右折疊 (E operator ...)
// E: (std::cout<<args<<' ')
// operator: ,
// ... : ...
// 上面的fold expression展開後會變
//print("luse",1,1.2)

//void print(const char(&args0)[5], const int & args1, const double& args2){
// (std::cout<<args0<<' '),((std::cout<< args1 << ' '),(std::cout<<args2<<' '))}
template<typename ...Args>
void print( const Args &...args) {
    //這是老式的寫法，但沒有道理還要用array存
    //int _[]{(std::cout<<args<<" ",0)...};
    //新式寫法
    ((std::cout<<args<<" "), ...);
}
// 一元左折疊 (... operator E) 為 (((E1 operator E2) operator E3) operator EN)
/* void printLeftFold(const char(&args0)[5], const int & args1, const double& args2){
 * ((std::cout<<args0<<' '),((std::cout<< args1 << ' ')),(std::cout<<args2<<' '))
 * }
 */
template<typename ... Args>
void printLeftFold(const Args &...args) {
    (...,(std::cout<<args<<" "));
}

//下方就可以比較right fold跟left fold的效果
template<int ... I>
constexpr int v_right=(I - ...); //這是一元右折疊

template<int ...I>
constexpr int v_left=(... - I);  //這是一元左折疊

// 二元 left fold expression
//語法為
// I operator ... operator E => I 是預設值或初始expression
// I : std::cout
// operator : <<
// ... : ...
// operator : <<
// E: std::endl
template <typename ...Args>
void print(Args && ...args) {
    (std::cout<< ... << args)<< '\n';
}

template<int ...I>
constexpr int v_left_2=(I + ... +10);

template<int ...I>
constexpr int v_right_2=(10 + ... + I);

template<class ... Args>
auto Reverse(Args && ... args) {
    std::vector<std::common_type_t<Args...>>res{};
    bool tmp{false};
    (tmp = ... =(res.push_back(args),false));
    return res;
}
int main() {
    //如果operator是 ”，”，你left fold跟right fold的效果都是一樣的，因為逗號的讀取順序都是由左至右
    print("luse",1,1.2);
    std::cout<<std::endl;
    printLeftFold("luse",1,1.2);
    std::cout<<std::endl;
    //(4-(5-6))=5
    std::cout<<v_right<4,5,6> <<std::endl;
    //((4-5)-6)=-7
    std::cout<<v_left<4,5,6> <<std::endl;

    //左折疊先算左邊，右折疊先算右邊，二元就是先算初值
    // (1+(2+(3+(4+10))))
    std::cout<<v_right_2<1,2,3,4> <<std::endl;
    // ((((10+1)+2)+3)+4)
    std::cout<<v_left_2<1,2,3,4> <<std::endl;
    auto reverse_vec=Reverse(1,2.0,3,4);
    std::cout<<reverse_vec[0]<<std::endl;
    return 0;
}