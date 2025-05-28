#include <concepts>
#include <iostream>
#include <vector>

// 定义size的概念
template <typename T>
concept HasSize = requires(T a) {
    {a.size()} -> std::convertible_to<std::size_t>;
};


// use
template <HasSize T>
void printSize(const T& container) {
    std::cout << "size: " << container.size() << "\n";
}

int main() {
    std::vector<int> v = {1, 2, 3, 4};
    printSize(v);

    return 0;
}