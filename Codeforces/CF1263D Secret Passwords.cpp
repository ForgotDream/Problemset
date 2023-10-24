/**
 * @file    CF1263D Secret Passwords.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-08-29
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using i64 = long long;

namespace DSU {
constexpr int N = 26;
struct Dsu {
  int fa[N];
  Dsu() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
} dsu;
}
constexpr int SIG = 26;
int n;
std::string s;
bool exist[SIG];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> s;
    int d = s[0] - 'a';
    exist[d] = true;
    for (int j = 1; j < s.length(); j++) {
      DSU::dsu.merge(s[j] - 'a', d);
    }
  }
  int ans = 0;
  for (int i = 0; i < 26; i++) {
    if (DSU::dsu.fa[i] == i && exist[i]) ans++;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}