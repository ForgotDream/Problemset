#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5050;
int n, T;
struct Node {
  int t, f, p;
  friend bool operator<(const Node &lhs, const Node &rhs) {
    return lhs.f > rhs.f;
  }
} a[N];
i64 f[N][N];
int cq[N][N], ch[N], ct[N];
int cur;
inline i64 nijou(i64 u) { return u * u; }
inline i64 x(int i) { return a[i].f; }
inline i64 y(int i) { return f[i][cur] + a[i].p - nijou(a[i].f); }
inline i64 up(int i, int j) { return y(i) - y(j); }
inline i64 dn(int i, int j) { return x(i) - x(j); }
void calc(int i, int j) {
  int k = j - a[i].t, *q = cq[k], *h = &ch[k], *t = &ct[k];
  cur = k;
  while (*h < *t && up(q[*h], q[*h + 1]) <= dn(q[*h], q[*h + 1]) * (2 * a[i].f)) ++*h;
  int u = q[*h];
  f[i][j] = std::max(f[i][j], f[u][k] + a[i].p - nijou(a[i].f - a[u].f));
  std::cerr << i << " " << u << " " << j << " " << f[i][j] << " " << f[u][k] << "\n";
  q = cq[j], h = &ch[j], t = &ct[j];
  cur = j;
  while (*h < *t && (!dn(q[*t - 1], q[*t]) || up(q[*t - 1], q[*t]) * dn(q[*t], i) <= dn(q[*t - 1], q[*t]) * up(q[*t], i))) --*t;
  // while (*h < *t && (!dn(q[*t], i) || up(q[*t - 1], q[*t]) * dn(q[*t], i) < dn(q[*t - 1], q[*t]) * up(q[*t], i))) --*t;
  q[++*t] = i;
}
void solve() {
  std::cin >> n >> T;
  for (int i = 1; i <= n; i++) std::cin >> a[i].t >> a[i].p >> a[i].f;
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) std::cerr << a[i].t << " " << a[i].f << " " << a[i].p << "\n";
  // for (int i = 0; i <= T; i++) cq[i][1] = 1, ch[i] = ct[i] = 1;
  for (int i = a[1].t; i <= T; i++) cq[i][1] = 1, ch[i] = ct[i] = 1;
  for (int i = a[1].t; i <= T; i++) f[1][i] = a[1].p;
  std::sort(a + 1, a + n + 1);
  for (int i = 2; i <= n; i++) {
    for (int j = T; j >= a[i].t; j--) {
      f[i][j] = a[i].p;
      calc(i, j);
    }
    // for (int j = a[i].t; j <= T; j++) {
    //   f[i][j] = a[i].p;
    //   calc(i, j);
    // }
  }
  i64 mx = 0;
  for (int i = 1; i <= n; i++) mx = std::max(mx, f[i][T]);
  // for (int i = 1; i <= n; i++) for (int j = 0; j <= T; j++) mx = std::max(mx, f[i][j]);
  std::cout << mx << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
