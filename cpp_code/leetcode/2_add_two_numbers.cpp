
#include <gtest/gtest.h>
#include <vector>

using namespace std;
// You are given two non-empty linked lists representing two non-negative
// integers. The digits are stored in reverse order, and each of their nodes
// contains a single digit. Add the two numbers and return the sum as a linked
// list. You may assume the two numbers do not contain any leading zero, except
// the number 0 itself. Example 1: Input: l1 = [2,4,3], l2 = [5,6,4] Output:
// [7,0,8] Explanation: 342 + 465 = 807.

// Example 2:
// Input: l1 = [0], l2 = [0]
// Output: [0]

// Example 3:
// Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
// Output: [8,9,9,9,0,0,0,1]

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *res = new ListNode();
    ListNode *cur = res;
    ListNode *last = nullptr;

    int carry = 0;
    while (l1 || l2) {

      int tmp = -1;
      if (l1 && l2) {
        tmp = l1->val + l2->val + carry;
      } else if (l1) {
        tmp = l1->val + carry;
      } else if (l2) {
        tmp = l2->val + carry;
      } else {
        tmp = carry;
      }

      if (tmp > 9) {
        carry = 1;
        tmp -= 10;
      } else {
        carry = 0;
      }

      cur->val = tmp;

      ListNode *next = new ListNode(tmp);
      cur->next = next;
      last = cur;
      cur = cur->next;

      l1 ? l1 = l1->next : nullptr;
      l2 ? l2 = l2->next : nullptr;
    }

    if (carry == 1) {
      cur->val = 1;
    } else {
      delete cur;
      last->next = nullptr;
    }

    return res;
  }
};

TEST(AddTwoNumbers, Case1) {
  ListNode *l1 = new ListNode(2);
  l1->next = new ListNode(4);
  l1->next->next = new ListNode(3);

  ListNode *l2 = new ListNode(5);
  l2->next = new ListNode(6);
  l2->next->next = new ListNode(4);

  Solution sln;
  auto res = sln.addTwoNumbers(l1, l2);

  std::vector<int> vc;
  while (res != nullptr) {
    vc.push_back(res->val);
    res = res->next;
  }
  EXPECT_EQ(vc[0], 7);
  EXPECT_EQ(vc[1], 0);
  EXPECT_EQ(vc[2], 8);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
