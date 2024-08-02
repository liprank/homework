#include <iostream>

// 基础情况：当没有参数时，返回0
template<typename T>
T sum() {
    return 0;
}

// 递归情况：计算所有参数的和
template<typename T, typename... Args>
T sum(T first, Args... rest) {
    return first + sum<Args...>(rest...);
}

int main() {
    // 测试整数加法
    std::cout << "Sum of integers: " << sum(1, 2, 3, 4, 5) << std::endl;

    // 测试浮点数加法
    std::cout << "Sum of floats: " << sum(1.5f, 2.5f, 3.5f) << std::endl;

    // 测试混合类型加法
    std::cout << "Sum of mixed types: " << sum(1, 2.5f, 3) << std::endl;

    return 0;
}
