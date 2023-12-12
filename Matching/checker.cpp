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
i64 f[N][N];
int p[N];
inline i64 nijou(i64 u) { return u * u; }
void solve() {
  std::cin >> n >> T;
  for (int i = 1; i <= n; i++) std::cin >> a[i].t >> a[i].f >> a[i].p;
  std::iota(p + 1, p + n + 1, 1);
  i64 ans = 0;
  do {
    i64 cur = a[p[1]].p, cost = a[p[1]].t;
    if (cost > T) break;
    ans = std::max(ans, cur);
    for (int i = 2; i <= n; i++) {
      cost += a[p[i]].t, cur += a[p[i]].p - nijou(a[p[i]].f - a[p[i - 1]].f);
      if (cost > T) break;
      ans = std::max(ans, cur);
    }
  } while(std::next_permutation(p + 1, p + n + 1));
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
