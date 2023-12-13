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
int cq[N][N], ch[N], ct[N];
inline i64 nijou(i64 u) { return u * u; }
inline i64 x(int i, int) { return a[i].f; }
inline i64 y(int i, int j) { return f[i][j] + a[i].p - nijou(a[i].f); }
inline i64 up(int i, int j, int k) { return x(i, k) - x(j, k); }
inline i64 dn(int i, int j, int k) { return y(i, k) - y(j, k); }
void calc(int i, int j) {
  int k = j - a[i].t, *q = cq[k], *h = &ch[k], *t = &ct[k];
  while (h < t && up(q[*h], q[*h + 1], k) > dn(q[*h], q[*h + 1], k) * (-2 * a[i].f)) h++;
  int u = q[*h];
  // std::cerr << i << " " << u << " " << j << "\n";
  f[i][j] = std::max(f[i][j], f[u][k] + a[i].p - nijou(a[i].f - a[u].f));
  q = cq[j], h = &ch[j], t = &ct[j];
  while (h < t && up(q[*t - 1], q[*t], j) * dn(q[*t], i, j) < dn(q[*t - 1], q[*t], j) * up(q[*t], i, j)) t--;
  q[++*t] = i;
}
void solve() {
  std::cin >> n >> T;
  for (int i = 1; i <= n; i++) std::cin >> a[i].t >> a[i].f >> a[i].p;
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= T; i++) cq[i][1] = 1, ch[i] = ct[i] = 1;
  for (int i = a[1].t; i <= T; i++) f[1][i] = a[1].p;
  std::sort(a + 1, a + n + 1);
  for (int i = 2; i <= n; i++) {
    for (int j = T; j >= a[i].t; j--) {
      f[i][j] = a[i].p;
      calc(i, j);
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
