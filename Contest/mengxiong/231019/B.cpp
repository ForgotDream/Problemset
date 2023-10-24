#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n, a[N];
struct Edge {
  int u, v, w;
  Edge() = default;
  Edge(int u, int v, int w) : u(u), v(v), w(w) {}
  bool operator<(const Edge &rhs) const { return w < rhs.w; }
};
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
struct ST {
  int mn[20][N], mx[20][N];
  int calcMin(int u, int v) { return a[u] < a[v] ? u : v; }
  int calcMax(int u, int v) { return a[u] > a[v] ? u : v; }
  void init() {
    for (int i = 1; i <= n; i++) mn[0][i] = mx[0][i] = i;
    for (int i = 1; i <= std::__lg(n); i++) {
      for (int j = 1; j <= n - (1 << i) + 1; j++) {
        mn[i][j] = calcMin(mn[i - 1][j], mn[i - 1][j + (1 << (i - 1))]);
        mx[i][j] = calcMax(mx[i - 1][j], mx[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  int queryMin(int l, int r) {
    int d = std::__lg(r - l + 1);
    return calcMin(mn[d][l], mn[d][r - (1 << d) + 1]);
  }
  int queryMax(int l, int r) {
    int d = std::__lg(r - l + 1);
    return calcMax(mx[d][l], mx[d][r - (1 << d) + 1]);
  }
} st;
std::vector<Edge> edges;
void solve(int l, int r) {
  if (l >= r) return;
  int mid = (l + r) >> 1, p = st.queryMax(l, mid);
  for (int i = mid + 1; i <= r; i++) edges.emplace_back(p, i, a[i] - a[p]);
  p = st.queryMin(mid + 1, r);
  for (int i = l; i <= mid; i++) edges.emplace_back(i, p, a[p] - a[i]);
  solve(l, mid), solve(mid + 1, r);
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  st.init();
  solve(1, n);
  std::sort(edges.begin(), edges.end());
  int cnt = 0;
  i64 ans = 0;
  for (auto [u, v, w] : edges) {
    if (dsu.merge(u, v)) {
      cnt++, ans += w;
      if (cnt == n - 1) break;
    }
  }
  std::cout << ans << "\n";
}

int main() {
  freopen("star.in", "r", stdin);
  freopen("star.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
