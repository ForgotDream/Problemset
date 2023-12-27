/*
 * @file    P4211 [LNOI2014] LCA.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-25
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 50050, mod = 201314;
int n, m;
std::vector<int> adj[N];

int fa[N], son[N], siz[N];
void dfs(int u) {
  siz[u] = 1;
  for (auto v : adj[u]) {
    dfs(v), siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}

struct Tree {
  int lc[N], rc[N], fa[N];
  int stk[N], val[N], subsiz[N];
  int build(int s, int t) {
    if (s > t) return 0;
    int p = std::lower_bound(val + s, val + t + 1, (val[t] + val[s - 1]) / 2) - val;
    int u = stk[p];
    subsiz[u] = t - s + 1;
    if (s < p) fa[lc[u] = build(s, p - 1)] = u;
    if (p < t) fa[rc[u] = build(p + 1, t)] = u;
    return u;
  }
  int build(int u) {
    int p = u;
    while (p) {
      for (auto v : adj[p]) {
        if (v == son[p]) continue;
        fa[build(v)] = p;
      }
      p = son[p];
    }
    int cnt = 0;
    p = u;
    while (p) {
      stk[++cnt] = p;
      val[cnt] = val[cnt - 1] + siz[p] - siz[son[p]];
      p = son[p];
    }
    return build(1, cnt);
  }
  int sum[N], tag[N];
  void modify(int u) {
    bool flg = true;
    int tmp = 0;
    while (u) {
      sum[u] += tmp;
      if (flg) {
        tag[u]++;
        if (rc[u]) tag[rc[u]]--;
        tmp += 1 + subsiz[lc[u]];
        sum[u] -= subsiz[rc[u]];
      }
      flg = (u != lc[fa[u]]);
      if (flg && u != rc[fa[u]]) tmp = 0;
      u = fa[u];
    }
  }
  int query(int u) {
    bool flg = true;
    int res = 0, tmp = 0;
    while (u) {
      if (flg) {
        res += sum[u] - sum[rc[u]];
        res -= 1ll * subsiz[rc[u]] * tag[rc[u]];
        tmp += 1 + subsiz[lc[u]];
      }
      res += 1ll * tmp * tag[u];
      flg = (u != lc[fa[u]]);
      if (flg && u != rc[fa[u]]) tmp = 0;
      u = fa[u];
    }
    return res;
  }
} t;

std::vector<int> vl[N], vr[N];
int p[N];
i64 ans[N];

void solve() {
  std::cin >> n >> m;
  for (int i = 2; i <= n; i++) {
    std::cin >> fa[i], fa[i]++;
    adj[fa[i]].push_back(i);
  }

  dfs(1);
  t.build(1);

  for (int i = 1, l, r, z; i <= m; i++) {
    std::cin >> l >> r >> z, r++, z++;
    if (l) vl[l].push_back(i);
    vr[r].push_back(i), p[i] = z;
  }

  for (int i = 1; i <= n; i++) {
    t.modify(i);
    for (auto j : vl[i]) ans[j] -= t.query(p[j]);
    for (auto j : vr[i]) ans[j] += t.query(p[j]);
  }

  for (int i = 1; i <= m; i++) std::cout << ans[i] % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
