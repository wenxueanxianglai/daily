#include <concepts>
#include <iostream>


// #include <type_traits>

// template <typename T>
// typename std::enable_if<std::is_integral_v<T>, T>::type increment(T value) {
//   return value + 1;
// }

template <std::integral T>
T increment(T value) {
    return value + 1;
}

int main() {
  std::cout << increment(5) << "\n";
  return 0;
}