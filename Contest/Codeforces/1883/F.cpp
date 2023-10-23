#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, a[N], lst[N];
std::vector<int> b;
bool vis[N];
int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n + 5; i++) lst[i] = vis[i] = false;
  b.clear();
  for (int i = 1; i <= n; i++) std::cin >> a[i], b.push_back(a[i]);
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  for (int i = 1; i <= n; i++) a[i] = find(a[i]);
  for (int i = n; i >= 1; i--) {
    lst[i] = !vis[a[i]], vis[a[i]] = true;
    lst[i] += lst[i + 1];
  }
  for (int i = 1; i <= n + 5; i++) vis[i] = false;
  i64 ans = 0;
  for (int i = 1; i <= n; i++) ans += (!vis[a[i]]) * lst[i], vis[a[i]] = true;
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
