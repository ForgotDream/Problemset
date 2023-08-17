#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

double f[20][1 << 16];
int n;
double x[20], y[20];
double dis[20][20], ans;

void init() {
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++) dis[i][j] = hypot(x[i] - x[j], y[i] - y[j]);
  return;
}

void solve() {
  for (int i = 1; i <= n; i++) {
    f[i][1 << (i - 1)] = dis[i][0];
  }
  for (int k = 1; k < 1 << n; k++) {
    for (int i = 1; i <= n; i++) {
      if ((k & 1 << (i - 1)) == 0) continue;
      for (int j = 1; j <= n; j++) {
        if (i == j) continue;
        if ((k & 1 << (j - 1)) == 0) continue;
        f[i][k] = min(f[i][k], f[j][k - (1 << (i - 1))] + dis[i][j]);
      }
    }
  }
  for (int i = 1; i <= n; i++) ans = min(ans, f[i][(1 << n) - 1]);
  printf("%.2lf\n", ans);
  return;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
  init();
  memset(f, 127, sizeof(f));
  ans = f[0][0];
  solve();
  return 0;
}