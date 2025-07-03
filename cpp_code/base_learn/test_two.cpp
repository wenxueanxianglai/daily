#include <iostream>

using namespace std;

int main() {

  int a = 10, b = 3;

  if (a < b) {
    cout << "0" << endl;
  }

  int i = 0;
  while (b << i < a && b << (i + 1) > a) {
    ++i;
  }

  int base = i > 0 ? 0x1 << i : 0;

  int cur = b << i;

  while (cur < a) {
    cur += b;
    base += 1;
  }

  cout << " a / b = " << base << endl;

  return 0;
}