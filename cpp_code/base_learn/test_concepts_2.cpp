#include <concepts>
#include <iostream>
#include <type_traits>

template <typename T>
concept IntegralOnly = std::integral<T>;

template <IntegralOnly T> T increment(T value) { return value + 1; }

int main() {

  std::cout << increment(5) << "\n";
  return 0;
}