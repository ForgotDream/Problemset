#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 11, mod = 1e9 + 7;
int n, m;
bool a[N][N];
int f[1 << N][N], ans[N];
std::vector<pii> s[1 << N];
void solve() {
  std::cin >> n >> m;
  int mask = (1 << n) - 1;
  for (int i = 0; i <= mask; i++) s[i].clear();
  for (int i = 1; i <= m; i++) {
    char opt;
    int u, v;
    std::cin >> opt >> u >> v;
    if (u > v) std::swap(u, v);
    if (opt == '+') {
      for (int i = 0; i <= mask; i++) {
        if ((i & (1 << (u - 1))) || (i & (1 << (v - 1)))) continue;
        s[i].emplace_back(u, v);
      }
    } else {
      for (int i = 0; i <= mask; i++) {
        if ((i & (1 << (u - 1))) || (i & (1 << (v - 1)))) continue;
        s[i].erase(std::find(s[i].begin(), s[i].end(), pii(u, v)));
      }
    }
    std::memset(f, 0, sizeof(f)), f[0][0] = 1;
    for (int i = 0; i <= mask; i++) {
      for (int l = 0; l <= n; l++) {
        for (auto [j, k] : s[i]) {
          if (j <= l) continue;
          int p = i | (1 << (j - 1)) | (1 << (k - 1));
          f[p][j] = (f[p][j] + f[i][l]) % mod;
        }
      }
    }
    std::memset(ans, 0, sizeof(ans));
    for (int i = 0; i <= mask; i++) {
      for (int j = 1; j <= n; j++) {
        (ans[__builtin_popcount(i) / 2] += f[i][j]) %= mod;
      }
    }
    for (int i = 1; i <= n / 2; i++) std::cout << ans[i] << " \n"[i == n / 2];
  }
}

int main() {
  std::freopen("sport.in", "r", stdin);
  std::freopen("sport.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
