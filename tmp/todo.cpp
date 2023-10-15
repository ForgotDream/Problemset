/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-10-15
 */
#include <iostream>
#include <numeric>
#include <queue>

using i64 = long long;

constexpr int N = 2e6 + 50, mod = 1e9 + 7;
int n, a[N], b[N], bln[N];
struct DSU {
  int fa[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
} dsu;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i] >> b[i], bln[a[i]] = bln[b[i]] = i;
  }
  for (int i = 1; i <= 2 * n; i++) nxt[i] = i;
  for (int i = 1; i <= 2 * n; i++) {
    int u = bln[i];
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
