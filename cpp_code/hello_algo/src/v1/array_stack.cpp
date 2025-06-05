#include <iostream>
#include <stdexcept>
#include <vector>

#include <gtest/gtest.h>

class ArrayStack {
public:
  int size() { return stack.size(); }

  bool empty() { return stack.size() == 0; }

  void push(int num) { stack.push_back(num); }

  int pop() {
    int num = top();

    stack.pop_back();
    return num;
  }

  int top() {
    if (empty()) {
      throw std::out_of_range("栈为空");
    }

    return stack.back();
  }

  std::vector<int> to_vector() { return stack; }

private:
  std::vector<int> stack;
};

class ArrayStackTest : public ::testing::Test {
  protected:
  ArrayStack stack;
};

// Test empty stack behavior
TEST_F(ArrayStackTest, EmptyStack) {
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    EXPECT_THROW(stack.top(), std::out_of_range);
    EXPECT_THROW(stack.pop(), std::out_of_range);
}


// Test push and top operations
TEST_F(ArrayStackTest, PushAndTop) {
    stack.push(10);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 10);

    stack.push(20);
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 20);
}

// Test pop operation
TEST_F(ArrayStackTest, Pop) {
    stack.push(30);
    stack.push(40);

    EXPECT_EQ(stack.pop(), 40);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 30);

    EXPECT_EQ(stack.pop(), 30);
    EXPECT_TRUE(stack.empty());
}

// Test to_vector conversion
TEST_F(ArrayStackTest, ToVector) {
    stack.push(50);
    stack.push(60);
    stack.push(70);

    std::vector<int> expected = {50, 60, 70};
    EXPECT_EQ(stack.to_vector(), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}