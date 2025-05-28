#include <concepts>

template <typename T>
concept Addable = requires(T a, T b) {
  { a + b } -> std::convertible_to<T>;
};

// use 1
template <Addable T> T add(T a, T b) {
  auto c = a + b;
  return c;
}

// use 2
template <typename T>
  requires Addable<T>
auto add_ref(T a, T b) {
  auto c = a + b;
  return c;
}

int main() {
  add(3, 4);
  add_ref(3, 4); //, T &b)
  return 0;
}