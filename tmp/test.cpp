#include <cstdio>
#include <iostream>
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOS(i, a, b) for (int i = a; i >= b; i--)
#define N 60
#define M 1400
using namespace std;
int s[N][N], f[N][M], maxl[N][M], ans, n, m, x;
int main() {
  scanf("%d%d", &n, &m);
  FOR(j, 1, n)
  FOS(i, n, j) scanf("%d", &x), s[i][j] = s[i][j - 1] + x;
  FOR(i, 1, n) {
    FOS(j, i, 1)
    FOS(k, min(j + i * (i - 1) / 2, m), j * (j + 1) / 2) {
      f[j][k] = maxl[j - 1][k - j] + s[i][j];
      maxl[j][k] = max(maxl[j + 1][k], f[j][k]);
      ans = max(ans, f[j][k]);
    }
    FOR(k, i * (i - 1) / 2 + 1, i * (i + 1) / 2)
    FOS(j, k - i * (i - 1) / 2 - 1, 0)
    maxl[j][k] = max(maxl[j + 1][k], f[j][k]);
    FOR(k, 1, i * (i + 1) / 2)
    maxl[0][k] = max(maxl[1][k], maxl[0][k]);
  }
  printf("%d", ans);
  return 0;
}
