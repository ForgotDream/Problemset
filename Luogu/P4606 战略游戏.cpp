/**
 * @file    P4606 战略游戏.cpp
 * @author  ForgotDream
 * @brief   圆方树
 * @date    2023-05-11
 */
#include <bits/stdc++.h>

using i64 = long long;

std::vector<std::vector<int>> g, t;
std::vector<int> dep, dis;
std::vector<std::vector<int>> fa;
std::vector<int> dfn, low;

namespace FastIO{
  char buf[1 << 23], *p1 = buf, *p2 = buf;
  inline char gc() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++;
  }

  template<typename T>
  inline void read(T& x) {
    x = 0;
    T f = 1;
    char c = gc();
    while (!isdigit(c)) {
      if (c == '-') f = -1;
      c = gc();
    }
    while (isdigit(c)) x = x * 10 + c - '0', c = gc();
    x *= f;
    return;
  }

  template<typename T, typename ... args>
  inline void read(T& x, args& ... tmp) {
    read(x);
    read(tmp...);
    return;
  }

  template<typename T>
  inline void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x / 10) print(x / 10);
    putchar(x % 10 + '0');
    return;
  }

  template<typename T>
  inline void print(T x, char c) {
    print(x), putchar(c);
    return;
  }
}

using FastIO::read;
using FastIO::print;

void solve() {
  int n, m;
  read(n, m);

  g.assign(n + 1, std::vector<int>());
  t.assign(2 * n + 1, std::vector<int>());
  for (int i = 0; i < m; i++) {
    int u, v;
    read(u, v);
    g[u].push_back(v), g[v].push_back(u);
  }

  dfn.assign(n + 1, 0), low.assign(n + 1, 0);
  std::stack<int> s;
  int clk = 0, cnt = n;
  std::function<void(int)> tarjan = [&](int u) {
    dfn[u] = low[u] = ++clk;
    s.push(u);
    for (auto v : g[u]) {
      if (!dfn[v]) {
        tarjan(v);
        low[u] = std::min(low[u], low[v]);
        if (low[v] == dfn[u]) {
          int p;
          ++cnt;
          do {
            p = s.top();
            s.pop();
            t[cnt].push_back(p), t[p].push_back(cnt);
          } while (p != v);
          t[cnt].push_back(u), t[u].push_back(cnt);
        }
      } else {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
  };

  tarjan(1);

  dfn.assign(cnt + 1, 0), dep.assign(cnt + 1, 0), dis.assign(cnt + 1, 0);
  fa.assign(cnt + 1, std::vector<int>(20));
  clk = 0;
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    dfn[u] = ++clk;
    dep[u] = dep[frm] + 1;
    dis[u] = dis[frm] + (u <= n);
    fa[u][0] = frm;
    for (int i = 1; i <= 19; i++) {
      fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (auto v : t[u]) {
      if (v == frm) {
        continue;
      }
      dfs(v, u);
    }
  };

  dfs(1, 0);

  std::function<int(int, int)> getLCA = [&](int u, int v) -> int {
    if (dep[u] < dep[v]) {
      std::swap(u, v);
    }
    for (int i = 19; i >= 0; i--) {
      if (dep[fa[u][i]] >= dep[v]) {
        u = fa[u][i];
      }
    }
    if (u == v) {
      return u;
    }
    for (int i = 19; i >= 0; i--) {
      if (fa[u][i] != fa[v][i]) {
        u = fa[u][i];
        v = fa[v][i];
      }
    }
    return fa[u][0];
  };

  int q;
  read(q);

  std::vector<int> a;
  while (q--) {
    int s;
    read(s);
    a.resize(s);
    for (int i = 0; i < s; i++) {
      read(a[i]);
    }
    std::sort(a.begin(), a.end(), [&](const int &lhs, const int &rhs) {
      return dfn[lhs] < dfn[rhs];
    });
    int ans = 0;
    for (int i = 0; i < s; i++) {
      int u = a[i], v = a[(i + 1) % s];
      assert(u <= cnt && v <= cnt && getLCA(u, v) <= cnt);
      ans += dis[u] + dis[v] - 2 * dis[getLCA(u, v)];
    }
    if (getLCA(a[0], a[s - 1]) <= n) {
      ans += 2;
    }
    // std::cout << ans / 2 - s << "\n";
    print(ans / 2 - s, '\n');
  }
  
}

signed main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  int t;
  // std::cin >> t;
  read(t);

  while (t--) {
    solve();
  }

  return 0;
}