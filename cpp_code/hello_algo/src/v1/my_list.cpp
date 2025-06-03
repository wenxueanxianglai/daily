#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <stdexcept>
#include <vector>
#include <cassert>
#include <iostream>

class MyList {
public:
  MyList() { arr_ = new int[capacity_]; }

  ~MyList() { delete[] arr_; }

  int size() const { return size_; }
  int capacity() const { return capacity_; }

  int get(int index) {
    if (index < 0 || index >= size())
      throw std::out_of_range("索引越界");
    return arr_[index];
  }

  void set(int index, int num) {
    if (index < 0 || index >= size())
      throw std::out_of_range("索引越界");
    arr_[index] = num;
  }

  void insert(int index, int num) {
    if (index < 0 || index > size())
      throw std::out_of_range("索引越界");

    // 元素数量超出容量时，触发扩容机制
    if (size() == capacity()) {
      extendCapacity();
    }

    // 将索引 index 以及之后的元素都向后移动一位
    for (int j = size() - 1; j >= index; --j) {
      arr_[j + 1] = arr_[j];
    }

    arr_[index] = num;
    // 更新元素数量
    ++size_;
  }

  int remove(int index) {
    if (index < 0 || index >= size())
      throw std::out_of_range("索引越界");

    int num = arr_[index];

    // 将索引 index 之后的元素都向前移动一位
    for (int j = index; j < size() - 1; ++j) {
      arr_[j] = arr_[j + 1];
    }

    // 更新元素数量
    size_--;

    return num;
  }

  void extendCapacity() {
    int newCapacity = capacity() * extend_ratio_;
    int *tmp = arr_;
    arr_ = new int[newCapacity];

    for (int i = 0; i < size(); ++i) {
      arr_[i] = tmp[i];
    }

    delete[] tmp;
    capacity_ = newCapacity;
  }

  std::vector<int> toVector() {
    std::vector<int> vec(size());
    for (int i = 0; i < size(); ++i) {
      vec[i] = arr_[i];
    }
    return vec;
  }

private:
  int *arr_;
  int capacity_{10};
  int size_{0};
  int extend_ratio_{2};
};


void test_initial_state() {
    MyList list;
    assert(list.size() == 0);
    assert(list.capacity() == 10);
    std::cout << "test_initial_state passed.\n";
}

void test_insert_and_get() {
    MyList list;
    
    // Insert at beginning
    list.insert(0, 10);
    assert(list.get(0) == 10);
    assert(list.size() == 1);
    
    // Insert at end
    list.insert(1, 30);
    assert(list.get(1) == 30);
    
    // Insert in middle
    list.insert(1, 20);
    assert(list.get(0) == 10);
    assert(list.get(1) == 20);
    assert(list.get(2) == 30);
    assert(list.size() == 3);
    
    std::cout << "test_insert_and_get passed.\n";
}



void test_out_of_range() {
    MyList list;
    bool caught = false;
    
    // Test empty list
    try { list.get(0); } 
    catch (const std::out_of_range& e) { caught = true; }
    assert(caught);
    
    caught = false;
    try { list.set(0, 10); } 
    catch (const std::out_of_range& e) { caught = true; }
    assert(caught);
    
    caught = false;
    try { list.insert(1, 10); } 
    catch (const std::out_of_range& e) { caught = true; }
    assert(caught);
    
    // Test with 1 element
    list.insert(0, 10);
    caught = false;
    try { list.get(1); } 
    catch (const std::out_of_range& e) { caught = true; }
    assert(caught);
    
    std::cout << "test_out_of_range passed.\n";
}

int main() {
    test_initial_state();
    test_insert_and_get();
    test_out_of_range();
    
    return 0; 
}