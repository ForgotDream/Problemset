#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1050, M = N * N, mod = 998244353;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

inline i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
inline i64 get_inv(i64 u) { return fast_pow(u, mod - 2, mod); }

int n, m, a[N][N];
int bln[N][N], cnt;

inline int idx(int x, int y) { return (x - 1) * m + y; }

std::vector<int> adj[N];
int dfn[N], low[N], clk, rt;
std::vector<int> cut;
voi dfs(int u, int frm) {
  dfn[u] = low[u] = ++clk;
  int ch = 0;
  for (auto v : adj[u]) {
    if (!dfn[v]) {
      dfs(v, u), low[u] = std::min(low[u], low[v]), ch++;
      if (low[v] >= dfn[u] && u != rt) b.push_back(u);
    } else if (v != frm) {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (u == rt && ch >= 2) b.push_back(u);
}

void solve() {
  std::cin >> n >> m;
  int tmp = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c;
      std::cin >> c;
      a[i][j] = (c == '#'), tmp += (c == '#');
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!a[i][j]) continue;
      for (auto [_x, _y] : d) {
        int dx = i + _x, dy = j + _y;
        if (!a[dx][dy]) continue;
        adj[idx(i, j)].emplace_back(idx(dx, dy));
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!a[i][j] || dfn[idx(i, j)]) continue;
      rt = idx(i, j), dfs(idx(i, j), 0);
    }
  }

  std::cerr << b.size() << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
