/**
 * @file    P1066 [NOIP2006 提高组] 2^k进制数.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-11
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int P = 2050;
int k, w, rst, len;
struct BigInt {
  static constexpr int N = 300;
  int d[N], len;
  void clean() {
    while (len > 1 && !d[len - 1])
      len--;
  }
  BigInt() {
    memset(d, 0, sizeof(d));
    len = 1;
  }
  BigInt(int num) { *this = num; }
  BigInt(char *num) { *this = num; }
  BigInt operator=(const char *num) {
    memset(d, 0, sizeof(d));
    len = strlen(num);
    for (int i = 0; i < len; i++)
      d[i] = num[len - 1 - i] - '0';
    clean();
    return *this;
  }
  BigInt operator=(int num) {
    char s[20];
    sprintf(s, "%d", num);
    *this = s;
    return *this;
  }
  BigInt operator+(const BigInt &b) {
    BigInt c = *this;
    int i;
    for (i = 0; i < b.len; i++) {
      c.d[i] += b.d[i];
      if (c.d[i] > 9) c.d[i] %= 10, c.d[i + 1]++;
    }
    while (c.d[i] > 9) c.d[i++] %= 10, c.d[i]++;
    c.len = std::max(len, b.len);
    if (c.d[i] && c.len <= i) c.len = i + 1;
    return c;
  }
  BigInt operator-(const BigInt &b) {
    BigInt c = *this;
    int i;
    for (i = 0; i < b.len; i++) {
      c.d[i] -= b.d[i];
      if (c.d[i] < 0) c.d[i] += 10, c.d[i + 1]--;
    }
    while (c.d[i] < 0) c.d[i++] += 10, c.d[i]--;
    c.clean();
    return c;
  }
  BigInt operator*(const BigInt &b) const {
    int i, j;
    BigInt c;
    c.len = len + b.len;
    for (j = 0; j < b.len; j++)
      for (i = 0; i < len; i++)
        c.d[i + j] += d[i] * b.d[j];
    for (i = 0; i < c.len - 1; i++) c.d[i + 1] += c.d[i] / 10, c.d[i] %= 10;
    c.clean();
    return c;
  }
  BigInt operator/(const BigInt &b) {
    int i, j;
    BigInt c = *this, a = 0;
    for (i = len - 1; i >= 0; i--) {
      a = a * 10 + d[i];
      for (j = 0; j < 10; j++)
        if (a < b * (j + 1)) break;
      c.d[i] = j;
      a = a - b * j;
    }
    c.clean();
    return c;
  }
  BigInt operator%(const BigInt &b) {
    int i, j;
    BigInt a = 0;
    for (i = len - 1; i >= 0; i--) {
      a = a * 10 + d[i];
      for (j = 0; j < 10; j++)
        if (a < b * (j + 1)) break;
      a = a - b * j;
    }
    return a;
  }
  BigInt operator+=(const BigInt &b) {
    *this = *this + b;
    return *this;
  }
  bool operator<(const BigInt &b) const {
    if (len != b.len) return len < b.len;
    for (int i = len - 1; i >= 0; i--)
      if (d[i] != b.d[i]) return d[i] < b.d[i];
    return false;
  }
  bool operator>(const BigInt &b) const { return b < *this; }
  bool operator<=(const BigInt &b) const { return !(b < *this); }
  bool operator>=(const BigInt &b) const { return !(*this < b); }
  bool operator!=(const BigInt &b) const { return b < *this || *this < b; }
  bool operator==(const BigInt &b) const {
    return !(b < *this) && !(b > *this);
  }

  std::string str() const {
    char s[N] = {};
    for (int i = 0; i < len; i++) s[len - 1 - i] = d[i] + '0';
    return s;
  }
};
std::istream &operator>>(std::istream &in, BigInt &x) {
  std::string s;
  in >> s;
  x = s.c_str();
  return in;
}
std::ostream &operator<<(std::ostream &out, const BigInt &x) {
  out << x.str();
  return out;
}
int prime[P], pcnt;
bool isNotPrime[P];
void getPrime(int n) {
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) prime[++pcnt] = i;
    for (int j = 1; j <= pcnt && i * prime[j] <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}
int calc(int base, int p) {
  int res = 0, cpy = p;
  for (; p <= base; p *= cpy) res += base / p;
  return res;
}
i64 fastPow(i64 base, i64 exp) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base;
    base = base * base;
  }
  return res;
}
BigInt C(int n, int m) {
  if (m > n) return 0;
  BigInt res = 1;
  for (int i = 1; i <= pcnt; i++) {
    int ca = calc(n, prime[i]), cb = calc(m, prime[i]),
        cc = calc(n - m, prime[i]);
    // std::cerr << m << " " << prime[i] << " " << cb << "\n";
    res = res * fastPow(prime[i], ca - cb - cc);
  }
  return res;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  getPrime(2e3);
  std::cin >> k >> w;
  len = w / k, rst = w % k;
  int m = (1 << k) - 1;
  int lim = (1 << rst) - 1;
  BigInt ans = 0;
  for (int i = 2; i <= len; i++) ans += C(m, i);
  for (int i = 1; i <= lim; i++) ans += C(m - i, len);
  std::cout << ans << "\n";
  return 0;
}