#include <iostream>
#include <stdexcept>
struct ListNode {
  int val;                                   // 节点值
  ListNode *next;                            // 指向下一节点的指针
  ListNode(int x) : val(x), next(nullptr) {} // 构造函数
};

void freeMemoryLinkedList(ListNode *head) {
  auto *current = head;

  while (current != nullptr) {
    auto *tmp = current->next;
    delete current;
    current = tmp;
  }
}

class LinkedListStack {

public:
  LinkedListStack() : size_(0), stack_top_(nullptr) {}

  ~LinkedListStack() {
    // 遍历链表删除节点，释放内存
    freeMemoryLinkedList(stack_top_);
  }

  int size() { return size_; }

  bool empty() { return size() == 0; }

  void push(int num) {
    ListNode *node = new ListNode(num);
    node->next = stack_top_;
    stack_top_ = node;
    size_++;
  }

  int pop() {
    int num = top();
    ListNode *tmp = stack_top_;
    stack_top_ = stack_top_->next;

    // 释放内存；
    delete tmp;
    size_--;

    return num;
  }
  int top() {
    if (empty()) {
      throw std::out_of_range("栈为空");
    }

    return stack_top_->val;
  }

private:
  ListNode *stack_top_;
  int size_;
};

int main() {

     LinkedListStack stack;
    
    // Test empty stack
    std::cout << "Testing empty stack:\n";
    std::cout << "Size: " << stack.size() << " (expected: 0)\n";
    std::cout << "Is empty: " << std::boolalpha << stack.empty() << " (expected: true)\n";
    
    // Test pushing elements
    std::cout << "\nPushing 10, 20, 30...\n";
    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    std::cout << "Top: " << stack.top() << " (expected: 30)\n";
    std::cout << "Size: " << stack.size() << " (expected: 3)\n";
    
    // Test popping
    std::cout << "\nPopping...\n";
    std::cout << "Popped: " << stack.pop() << " (expected: 30)\n";
    std::cout << "New top: " << stack.top() << " (expected: 20)\n";
    std::cout << "Size: " << stack.size() << " (expected: 2)\n";
    
    // Test popping all elements
    stack.pop();
    stack.pop();
    std::cout << "\nAfter popping all, size: " << stack.size() << " (expected: 0)\n";
    
    // Test exception handling
    std::cout << "\nTesting exceptions:\n";
    try {
        stack.top();
        std::cerr << "Error: top() should throw exception!\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Caught top() exception: " << e.what() << " (expected)\n";
    }
    
    try {
        stack.pop();
        std::cerr << "Error: pop() should throw exception!\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Caught pop() exception: " << e.what() << " (expected)\n";
    }

    return 0; 
}