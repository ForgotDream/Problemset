#include <bits/stdc++.h>
using namespace std;
int n, m, x, y[3333], z[3333];
long long f[3333][3333][2], inf = 6666666666666;
struct node {
  int x, y;
  bool operator<(node b) { return x < b.x; }
} a[3333];
int main() {
  scanf("%d%d", &n, &x);
  for (int i = 1; i <= n; i++) scanf("%d", &y[i]), a[++m] = {y[i], i};
  for (int i = 1; i <= n; i++) scanf("%d", &z[i]), a[++m] = (node){z[i], 0};
  a[++m] = {x, 0};
  a[++m] = (node){0, 0};
  sort(a + 1, a + m + 1);
  int wei = 0, chu = 0;
  for (int i = 1; i <= m; i++) {
    if (a[i].x == x) wei = i;
  }
  for (int i = 1; i <= m; i++)
    if (!a[i].x) chu = i;
  for (int i = 0; i < 3333; i++) {
    for (int j = 0; j < 3333; j++) {
      f[i][j][0] = f[i][j][1] = inf;
    }
  }
  f[chu][chu][0] = f[chu][chu][1] = 0;
  for (int len = 1; len < m; len++)
    for (int l = 1; l <= m - len + 1; l++) {
      int r = l + len - 1;
      if (l > 1) {
        if (a[l - 1].y > 0 &&
            (z[a[l - 1].y] < a[l].x || z[a[l - 1].y] > a[r].x)) {
        } else {
          f[l - 1][r][0] =
              min(f[l - 1][r][0], f[l][r][0] + a[l].x - a[l - 1].x);
          f[l - 1][r][0] =
              min(f[l - 1][r][0], f[l][r][1] + a[r].x - a[l - 1].x);
        }
      }
      if (r < m) {
        if (a[r + 1].y > 0 &&
            (z[a[r + 1].y] < a[l].x || z[a[r + 1].y] > a[r].x))
          ;
        else {
          f[l][r + 1][1] =
              min(f[l][r + 1][1], f[l][r][0] + a[r + 1].x - a[l].x);
          f[l][r + 1][1] =
              min(f[l][r + 1][1], f[l][r][1] + a[r + 1].x - a[r].x);
        }
      }
    }
  long long ans = inf;
  for (int i = 1; i <= wei; i++) {
    for (int j = wei; j <= m; j++) {
      ans = min(ans, min(f[i][j][0], f[i][j][1]));
    }
  }
  if (ans == inf) cout << -1;
  else cout << ans;
  return 0;
}
