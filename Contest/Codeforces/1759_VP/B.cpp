#include <bits/stdc++.h>
constexpr int N = 55;
int t, m, s, b[N], sum;
bool vis[N];
void solve() {
  std::memset(vis, 0, sizeof(vis)), sum = 0;
  std::cin >> m >> s;
  for (int i = 1; i <= m; i++) std::cin >> b[i], vis[b[i]] = true;
  int max = *std::max_element(b + 1, b + m + 1);
  for (int i = 1; i <= max; i++) {
    if (!vis[i]) sum += i;
  }
  if (sum > s) return void(std::cout << "NO\n");
  if (sum == s) return void(std::cout << "YES\n");
  for (int i = max + 1; sum < s; i++) {
    sum += i;
    if (sum == s) return void(std::cout << "YES\n");
  }
  std::cout << "NO\n";
  return;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}