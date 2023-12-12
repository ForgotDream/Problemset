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
int q[N][N], h[N], t[N];
inline i64 nijou(i64 u) { return u * u; }
void solve() {
  std::cin >> n >> T;
  for (int i = 1; i <= n; i++) std::cin >> a[i].t >> a[i].f >> a[i].p;
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = a[i].t; j <= T; j++) {
      f[i][j] = a[i].p;
      for (int k = 1; k < i; k++) {
        f[i][j] = std::max(f[i][j], 
                           f[k][j - a[i].t] + a[i].p - nijou(a[i].f - a[k].f));
      }
    }
  }
  i64 mx = 0;
  for (int i = 1; i <= n; i++) mx = std::max(mx, f[i][T]);
  std::cout << mx << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
