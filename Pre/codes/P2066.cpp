#include <cstdio>
#include <iostream>

using namespace std;

int n, m;
int a[20][20];
int f[20][20];
int step[20];

void rep(int dep = n, int cur = m) {
  if (dep == 0) return;
  for (int i = cur; i >= 0; i--) {
    if (f[dep - 1][cur - i] + a[dep][i] == f[dep][cur]) {
      step[dep] = i;
      rep(dep - 1, cur - i);
      return;
    }
  }
  return;
}

void solve() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      for (int k = 0; k <= j; k++)
        f[i][j] = max(f[i][j], f[i - 1][j - k] + a[i][k]);
  cout << f[n][m] << endl;
  rep();
  for (int i = 1; i <= n; i++) cout << i << " " << step[i] << endl;
  /*
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= m; j++) cout << f[i][j] << (j == m ? "\n" : " ");
  */
  return;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) cin >> a[i][j];
  solve();
  return 0;
}