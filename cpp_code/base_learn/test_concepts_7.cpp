#include <concepts>
#include <ranges>
#include <iostream>
#include <vector>

template <typename T>
concept HasSize = requires(T a) {
    {a.size()} -> std::convertible_to<std::size_t>;
};

template <typename T>
concept RangeLike = std::ranges::range<T>;


template <typename T>
concept ContainerWithSize = RangeLike<T> && HasSize<T>;

template<ContainerWithSize T>
void dumpSizeAndContent(const T& c) {
    std::cout << "Size: " << c.size() << "\n";
    for (auto&& item : c) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> v{1, 2, 3};

    dumpSizeAndContent(v);

    return 0;
}