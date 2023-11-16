#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 150;
int n, a[N], p[N], vis[N];
void solve() {
  memset(p, 0, sizeof(p));
  memset(vis, 0, sizeof(vis));
  std::cin >> n;
  int cnt = 0;
  for (int i = 1; i <= n; i++) std::cin >> a[i], p[a[i]]++;
  for (int i = 1; i <= 100; i++) cnt += p[i] >= 2;
  if (cnt < 2) return std::cout << -1 << "\n", void();
  int t = 1;
  for (int i = 1; i <= n; i++) {
    if (p[a[i]] < 2) std::cout << 1 << " ";
    else if (t >= 3) std::cout << 1 << " ";
    else if (!vis[a[i]]) std::cout << ++t << " ", vis[a[i]] = true;
    else std::cout << 1 << " ";
  }
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
