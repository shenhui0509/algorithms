#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::pair;

/*
 * the famous KMP string match algorithm. 
 * the essential of KMP is a FSM, the 'next' array represent the automation's state move
 * For e.g. if we want to search for a pattern "abcabcaa"
 * the FSM is like
 * 
 *     a      b      c      a      b      c      a      a
 *  o ---> o ---> o ---> o ---> o ---> o ---> o ---> o ---> success 
 *                       ^                    |
 *                       ---------------------
 * note that if we have already matches the second 'c', if the next character doesn't match, the "abc" before it has already
 * matched, and the prefix "abc" is not neccessary to scan again
 * so we just start match after the prefix "abc"
 * the "next" array defines the state transition.
 * the "next" for the example is 
 * [-1, 0, 0, 0, 1, 2, 3, 1]
 */
 
 
auto
  complie(const string &pattern)
  ->vector<int>
{
  auto slen = pattern.length();
  vector<int> result(slen, -1);
  size_t i = 0;
  int j = -1;
  while(i < slen){
    if(j == -1 || pattern[i] == pattern[j])
      result[++i] = ++j;
    else
      j = result[j];
  }
  return result;
}

size_t str_cnt(const string &text, const string &pattern)
{
  auto nex = complie(pattern);
  size_t i = 0, j = 0;
  auto slen = text.length();
  int ans = 0;
  while(i < slen){
    if(j == -1 || text[i] == pattern[j]){
      ++i;
      ++j;
    } else {
      j = nex[j];
    }

    if(j == pattern.length())
      ++ans;
  }
  return ans;
}

int main()
{
  vector<pair<string, string>> tests(5);
  tests[0] = std::make_pair("1234567", "123");
  tests[1] = std::make_pair("123412341234","234");
  tests[3] = std::make_pair("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaa");
  tests[4] = std::make_pair("uahqohhf1890r31hrohfo)","(28bjkbfkjq)");
  for(int i = 0; i < 5; ++i){
    std::cout << str_cnt(tests[i].first, tests[i].second) << std::endl;
  }
  return 0;

}
