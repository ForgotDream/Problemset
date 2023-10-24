/**
 * @file    P3803 多项式乘法（FFT）.cpp
 * @author  ForgotDream
 * @brief   FFT
 * @date    2023-04-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace MyFile {
void useFileInuput() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif
  return;
}
};

namespace Polygon {
using comp = std::complex<f80>;

static const f80 PI = std::acos(-1);

void change(std::vector<comp> &f) {
  int len = f.size();
  static std::vector<int> rev(len);
  // std::cerr << "OK" << "\n";

  for (int i = 0; i < len; i++) {
    rev[i] = (rev[i >> 1] >> 1) + (i & 1) * (len >> 1);
  }

  for (int i = 0; i < len; i++) {
    if (i < rev[i]) {
      std::swap(f[i], f[rev[i]]);
    }
  }

  return;
}

void fft(std::vector<comp> &f, const int &opt) {
  change(f);

  int len = f.size();

  for (int h = 2; h <= len; h <<= 1) {
    comp delta(std::cos(2 * PI / h), std::sin(opt * 2 * PI / h));
    for (int j = 0; j < len; j += h) {
      comp w(1, 0);
      for (int k = j; k < j + h / 2; k++) {
        comp cur = f[k], t = w * f[k + h / 2];
        f[k] = cur + t;
        f[k + h / 2] = cur - t;
        w *= delta;
      }
    }
  }

  if (opt == -1) {
    for (int i = 0; i < len; i++) {
      f[i] = f[i].real() / len;
    }
  }

  return;
}
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::complex<f80>> a(n + 1), b(m + 1);
  for (int i = 0; i <= n; i++) {
    std::cin >> a[i];
  }
  for (int i = 0; i <= m; i++) {
    std::cin >> b[i];
  }

  int len = 1;
  while (len <= n + m) {
    len <<= 1;
  }

  a.resize(len), b.resize(len);

  Polygon::fft(a, 1);
  Polygon::fft(b, 1);

  for (int i = 0; i < len; i++) {
    a[i] *= b[i];
  }

  Polygon::fft(a, -1);

  for (int i = 0; i <= n + m; i++) {
    std::cout << static_cast<int>(a[i].real() + 0.5) << " \n"[i == len - 1];
  }

  return 0;
}