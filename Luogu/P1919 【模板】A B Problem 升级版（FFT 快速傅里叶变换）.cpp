/**
 * @file    P1919 【模板】A*B Problem 升级版（FFT 快速傅里叶变换）.cpp
 * @author  ForgotDream
 * @brief   Polygon Convolution
 * @date    2023-07-29
 */
#include <bits/stdc++.h>

using i64 = long long;

i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
namespace Polygon {
constexpr int N = 2.5e6 + 50;
template<typename T>
struct Polygon : std::vector<T> {
  using std::vector<T>::vector;
  using std::vector<T>::operator=;
  Polygon(const std::vector<T> &rhs) {
    this->resize(rhs.size()), std::copy(rhs.begin(), rhs.end(), this->begin());
  }
  const int length() const { return this->size(); }
  void extend(int base = 2) {
    auto l = std::ceil(std::log(length()) / std::log(base));
    l = fastPow(base, l, 998244353);
    resize(l);
  }
  Polygon<T> operator+(const Polygon<T> &rhs) const {
    Polygon<T> res(*this);
    res.resize(std::max(res.length(), rhs.length()));
    for (int i = 0; i < res.length(); i++) res[i] += rhs[i];
    return res;
  }
  Polygon<T> operator-(const Polygon<T> &rhs) const {
    Polygon<T> res(*this);
    res.resize(std::max(res.length(), rhs.length()));
    for (int i = 0; i < res.length(); i++) res[i] -= rhs[i];
    return res;
  }
  Polygon<T> &operator+=(const Polygon<T> &rhs) { return *this = *this + rhs; }
  Polygon<T> &operator-=(const Polygon<T> &rhs) { return *this = *this - rhs; }
};
namespace FFT {
const double pi = std::acos(-1);
template<typename T>
using comp = std::complex<T>;
int r[N];
void init(int len) {
  for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) + (i & 1) * (len >> 1);
}
template<typename T>
void perm(Polygon<comp<T>> &f) {
  int len = f.length();
  for (int i = 0; i < len; i++) if (i < r[i]) std::swap(f[i], f[r[i]]);
}
template<typename T>
void fft(Polygon<comp<T>> &f, int opt) {
  perm(f);
  int len = f.length();
  for (int h = 2; h <= len; h <<= 1) {
    comp<T> delta(std::cos(2 * pi / h), std::sin(opt * 2 * pi / h));
    for (int j = 0; j < len; j += h) {
      comp<T> w(1, 0);
      for (int k = j; k < j + (h >> 1); k++) {
        auto cur = f[k];
        auto t = w * f[k + (h >> 1)];
        f[k] = cur + t;
        f[k + (h >> 1)] = cur - t;
        w *= delta;
      }
    }
  }
  if (opt == -1) for (int i = 0; i < len; i++) 
    f[i].real(f[i].real() / len), f[i].imag(f[i].imag() / len);
}
}
namespace NTT {
constexpr int mod = 998244353, g = 3;
int r[N];
void init(int len) {
  for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) + (i & 1) * (len >> 1);
}
template<typename T>
void perm(Polygon<T> &f) {
  int len = f.length();
  for (int i = 0; i < len; i++) if (i < r[i]) std::swap(f[i], f[r[i]]);
}
template<typename T>
void ntt(Polygon<T> &f, int opt) {
  perm(f);
  int len = f.length();
  for (int h = 2; h <= len; h <<= 1) {
    int delta = fastPow(g, (mod - 1) / h, mod);
    for (int j = 0; j < len; j += h) {
      int w = 1;
      for (int k = j; k < j + (h >> 1); k++) {
        auto cur = f[k];
        auto t = 1ll * w * f[k + (h >> 1)] % mod;
        f[k] = (cur + t) % mod;
        f[k + (h >> 1)] = (cur - t + mod) % mod;
        w = 1ll * w * delta % mod;
      }
    }
  }
  if (opt == -1) {
    std::reverse(f.begin() + 1, f.end());
    int inv = fastPow(len, mod - 2, mod);
    for (int i = 0; i < len; i++) f[i] = 1ll * f[i] * inv % mod;
  }
}
}
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  auto read = [&]() {
    std::vector<int> res;
    char c = std::cin.get();
    while (!std::isdigit(c)) c = std::cin.get();
    while (std::isdigit(c)) res.push_back(c - '0'), c = std::cin.get();
    return res;
  };
  auto a(read()), b(read());
  int n = a.size() - 1, m = b.size() - 1;
  int len = std::ceil(std::log2(n + m + 1));
  len = fastPow(2, len, 998244353);

  Polygon::Polygon<std::complex<double>> c(len);
  for (int i = 0; i <= n; i++) c[i].real(a[i]);
  for (int i = 0; i <= m; i++) c[i].imag(b[i]);

  Polygon::FFT::init(len);
  Polygon::FFT::fft(c, 1);
  for (int i = 0; i < len; i++) c[i] *= c[i];
  Polygon::FFT::fft(c, -1);

  std::stack<int> ans;
  for (int i = 0; i <= n + m; i++) c[i].imag(c[i].imag() / 2);
  for (int i = n + m; i >= 0; i--) {
    int cur = int(c[i].imag() + 0.5);
    ans.push(cur % 10);
    if (i) c[i - 1].imag(int(cur / 10) + c[i - 1].imag());
    else if (cur / 10) ans.push(cur / 10);
  }
  while (!ans.empty()) {
    std::cout << ans.top();
    ans.pop();
  }
  std::cout << "\n";

  return 0;
}