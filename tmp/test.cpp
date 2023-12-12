#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5050;
int n, T;
struct Node {
  int t, f, p;
  friend bool operator<(const Node &lhs, const Node &rhs) {
    return lhs.f < rhs.f;
  }
} a[N];
i64 ans;
inline i64 nijou(i64 u) { return u * u; }
void dfs(int idx, int pre, int cost, i64 cur) {
  if (cost > T) return;
  if (idx == n) {
    ans = std::max(ans, cur);
    return;
  }
  for (int i = idx + 1; i <= n; i++) {
    dfs(i, pre, cost, cur);
    if (cost + a[i].t > T) continue;
    i64 d = pre ? nijou(a[i].f - a[pre].f) : 0;
    dfs(i, i, cost + a[i].t, cur + a[i].p - d);
  }
}
void solve() {
  std::cin >> n >> T;
  for (int i = 1; i <= n; i++) std::cin >> a[i].t >> a[i].f >> a[i].p;
  std::sort(a + 1, a + n + 1);
  dfs(0, 0, 0, 0);
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
