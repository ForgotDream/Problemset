#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, k, a[N];
bool vis[N];
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 0; i < n; i++) vis[i] = false;
  int p = 0;
  for (int i = 1; i <= k; i++) {
    vis[p] = true;
    if (a[n - p] > n) return std::cout << "No\n", void();
    p = (p + a[n - p]) % n;
    if (vis[p]) break;
  }
  std::cout << "Yes\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
