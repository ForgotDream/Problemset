#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int oo = 1000000000;

char a[10][10];
int f[10][10][10][10];

int calc(int x1, int y1, int x2, int y2, int i1, int j1, int i2, int j2) {
  int res = 0;
  for (int i = i1; i <= i2; ++i)
    for (int j = j1; j <= j2; ++j)
      if (a[i][j] == '#')
        res +=
            max(max(abs(i - x1), abs(i - x2)), max(abs(j - y1), abs(j - y2)));
  return res;
}

int dp(int x1, int y1, int x2, int y2) {
  if (x1 > x2 || y1 > y2) return 0;
  int &res = f[x1][y1][x2][y2];
  if (res > -1) return res;

  res = calc(x1, y1, x2, y2, x1, y1, x1, y2) + dp(x1 + 1, y1, x2, y2);
  res = min(res, calc(x1, y1, x2, y2, x2, y1, x2, y2) + dp(x1, y1, x2 - 1, y2));
  res = min(res, calc(x1, y1, x2, y2, x1, y1, x2, y1) + dp(x1, y1 + 1, x2, y2));
  res = min(res, calc(x1, y1, x2, y2, x1, y2, x2, y2) + dp(x1, y1, x2, y2 - 1));

  return res;
}

int main() {
  freopen("station.in", "r", stdin);
  freopen("station.out", "w", stdout);

  for (int i = 1; i <= 8; ++i) scanf("%s", a[i] + 1);

  memset(f, -1, sizeof(f));
  printf("%d\n", dp(1, 1, 8, 8));

  return 0;
}
