#include <cstdio>
#include <iostream>

using namespace std;

int n, m, sx, sy;
long long f[50][50];
int d[][2] = {{-1, -2}, {-1, 2}, {1, -2}, {1, 2},
              {-2, -1}, {-2, 1}, {2, -1}, {2, 1}};

void pre() {
  f[sx][sy] = -1;
  for (int i = 0; i < 8; i++) {
    int dx = sx + d[i][0], dy = sy + d[i][1];
    if (dx > n || dy > m || dx < 0 || dy < 0) continue;
    f[dx][dy] = -1;
  }
  return;
}

void solve() {
  pre();
  f[0][0] = 1;
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      if (f[i][j] == -1)
        f[i][j] = 0;
      else {
        if (i > 0) f[i][j] += f[i - 1][j];
        if (j > 0) f[i][j] += f[i][j - 1];
      }
  cout << f[n][m] << endl;
  // for (int i = 0; i <= n; i++) {
  //  for (int j = 0; j <= m; j++) cout << f[i][j] << " ";
  //  cout << endl;
  //}
  return;
}

int main() {
  cin >> n >> m >> sx >> sy;
  solve();
  return 0;
}