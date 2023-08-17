#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int M = 100;
int n, ans;
int a[2 * M + 50], f[2 * M + 50][2 * M + 50], g[2 * M + 50][2 * M + 50];
int sum[2 * M + 50];

void solve() {
  // memset(g, 0x3f, sizeof(g));
  ans = -1;
  for (int l = 1; l <= n; l++)
    for (int i = 1, j = l + i; i < 2 * n && j < 2 * n; i++, j = i + l) {
      g[i][j] = 0x3f3f3f3f;
      for (int k = i; k < j; k++) {
        f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1]);
        g[i][j] = min(g[i][j], g[i][k] + g[k + 1][j] + sum[j] - sum[i - 1]);
      }
    }
  ans = 0x3f3f3f3f;
  for (int i = 1; i <= n; i++) {
    ans = min(ans, g[i][i + n - 1]);
  }
  cout << ans << endl;
  ans = -1;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, f[i][i + n - 1]);
  }
  cout << ans << endl;
  return;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i], a[i + n] = a[i];
  for (int i = 1; i <= 2 * n; i++) sum[i] = sum[i - 1] + a[i];
  solve();
  return 0;
}