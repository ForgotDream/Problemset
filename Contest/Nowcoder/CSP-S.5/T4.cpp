#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, q, id;
i64 a[N];
namespace P1_4 {
using pii = std::pair<int, int>;
std::vector<pii> query;
struct DSU {
  int fa[N];
  i64 sum[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v, a[v] += a[u];
    return true;
  }
} dsu;
void solve() {
  for (int i = 1, opt; i <= q; i++) {
    std::cin >> opt;
    if (opt == 1) {
      int u, v;
      std::cin >> u >> v;
      if (u > v) std::swap(u, v);
      dsu.merge(u, v);
      for (auto [pu, pv] : query) {
        if ((pu <= u && pv >= v) || (u <= pu && pu <= v) ||
            (u <= pv && pv <= v)) {
          dsu.merge(u, pu);
        }
      }
      query.emplace_back(u, v);
    } else {
      i64 k, b, c;
      std::cin >> k >> b >> c;
      i64 cur = 0;
      std::vector<i64> tmp;
      for (int i = 1; i <= n; i++) {
        if (dsu.fa[i] == i) tmp.push_back(a[i] / k);
      }
      if (tmp.size() < b) {
        std::cout << "No\n";
        continue;
      }
      std::nth_element(tmp.begin(), tmp.begin() + b - 1, tmp.end(),
                       std::greater<i64>());
      if (tmp[b - 1] >= c) std::cout << "Yes\n";
      else std::cout << "No\n";
    }
  }
}
}  // namespace P1_4
void solve() {
  std::cin >> n >> q >> id;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  if (1 <= id && id <= 4) P1_4::solve();
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
