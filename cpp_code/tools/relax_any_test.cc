#include "relax_any.hpp"
#include <cassert>
#include <iostream>

#include <string>
#include <string_view>

using namespace zxp::util;

#define RegistConvertType(A, B)                                                \
  if constexpr (std::is_convertible_v<A, B>)                                   \
    register_conversion<A, B>();

void test_basic_type_storage() {
  RelaxAny a = 123;
  assert(a.is<int>());
  assert(a.get<int>() == 123);
  assert(a.has_value());
  std::cout << "✔ test_basic_type_storage passed\n";
}

void test_copy_and_assignment() {
  RelaxAny a = 42;
  RelaxAny b = a;
  assert(b.is<int>());
  assert(b.get<int>() == 42);

  RelaxAny c;
  c = b;
  assert(c.is<int>());
  assert(c.get<int>() == 42);
  std::cout << "✔ test_copy_and_assignment passed\n";
}

void test_move_semantics() {
  RelaxAny a = 999;
  RelaxAny b = std::move(a);
  assert(b.is<int>());
  assert(b.get<int>() == 999);
  assert(!a.has_value()); // moved-from
  std::cout << "✔ test_move_semantics passed\n";
}

void test_conversion_between_types() {

  RelaxAny a = 100;
  assert(a.can_convert<double>());
  double d = a.convert<double>();
  assert(d == 100.0);

  RelaxAny f = float{3.14f};

  assert(f.can_convert<double>());
  auto fres = f.convert<double>();
  assert(fres - 3.14 < 0.00001);

  std::cout << "✔ test_conversion_between_types passed\n";
}
void test_invalid_conversion() {
  RelaxAny a = std::string("abc");

  try {
    [[maybe_unused]] int x = a.convert<int>();
    assert(false && "Conversion should have failed!");
  } catch (const std::bad_cast &) {
    std::cout << "✔ test_invalid_conversion passed\n";
  }
}

void test_custom_conversion() {
  struct Point {
    int x, y;
    explicit operator std::string() const {
      return "Point{" + std::to_string(x) + ", " + std::to_string(y) + '}';
    }
  };

  register_conversion<Point, std::string>();

  RelaxAny a = Point{1, 2};
  assert(a.can_convert<std::string>());
  std::string s = a.convert<std::string>();
  assert(!s.empty());

  std::cout
      << "✔ test_custom_conversion passed (manual verification of string)\n";
}

void test_reset_and_empty() {
  RelaxAny a = 42;
  assert(a.has_value());
  a.reset();
  assert(!a.has_value());

  try {
    [[maybe_unused]] int v = a.get<int>();
    assert(false && "Should throw on empty");
  } catch (const std::bad_cast &) {
    std::cout << "✔ test_reset_and_empty passed\n";
  }
}

void test_construct() {
  RelaxAny any;
  any.construct<std::string>("hello, relax");

  RelaxAny aa{std::string{}}; // <std::string> aa("sdft");
  if(aa.can_construct<std::string_view>()) {
    std::cout << "std::string can construct frome std::string_view\n";
  } else {
    std::cout << "std::string can not construct frome std::string_view\n";
  }
  
  RelaxAny view{std::string_view{}};
  if(aa.can_construct<std::string_view>()) {
    std::cout << "std::string_view can construct frome std::string\n";
  } else {
    std::cout << "std::string_view can not construct frome std::string\n";
  }

  aa.construct<std::string>("hello");
  std::cout << aa.get<std::string>() << std::endl;

  auto res = view.construct<std::string_view>("hello");
  auto rv = view.try_get<std::string_view>();
  std::cout << std::string{ rv->data(), rv->size() };


//  std::cout << "can_construct : " << res << std::endl;
}

int main() {
  test_basic_type_storage();
  test_copy_and_assignment();
  test_move_semantics();
  test_conversion_between_types();
  test_invalid_conversion();
  test_reset_and_empty();

  test_construct();

}