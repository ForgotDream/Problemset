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

inline int idx(int x, int y) { return (x - 1) * m + y; }

std::vector<int> adj[M];
int dfn[M], low[M], clk, rt, cnt;
int bln[M];
std::stack<int> s;
void dfs(int u, int frm) {
  dfn[u] = low[u] = ++clk, s.push(u);
  for (auto v : adj[u]) {
    if (!dfn[v]) {
      dfs(v, u), low[u] = std::min(low[u], low[v]);
      if (low[v] >= dfn[u]) {
        cnt++;
        int p;
        do {
          p = s.top(), s.pop();
          bln[p]++;
        } while (p != v);
        bln[u]++;
      }
    } else if (v != frm) {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
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

  int bcnt = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!a[i][j] || dfn[idx(i, j)]) continue;
      bcnt++;
      rt = idx(i, j), dfs(idx(i, j), 0);
    }
  }

  // for (int i = 1; i <= n * m; i++) std::cerr << bln[i] << " \n"[i % n == 0];
  i64 sum = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!a[i][j]) continue;
      sum = (sum + bcnt + bln[idx(i, j)] - 1 + mod) % mod;
    }
  }
  std::cout << sum * get_inv(tmp) % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
