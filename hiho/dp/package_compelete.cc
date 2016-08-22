/* distinguished from 01 package problem, 
 * the complete package problem allows to selecet for a object for more than once
 */
 
#include <iostream>
#include <vector>
#include <algorithm> //std::max

using namespace std;

int compelete_package(const vector<int> &need, const vector<int> &value, const int &max_cap)
{
  auto n = need.size();
  assert(n == value.size());
  vector<int> dp(max_cap + 1, 0);
  for(int i = 0; i < n; ++i){
    for(int j = need[i]; j <= max_cap; ++j){
      dp[j] = max(dp[j - need[i]] + value[i], dp[j]);
    }
  }
  return dp[max_cap];
}

int main()
{
  int m,n;
  cin >> n >> m;
  vector<int> need(n,0), value(n,0);
  for(int i = 0; i < n; ++i)
    cin >> need[i] >> value[i];
  cout << compelete_package(need, value, m) << endl;
}
