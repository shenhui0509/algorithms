#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //for std::min
#include <utility> // for tuple

using std::string;
using std::cout;
using std::vector;
using std::min;

/*
 * Manacher algorithms for longest palindarome substring
 * imagine a string is "abcdedcbaeabcdedcba"
 * i : 1  2  3  4  5  6  7  8  9  10 
 * s : a  b  a  c  d  c  a  b  a  a
 * p : 1  3  1  1  9  1  1  ?
 * m : *  *  *        *  *  *
 * i is the index in the string start from 1,
 * p is the longest palindarome substring's length that center at i
 * now we want to determine the value of p[8]
 * current longest palindarome is centered at 5, and its right bound is at 9
 * 8 is less than the current right bound
 * what is p[8]'s minimum value ?
 * 1. R - 8 > p[2](mirror) , that we have to search from the right bound, so the p[8] = R - 8;
 * 2. R - 8 < p[2](mirror) , that the string center at 8 with length p[2] is also palindarome otherwise the longest palindarome center at C fails
 * so we have p[i] = min(R - i, p[2 * c -i]);
 * and we can search from s[i + p[i] + 1]...s[i]... s[i - p[i] - 1]  for p[i] rather than from s[i+1] s[i] s[i-1]
 *
 * however if i >= R, no information can be obtained from the previous search, we have to start search at s[i+1] s[i] s[i-1] 
 * 
 * noting that this algorithm is only suit for odd length string, so we have to add a preprocess to uniform the length of the string
 * 12345 => $#1#2#3#4#5#^
 */
static string pre_process(const string &s)
{
  string result(2 * s.size() + 3, '#');
  result.front() = '^';
  result.back() = '$';
  using size_type = string::size_type;
  size_type i = 2;
  for(; i < result.size() - 1; i += 2){
    result[i] = s[(i >> 1) - 1];
  }
  return result;
}

string LongestPalindaromeSubstr(const std::string &s)
{
  auto t = pre_process(s);
  vector<int> P(t.size(), 0);
  int C = 0, R = 0;
  for(int i = 1; i < t.size() - 1; ++i){
    int i_mirror = 2 * C - i;
    P[i] = (R > i) ? min(P[i_mirror], R - i) : 0;
    while(t[i+1+P[i]] == t[i-1-P[i]])
      ++P[i];
    if(P[i] > R - C){
      C = i;
      R = C + P[i];
    }
  }
  auto max_len = R - C;
  return s.substr((C-max_len -1) >> 1, max_len);
}

int main(int argc, char *argv[])
{
  string s = "1234543";
  string s1 = "i01123456543210fafhfuehwfihw";
  cout << pre_process(s) << "\n";
  cout << pre_process(s1) << "\n";
  auto l1 = LongestPalindaromeSubstr(s), l2 = LongestPalindaromeSubstr(s1);
  cout << l1 << "\n";
  cout << l2 << "\n";
  return 0;
}
