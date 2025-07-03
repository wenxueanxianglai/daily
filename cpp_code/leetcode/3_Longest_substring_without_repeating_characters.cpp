#include <algorithm>
#include <bitset>
#include <cstddef>
#include <gtest/gtest.h>
#include <iterator>
#include <unordered_map>
#include <vector>
using namespace std;

// Given a string s, find the length of the longest substring without duplicate
// characters.

// Example 1:
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3.

// Example 2:

// Input: s = "bbbbb"
// Output: 1
// Explanation: The answer is "b", with the length of 1.

// Example 3:
// Input: s = "pwwkew"
// Output: 3
// Explanation: The answer is "wke", with the length of 3.
// Notice that the answer must be a substring, "pwke" is a subsequence and not a
// substring.

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    if (s.empty())
      return 0;

    auto it1 = s.begin();
    auto it2 = it1 + 1;
    size_t max_len = 0;

    std::unordered_map<char, size_t> current_substring;
    current_substring[*it1] = 0;

    while (it2 != s.end() && it1 != s.end()) {
      if (current_substring.count((*it2)) == 0) {
        current_substring[*it2] = std::distance(s.begin(), it2);
        ++it2;
      } else {
        max_len = std::max(max_len, current_substring.size());
        current_substring.erase(*it1);
        ++it1;
      }
    }

    if (current_substring.size() > max_len) {
      return current_substring.size();
    }

    return max_len;
  }
};

TEST(lengthOfLongestSubstring, Case1) {
  string input{"abcabcbb"};
  int res{3};

  Solution soln;
  EXPECT_EQ(soln.lengthOfLongestSubstring(input), res);
}
TEST(lengthOfLongestSubstring, Case2) {
  string input{"bbbbb"};
  int res{1};

  Solution soln;
  EXPECT_EQ(soln.lengthOfLongestSubstring(input), res);
}
TEST(lengthOfLongestSubstring, Case3) {

  string input{"pwwkew"};
  int res{3};

  Solution soln;
  EXPECT_EQ(soln.lengthOfLongestSubstring(input), res);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
