#include <bits/stdc++.h>

using namespace std;

static const int N = 150, INF = 0x3f3f3f3f, M = 1e6 + 50;
int n, m;
int a[N], b[N], f[M][2], sum[2];
int ans = INF;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  memset(f, 0x3f, sizeof(f));
  f[0][0] = f[0][1] = 0;

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sum[0] += a[i];
  }

  cin >> m;
  for (int i = 1;i <= m; i++) {
    cin >> b[i];
    sum[1] += b[i];
  }

  for (int i = 1; i <= n; i++) {
    for (int j = sum[0]; j >= a[i]; j--) {
      f[j][0] = min(f[j][0], f[j - a[i]][0] + 1);
    }
  }

  for (int i = 1; i <= m; i++) {
    for (int j = sum[1]; j >= b[i]; j--) {
      f[j][1] = min(f[j][1], f[j - b[i]][1] + 1);
    }
  }

  for (int i = 1; i <= min(sum[0], sum[1]); i++) {
    if (f[i][0] != INF && f[i][1] != INF) {
      ans = min(ans, f[i][0] + f[i][1]);
    }
  }

  if (ans == INF) {
    cout << "impossible" << '\n';
  } else {
    cout << ans << '\n';
  }

  return 0;
}