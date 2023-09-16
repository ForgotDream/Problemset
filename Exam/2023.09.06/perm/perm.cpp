#include <iostream>

using i64 = long long;

constexpr int N = 2050, mod = 1e9 + 7;
int n, a[N], ans;
bool used[N];
void dfs(int u, int pos) {
  if (u == n) {
    ans++;
    return;
  }
  if (a[u]) {
    for (int i = pos + 1; i <= n; i++) {
      if (used[i]) continue;
      used[i] = true;
      dfs(u + 1, i);
      used[i] = false;
    }
  } else {
    for (int i = 1; i <= pos - 1; i++) {
      if (used[i]) continue;
      used[i] = true;
      dfs(u + 1, i);
      used[i] = false;
    }
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1; i < n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) used[i] = true, dfs(1, i), used[i] = false;
  std::cout << ans % mod << "\n";
}

int main() {
  std::freopen("perm.in", "r", stdin);
  std::freopen("perm.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}