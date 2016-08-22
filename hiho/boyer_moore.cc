#include <string>
#include <array>
#include <iostream>
#include <algorithm>
#include <vector>

using std::array;
using std::string;
using std::cout;
using std::vector;

constexpr size_t ASCII_NUMS = 256;

auto 
compile_bad_char(const string& pattern)
  ->array<int, ASCII_NUMS>
{
  using bad_char_table = array<int, ASCII_NUMS>;
  auto len = pattern.length();
  bad_char_table bc;
  bc.fill(-1);
  int i = 0;
  for_each(pattern.begin(), pattern.end(),
          [&i, &bc](const char& c)
          {
            bc[static_cast<int>(c)] = i++; 
          });
  return bc;
}


auto suffix(const string &pattern)
  ->vector<int>
{
  auto len = pattern.length();
  vector<int> suffix_(len, 0);
  suffix_[len - 1] = len;

  int f = 0, i = 0, g = len - 1;
  for(i = len - 2; i >= 0; --i){
    if(i > g && suffix_[i + len - 1 - f] < i - g)
      suffix_[i] = suffix_[i + len - 1 - f];
    else{
      if(i < g)
        g = i;
      f = i;
      while(g >= 0 && pattern[g] == pattern[g + len - 1 -f])
        --g;
      suffix_[i] = f - g;
    }
  }
  return suffix_;
}

auto compile_good_suffix(const string &pattern)
  ->vector<int>
{
  auto suffix_ = suffix(pattern);
  auto len = pattern.size();
  vector<int> good_suffix(len, 0);
  int i = 0, j = 0;
  std::fill(good_suffix.begin(), good_suffix.end(), len);

  for(i = len - 1; i >= 0; --i){
    if(suffix_[i] == i + 1){
      for(; j < len - 1 - i; j++){
        if(good_suffix[j] == len)
          good_suffix[j] = len - 1 - i;
      }
    }
  }

  for(i = 0; i <= len - 2; ++i){
    good_suffix[len - 1 - suffix_[i]] = len - 1 - i;
  }
  return good_suffix;
}

size_t str_cnt(const string &text, const string &pattern)
{
  auto bad_char = compile_bad_char(pattern);
  auto good_suffix = compile_good_suffix(pattern);

  auto n = text.length(), m = pattern.length();
  size_t s = 0;
  size_t result = 0;
  while(s <= (n - m)){
    int j = m - 1;
    while(j >= 0 && pattern[j] == text[s + j])
      --j;
    if(j < 0){
      ++result;
      s += good_suffix[0];
    } else {
      s += std::max(good_suffix[j], j - bad_char[static_cast<int>(text[s+j])]);
    }
  }
  return result;
}

int main()
{
  cout << str_cnt("bbabcabcabcdabc", "abc") << "\n";
  cout << "\n";
}

