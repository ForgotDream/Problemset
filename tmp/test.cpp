#include <cstdio>
#include <iostream>
#define gmi(a, b) a = a - b >> 31 ? a : b
#define FOF(i, a, b) for (int i = a; i < b; i++)
using namespace std;
const int M = 23, N = 1 << M;
int n, m, K, x, y, z, s, L, R;
int f[N], g[M][M], w[M][M], c[M][M], lg[N], sz[N];
int main() {
  scanf("%d%d%d", &n, &m, &K), x = -1;
  while (n--)
    scanf("%d", &y), ~x ? ++g[x][--y] : --y, x = y;
  FOF(i, 0, m)
  FOF(j, 0, m) if (i ^ j) w[0][i] += g[j][i] * K - g[i][j],
      c[i][j] = g[i][j] * (1 + K) + g[j][i] * (1 - K);
  R = 1 << m;
  L = R - 1;
  lg[0] = -1;
  FOF(i, 1, R) sz[i] = sz[i >> 1] + (i & 1), lg[i] = lg[i >> 1] + 1, f[i] = 1e9;
  FOF(i, 0, L) {
    z = lg[i & -i];
    if (s = sz[i])
      FOF(j, 0, m) w[s][j] = w[s - 1][j] + c[j][z]; // 只有这里和方法四不同
    for (x = L ^ i; y = x & -x; x ^= y)
      z = f[i] + w[s][lg[y]] * (s + 1), gmi(f[i | y], z);
  }
  cout << f[L] << '\n';
}
