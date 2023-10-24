/**
 * @file    CF633D Fibonacci-ish.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-31
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using i64 = long long;

constexpr int N = 1050;
int n, a[N];
std::map<int, int> mp;
std::vector<int> b;
bool vis[N][N];
int find(int val) {
  return std::lower_bound(b.begin(), b.end(), val) - b.begin();
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], b.push_back(a[i]), mp[a[i]]++;
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  int ans = 0;
  if (mp.count(0)) ans = mp[0];
  for (auto i : b) {
    for (auto j : b) {
      if (i == 0 && j == 0) continue;
      if (i == j && mp[j] == 1) continue;
      if (vis[find(i)][find(j)]) continue;
      std::map<int, int> cnt;
      int x = i, y = j, z = i + j, cur = 2;
      cnt[x]++, cnt[y]++, cnt[z]++;
      while (mp.count(z) && cnt[z] <= mp[z]) {
        x = y, y = z, z = x + y;
        cnt[z]++, cur++;
      }
      vis[find(x)][find(y)] = true;
      ans = std::max(ans, cur);
    }
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}