#include <bits/stdc++.h>

using i64 = long long;

struct DSU {
  int n;
  std::vector<int> fa;

  DSU(int _n) {
    n = _n;
    fa.assign(n, 0);
    std::iota(fa.begin(), fa.end(), 0);
  }

  int find(int u) {
    while (u != fa[u]) {
      u = fa[u] = fa[fa[u]];
    }
    return u;
  }

  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) {
      return false;
    } else {
      fa[u] = v;
      return true;
    }
  }
};

struct Edge {
  int u, v, w;
  Edge(int _u = 0, int _v = 0, int _w = 0) {
    u = _u, v = _v, w = _w;
  }
  friend bool operator<(const Edge &lhs, const Edge &rhs) {
    return lhs.w < rhs.w;
  }
};

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  freopen("mst.in", "r", stdin);
  freopen("mst.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, p;
  std::cin >> n >> p;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  if (std::count(a.begin(), a.end(), 1) == n) {
    std::cout << 1ll * std::min(p, 1) * (n - 1) << "\n";
    return 0;
  } else if (p == 1) {
    std::cout << n - 1 << "\n";
    return 0;
  }

  std::vector<Edge> edges;
  for (int i = 0; i < n - 1; i++) {
    edges.emplace_back(i, i + 1, p);
  }

  for (int i = 0; i < n - 1; i++) {
    int min = a[i], g = a[i];
    for (int j = i + 1; j < n; j++) {
      min = std::min(min, a[j]);
      g = gcd(g, a[j]);
      if (min == g) {
        edges.emplace_back(i, j, min);
      }
    }
  }

  std::sort(edges.begin(), edges.end());

  int cnt = 0;
  i64 ans = 0;
  DSU dsu(n);
  for (int i = 0; i < edges.size(); i++) {
    int u = edges[i].u, v = edges[i].v, w = edges[i].w;
    if (dsu.merge(u, v)) {
      ans += w;
      cnt++;
    }
    if (cnt == n - 1) {
      break;
    }
  }

  std::cout << ans << "\n";

  return 0;
}