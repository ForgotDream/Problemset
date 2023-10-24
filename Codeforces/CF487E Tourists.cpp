/**
 * @file    CF487E Tourists.cpp
 * @author  ForgotDream
 * @brief   Block Round Tree + Segment Tree + HLD
 * @date    2023-05-11
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  constexpr int INF = 1e9;

  int n, m, q;
  std::cin >> n >> m >> q;

  std::vector<int> w(2 * n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> w[i];
  }

  std::vector<std::vector<int>> g(n + 1), t(2 * n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  std::vector<int> dfn(n + 1), low(n + 1);
  int clk = 0, cnt = n;
  std::stack<int> s;
  std::function<void(int)> tarjan = [&](int u) {
    dfn[u] = low[u] = ++clk;
    s.push(u);
    for (auto v : g[u]) {
      if (!dfn[v]) {
        tarjan(v);
        low[u] = std::min(low[u], low[v]);
        if (dfn[u] == low[v]) {
          int p;
          cnt++;
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

  dfn.assign(cnt + 1, 0);
  clk = 0;
  std::vector<int> fa(cnt + 1), son(cnt + 1);
  std::vector<int> siz(cnt + 1), top(cnt + 1), idx(cnt + 1), dep(cnt + 1);
  std::function<void(int, int)> dfs1 = [&](int u, int frm) {
    siz[u] = 1;
    dep[u] = dep[frm] + 1;
    fa[u] = frm;
    for (auto v : t[u]) {
      if (v == frm) {
        continue;
      }
      dfs1(v, u);
      siz[u] += siz[v];
      if (siz[son[u]] < siz[v]) {
        son[u] = v;
      }
    }
  };

  std::function<void(int, int)> dfs2 = [&](int u, int rt) {
    top[u] = rt, dfn[u] = ++clk, idx[dfn[u]] = u;
    if (son[u]) {
      dfs2(son[u], rt);
    }
    for (auto v : t[u]) {
      if (v == son[u] || v == fa[u]) {
        continue;
      }
      dfs2(v, v);
    }
  };

  dfs1(1, 0);
  dfs2(1, 1);
  
  std::vector<std::multiset<int>> ms(cnt - n + 1);
  for (int i = 2; i <= n; i++) {
    int f = fa[i];
    ms[f - n].insert(w[i]);
  }
  for (int i = n + 1; i <= cnt; i++) {
    if (ms[i - n].empty()) {
      w[i] = INF;
    } else {
      w[i] = *ms[i - n].begin();
    }
  }

  std::vector<int> min((cnt << 2) + 1);
  std::function<void(int, int, int)> build = [&](int l, int r, int u) {
    if (l == r) {
      min[u] = w[idx[l]];
      return;
    }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(l, mid, lc), build(mid + 1, r, rc);
    min[u] = std::min(min[lc], min[rc]);
  };

  build(1, cnt, 1);

  std::function<void(int, int, int, int, int)> modify = 
  [&](int target, int s, int t, int u, int val) {
    if (target == s && t == target) {
      min[u] = val;
      return;
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (target <= mid) {
      modify(target, s, mid, lc, val);
    } else {
      modify(target, mid + 1, t, rc, val);
    }
    min[u] = std::min(min[lc], min[rc]);
  };

  std::function<int(int, int, int, int, int)> query = 
  [&](int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) {
      return min[u];
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = INF;
    if (l <= mid) {
      res = std::min(res, query(l, r, s, mid, lc));
    }
    if (r > mid) {
      res = std::min(res, query(l, r, mid + 1, t, rc));
    }
    return res;
  };

  std::function<int(int, int)> queryP2P = [&](int u, int v) {
    int res = INF;
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) {
        std::swap(u, v);
      }
      // std::cerr << dfn[top[u]] << " " << dfn[u] << "\n";
      res = std::min(res, query(dfn[top[u]], dfn[u], 1, cnt, 1));
      u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
      std::swap(u, v);
    }
    res = std::min(res, query(dfn[u], dfn[v], 1, cnt, 1));
    if (u > n) {
      res = std::min(res, w[fa[u]]);
    }
    return res;
  };

  while (q--) {
    char c;
    int u, v;
    std::cin >> c >> u >> v;
    if (c == 'C') {
      modify(dfn[u], 1, cnt, 1, v);
      if (u == 1) {
        w[u] = v;
        continue;
      }
      int f = fa[u];
      std::cerr << f << " ";
      ms[f - n].erase(ms[f - n].find(w[u]));
      // std::cerr << f << " ";
      ms[f - n].insert(v);
      // std::cerr << f << "\n";
      int curMin = *ms[f - n].begin();
      if (curMin == w[f]) {
        w[u] = v;
        continue;
      }
      modify(dfn[f], 1, cnt, 1, curMin);
      w[f] = curMin, w[u] = v;
    } else {
      std::cout << queryP2P(u, v) << "\n";
    }
  }

  return 0;
}