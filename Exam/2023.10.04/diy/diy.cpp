#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e4 + 50;
std::vector<pii> pfac[N];
std::vector<int> fac[N];
int n;
i64 ans[N];
std::bitset<N> b[N];
void dfs(int u, int idx, int cur) {
  if (idx == pfac[u].size()) {
    fac[u].push_back(cur), b[u].set(cur);
    return;
  }
  auto [p, l] = pfac[u][idx];
  i64 tmp = 1;
  for (int i = 0; i <= l; i++) dfs(u, idx + 1, cur * tmp), tmp *= p;
}
void init() {
  std::memset(ans, -1, sizeof(ans));
  for (int i = 1; i <= 1e4; i++) {
    int cpy = i;
    for (int j = 2; j * j <= cpy; j++) {
      if (cpy % j == 0) {
        pfac[i].emplace_back(j, 0);
        while (cpy % j == 0) pfac[i].back().second++, cpy /= j;
      }
    }
    if (cpy != 1) pfac[i].emplace_back(cpy, 1);
    dfs(i, 0, 1);
    std::sort(fac[i].begin(), fac[i].end());
    for (auto j : fac[i]) {
      for (auto k : fac[i]) {
        if (j + k >= i || k > j || !b[i][i - j - k]) continue;
        ans[i] = std::max(ans[i], 1ll * j * k * (i - j - k));
      }
    }
  }
}
void solve() {
  std::cin >> n;
  std::cout << ans[n] << "\n";
}

int main() {
  std::freopen("diy.in", "r", stdin);
  std::freopen("diy.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  init();
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
