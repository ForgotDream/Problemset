/**
 * @file    CF367B Sereja ans Anagrams.cpp
 * @author  ForgotDream
 * @brief   玄学
 * @date    2023-08-23
 */
#include <iostream>
#include <unordered_map>
#include <vector>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m, p;
int a[N], b[N];
std::unordered_map<int, int> q[N], chk;
int cnt[N];
void solve() {
  std::cin >> n >> m >> p;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= m; i++) std::cin >> b[i], chk[b[i]]++;
  int ans = 0;
  std::vector<int> vec;
  for (int i = 1; i <= p; i++) {
    int cur = i % p;
    for (int j = 0; j < m && i + j * p <= n; j++) {
      q[cur][a[i + j * p]]++, cnt[cur]++;
    }
    if (q[cur] == chk) vec.push_back(i), ans++;
  }
  for (int i = p + 1; i <= n - 1ll * (m - 1) * p; i++) {
    int cur = i % p;
    if (cnt[cur] == m) {
      q[cur][a[i - p]]--, cnt[cur]--;
      if (!q[cur][a[i - p]]) q[cur].erase(a[i - p]);
    }
    q[cur][a[i + (m - 1) * p]]++, cnt[cur]++;
    if (q[cur] == chk) vec.push_back(i), ans++;
  }
  std::cout << ans << "\n";
  for (auto i : vec) std::cout << i << " ";
  std::cout << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}