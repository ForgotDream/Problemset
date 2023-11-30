/**
 * @file    P1360 [USACO07MAR] Gold Balanced Lineup G.cpp
 * @author  ForgotDream
 * @brief   Hash?
 * @date    2023-11-27
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e5 + 50;
int n, m, a[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::map<std::vector<int>, int> mp;
  std::vector<int> cur(m);
  mp[cur] = 0;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++) cur[j] += !!(a[i] & (1 << j));
    if (a[i] & 1) for (int j = 0; j < m; j++) cur[j]--;
    if (mp.find(cur) != mp.end()) ans = std::max(ans, i - mp[cur]);
    else mp[cur] = i;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
