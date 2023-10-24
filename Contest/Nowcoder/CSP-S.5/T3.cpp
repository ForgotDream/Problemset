#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 21, M = 3000;
int n, m, a[N];
int b[N], f[N];
i64 ans;
void dfs(int idx) {
  if (idx == n + 1) return ans++, void();
  for (int i = 1; i <= m; i++) {
    b[idx] = i, f[idx] = 1;
    for (int j = 1; j < idx; j++) {
      if (b[j] >= b[idx]) continue;
      f[idx] = std::max(f[idx], f[j] + 1);
    }
    if (f[idx] == a[idx]) dfs(idx + 1);
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  dfs(1);
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
