/**
 * @file    UVA11354 Bond.cpp
 * @author  ForgotDream
 * @brief   DSU 按秩合并 or Kruskal 重构树
 * @date    2023-02-27
 */
#include <bits/stdc++.h>

using i64 = long long;

static const int N = 1e5 + 50, INF = 0x3f3f3f3f;
struct Edge {
  int u, v, w;
  Edge() {
    u = 0;
    v = 0;
    w = 0;
    return;
  }
  Edge(int u, int v, int w) : u(u), v(v), w(w) {}
  bool operator< (const Edge &oth) const {
    return w < oth.w;
  }
};
std::vector<int> fa(N, 0), val(N, 0), rk(N, 0), w(N, 0);

inline void init() {
  std::iota(fa.begin(), fa.end(), 0);
  val.clear();
  val.resize(N, 0);
  rk.clear();
  rk.resize(N, 0);
  return;
}

inline int get(int u) {
  return u == fa[u] ? u : get(fa[u]);
}

void merge(int u, int v, int w) {
  int fau = get(u), fav = get(v);
  if (fau == fav) {
    return;
  }
  if (rk[fau] < rk[fav]) {
    fa[fau] = fav;
    val[fau] = w;
  } else {
    fa[fav] = fau;
    val[fav] = w;
    if (rk[fau] == rk[fav]) {
      rk[fau]++;
    }
  }
  return;
}

int calc(int u, int v) {
  int res = 0, cur = u;
  w.clear();
  w.resize(N, 0);

  int pivot = 1;
  while (true) {
    w[cur] = pivot;
    if (cur == fa[cur]) {
      break;
    }
    pivot = std::max(pivot, val[cur]);
    cur = fa[cur];
  }

  cur = v;
  while (true) {
    if (w[cur]) {
      res = std::max(res, w[cur]);
      break;
    } else if (cur == fa[cur]) {
      break;
    } else {
      res = std::max(res, val[cur]);
      cur = fa[cur];
    }
  }

  return res;
}

void solve(int n, int m) {
  static int d = 0;
  if (d++) {
    std::cout << "\n";
  }
  
  std::vector<Edge> e(m);
  init();

  for (auto &i : e) {
    std::cin >> i.u >> i.v >> i.w;
  }

  std::sort(e.begin(), e.end());
  for (auto i : e) {
    merge(i.u, i.v, i.w);
  }

  int q;
  std::cin >> q;
  while (q--) {
    int u, v;
    std::cin >> u >> v;
    std::cout << calc(u, v) << "\n";
  }

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;

  while (std::cin >> n >> m) {
    solve(n, m);
  }

  return 0;
}