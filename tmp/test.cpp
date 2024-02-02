#include <bits/stdc++.h>
using namespace std;
const int N = 4.2e6;
const double PI = acos(-1);
int n, r[N];
struct Complex {
  double r, i;
  inline Complex operator+(Complex &x) { return {r + x.r, i + x.i}; }
  inline Complex operator-(Complex &x) { return {r - x.r, i - x.i}; }
  inline Complex operator*(Complex &x) {
    return {r * x.r - i * x.i, r * x.i + i * x.r};
  }
  inline void operator+=(Complex &x) {
    r += x.r;
    i += x.i;
  }
  inline void operator*=(Complex &x) {
    double t = r;
    r = r * x.r - i * x.i;
    i = t * x.i + i * x.r;
  }
} f[N], g[N];
inline void FFT(Complex a[], int op) {
  for (int i = 0; i < n; i++)  // 根据映射关系交换元素
    if (i < r[i]) {
      auto t = a[i];
      a[i] = a[r[i]];
      a[r[i]] = t;
    }
  for (int i = 1; i < n; i <<= 1) {
    Complex W = {cos(PI / i), sin(PI / i) * op};
    for (int j = 0; j < n; j += i << 1)  // 控制一层中的子问题个数
    {
      Complex w = {1, 0};
      for (int k = 0; k < i; k++, w *= W) {
        auto t = a[i + j + k] * w;
        a[i + j + k] = a[j + k] - t;
        a[j + k] += t;
        // 蝴蝶操作
      }
    }
  }
}
int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int m, l = 0;
  std::cin >> n >> m;
  for (int i = 0; i <= n; i++) std::cin >> f[i].r;
  for (int i = 0; i <= m; i++) std::cin >> g[i].r;
  for (m += n, n = 1; n <= m; n <<= 1, l++);
  for (int i = 0; i < n; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
  FFT(f, 1);
  FFT(g, 1);
  for (int i = 0; i < n; i++) f[i] *= g[i];
  FFT(f, -1);
  std::cout << std::fixed << std::setprecision(0);
  for (int i = 0; i <= m; i++) std::cout << (fabs(f[i].r) / n) << ' ';
  return 0;
}
