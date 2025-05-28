#include <concepts>
#include <iostream>
#include <type_traits>

template <typename T>
concept NumberLike = std::is_arithmetic_v<T> && requires (T a){
    {a + a } -> std::same_as<T>;
    {a < a } -> std::convertible_to<bool>;
};


template <NumberLike T>
T addIfLess(T a , T b) {
    return (a < b) ? (a + b) : a;
}


int main() {
std::cout << addIfLess(1, 2) << '\n'; 
    return 0;
}