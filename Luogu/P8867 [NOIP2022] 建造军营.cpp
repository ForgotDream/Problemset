/**
 * @file    P8867 [NOIP2022] 建造军营.cpp
 * @author  ForgotDream
 * @brief   DP + BCC / DCC
 * @date    2023-11-15
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;

constexpr int N = 5e5 + 50, mod = 1e9 + 7;
int n, m;
std::vector<pii> adj[N];
int dfn[N], low[N], clk;
std::stack<int, std::vector<int>> st;
bool ins[N];
int tot, bln[N], vcnt[N];
void tarjan(int u, int frm) {
  dfn[u] = low[u] = ++clk;
  st.push(u), ins[u] = true;
  for (auto [v, idx] : adj[u]) {
    if (!dfn[v]) {
      tarjan(v, idx), low[u] = std::min(low[u], low[v]);
    } else if (idx != frm) {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    int p;
    ++tot;
    do {
      p = st.top(), st.pop(), ins[p] = false;
      bln[p] = tot, vcnt[tot]++;
    } while (p != u);
  }
}

std::vector<int> g[N];
i64 f[N][2], ecnt[N], ans, s[N];
inline i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void dfs(int u, int frm) {
  f[u][0] = fastPow(2, ecnt[u], mod);
  f[u][1] = fastPow(2, ecnt[u], mod) * (fastPow(2, vcnt[u], mod) - 1) % mod;
  s[u] = ecnt[u];
  for (auto v : g[u]) {
    if (v == frm) continue;
    dfs(v, u), s[u] += s[v] + 1;
    f[u][1] = (f[u][0] * f[v][1] % mod + f[u][1] * (2 * f[v][0] + f[v][1]) % mod) % mod;
    f[u][0] = f[u][0] * (2 * f[v][0]) % mod;
  }
}

void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].emplace_back(v, i), adj[v].emplace_back(u, i);
  }
  tarjan(1, 0);
  for (int u = 1; u <= n; u++) {
    for (auto [v, idx] : adj[u]) {
      if (bln[v] == bln[u]) ecnt[bln[u]]++;
      else g[bln[u]].push_back(bln[v]);
    }
  }
  for (int i = 1; i <= tot; i++) ecnt[i] /= 2;
  dfs(1, 0);
  for (int i = 1; i <= tot; i++) {
    // std::cout << f[i][0] << " " << f[i][1] << "\n";
    if (i == 1) (ans += f[i][1]) %= mod;
    else (ans += f[i][1] * fastPow(2, s[1] - s[i] - 1, mod) % mod) %= mod;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
