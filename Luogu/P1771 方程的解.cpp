/**
 * @file    P1771 方程的解.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
using i64 = long long;
int x, k;
constexpr int maxn = 295;
struct BigInt {
  int d[maxn], len;
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
    char s[maxn] = {};
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
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> k >> x;
  x = fastPow(x, x, 1000);
  x--, k--;
  BigInt ans = 1;
  for (int i = x - k + 1; i <= x; i++) ans = ans * i;
  for (int i = 1; i <= k; i++) ans = ans / i;
  std::cout << ans << "\n";
  return 0;
}