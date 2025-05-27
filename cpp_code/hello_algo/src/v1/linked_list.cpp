#include "fmt/base.h"
#include <fmt/core.h>
#include <fmt/format.h>
struct ListNode {
  int val;                                   // 节点值
  ListNode *next;                            // 指向下一节点的指针
  ListNode(int x) : val(x), next(nullptr) {} // 构造函数
};

// 插入节点 :在n0后插入p
void insert(ListNode *n0, ListNode *p) {
  ListNode *n1 = n0->next;
  p->next = n1;
  n0->next = p;
}

// 删除节点： 删除n0之后的首个节点
void remove(ListNode *n0) {
  if (n0->next == nullptr) {
    return;
  }

  ListNode *p = n0->next;
  ListNode *n1 = p->next;
  n0->next = n1;

  delete p;
}

// 访问节点
ListNode *access(ListNode *head, int index) {
  for (int i = 0; i < index; ++i) {
    if (head == nullptr)
      return nullptr;
    head = head->next;
  }

  return head;
}

// 查找节点
int find(ListNode *head, int target) {
  int index = 0;
  while (head != nullptr) {
    if (head->val == target) {
      return index;
    }
    head = head->next;
    index++;
  }

  return -1;
}

// 遍历节点
void traverse(ListNode *n0) {
  if (n0 == nullptr) {
    fmt::println("");
    return;
  }
  fmt::print("{}, ", n0->val);
  traverse(n0->next);
}

int main() {

  // 初始化
  // 初始化各个节点
  ListNode *n0 = new ListNode(1);
  ListNode *n1 = new ListNode(2);
  ListNode *n2 = new ListNode(3);
  ListNode *n3 = new ListNode(4);
  ListNode *n4 = new ListNode(5);

  // 构建节点之间的引用
  n0->next = n1;
  n1->next = n2;
  n2->next = n3;
  n3->next = n4;

  // test traverse
  traverse(n0);

  // test insert
  ListNode *p = new ListNode(9);
  insert(n0, p);
  fmt::print("insert res: ");
  traverse(n0);

  // test remove
  remove(n0);
  fmt::print("remove res: ");
  traverse(n0);

  // test find
  auto finder = find(n0, 4);
  fmt::println("find index: {}, value:{}", finder, access(n0, finder)->val);

  return 0;
}