#include <iostream>
#include <vector>
#include <algorithm> //for std::max
using namespace std;

int pack_01(const vector<int> &need, const vector<int> &value, const int &max_cap)
{
  vector<int> dp(max_cap + 1, 0);
  auto n = need.size();
  assert(n == value.size());
  for(int i = 0; i < n; ++i)
    for(int j = max_cap; j >= need[i]; --j)
      dp[j] = max(dp[j - need[i]] + value[i], dp[j]);
  return dp[max_cap];
}

int main()
{
  int n,m;
  cin >> n >> m;
  vector<int> need(n,0), value(n,0);
  for(int i = 0; i < n; ++i)
    cin >> need[i] >> value[i];
  cout << pack01(need, value, m);
  return 0;
}
