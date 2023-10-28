#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 3;
#define db double
db x[N], y[N], a[N], b[N], r[N], c[N], d[N];
int u, s[N * 4];
#define f(i, t) (y[t] + x[t] * c[i])
void upd(int k, int t, int l, int r) {
  if (l == r) {
    if (f(l, t) > f(l, s[k])) s[k] = t;
    return;
  }
  int m = l + r >> 1;
  if (f(m, t) > f(m, s[k])) swap(t, s[k]);
  f(l, t) > f(l, s[k]) ? upd(k * 2, t, l, m) : upd(k * 2 + 1, t, m + 1, r);
}  // 李超树插入
db qry(int k, int l, int r) {
  if (l == r) return f(u, s[k]);
  int m = l + r >> 1;
  return max(f(u, s[k]), u > m ? qry(k * 2 + 1, m + 1, r) : qry(k * 2, l, m));
}  // 李超树查询
int main() {
  int n, i;
  db f, g;
  scanf("%d%lf", &n, &f);
  for (i = 1; i <= n; ++i)
    scanf("%lf%lf%lf", a + i, b + i, r + i), c[i] = a[i] / b[i], d[i] = c[i];
  sort(c + 1, c + n + 1);  // 离散化
  for (i = 1; i <= n; ++i) {
    u = lower_bound(c + 1, c + n + 1, d[i]) - c,
    f = max(f, b[i] * qry(1, 1, n));
    g = a[i] * r[i] + b[i], x[i] = f * r[i] / g, y[i] = f / g, upd(1, i, 1, n);
  }
  printf("%.3lf", f);
  return 0;
}
