/* Levenshtein distance is the edit distance between two strings.
 * the allowd action on string is :
 * (1) replace ; (2) insert ; (3) delete
 * str1 : GUMBO
 * str2 : GAMBOL
 * Levenshtein(str1, str2) = 2 (replace 'U' by 'A', add 'L' on str1)
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::string;
using std::vector;
using std::min;

size_t levenshtein(const string &str1, const string &str2)
{
  auto n = str1.size(), m = str2.size();
  if(n == 0)
    return m;
  if(m == 0)
    return n;
 
  vector<size_t> v0(n+1, 0), v1(n+1, 0);
  size_t i = 0;
  std::generate(v0.begin(), v0.end(),[&i](){return i++;});
  v[1] = 1;

  for(i = 1; i <= m; ++i){
    for(size_t j = 1; j <= n; ++j){
      int cost = (str2[i - 1] == str1[j - 1] ? 0 : 1);
      v1[j] = min(v0[j-1] + cost, min(v1[j-1] + 1, v0[j] + 1));
    }
    v0 = v1;
  }
  return v1[n];
}

int main()
{
  std::cout << levenshtein("GAMBOL", "GUMBO") << std::endl;
}
