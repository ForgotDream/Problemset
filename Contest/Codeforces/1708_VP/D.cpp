#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50;
int t, n, a[N];
void solve() {
  std::cin >> n;
  std::map<int, int> mp;
  for (int i = 1; i <= n; i++) std::cin >> a[i], mp[a[i]]++;
  while (true) {
    if (mp.size() == 1 && mp.begin()->second == 1) break;
    std::map<int, int> cur;
    for (auto it = mp.begin(); it != mp.end(); it++) {
      auto nxt = std::next(it);
      auto [num, cnt] = *it;
      if (cnt - 1 || cur.count(0)) cur[0] += cnt - 1;
      if (nxt != mp.end()) cur[nxt->first - num]++;
    }
    mp = cur;
  }
  std::cout << mp.begin()->first << "\n";
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}