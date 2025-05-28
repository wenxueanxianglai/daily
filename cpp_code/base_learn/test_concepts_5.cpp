#include <concepts>
#include <iostream>

template <typename T>
concept SupportLessThan = requires(T a, T b) {
    {a < b} -> std::convertible_to<bool>;
};

template <SupportLessThan T>
void printMin(const T& a, const T& b){
    if (a < b){
        std::cout << "min: "<< a << "\n";
    } else {
        std::cout << "min: "<< b << "\n";
    }
}

int main() {
    printMin(5, 7);
    return 0;
}