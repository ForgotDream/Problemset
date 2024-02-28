#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1e5;
const long double eps = 1e-12;
int n, k, g[N + 5];
int q[N + 5], hd, tl;
long double f[N + 5];
long double l, r, mid;
inline long double slope(int x, int y) { return (f[x] - f[y]) / (x - y); }
int check() {
  std::cerr << mid << "\n";
  q[hd = tl = 1] = 0;
  for (int i = 1; i <= n; ++i) {
    for (; hd < tl && slope(q[hd], q[hd + 1]) - 1.0 / i > eps; ++hd);
    f[i] = f[q[hd]] + (long double)(i - q[hd]) / i - mid, g[i] = g[q[hd]] + 1;
    for (; hd < tl && slope(q[tl - 1], q[tl]) - slope(q[tl], i) < -eps; --tl);
    q[++tl] = i;
  }
  return g[n] >= k;
}
int main() {
  scanf("%d%d", &n, &k);
  l = 0, r = 1e6;
  for (int i = 1; i <= 200; ++i) {
    mid = (l + r) / 2;
    if (check())
      l = mid;
    else
      r = mid;
  }
  mid = l, check();
  printf("%.9Lf\n", f[n] + k * mid);
}
