/**
 * @file    P2522 [HAOI2011] Problem b.cpp
 * @author  ForgotDream
 * @brief   整除分块 + Mobius Invertion
 * @date    2023-10-08
 */
#include <iostream>

#pragma region
struct FastIO {
  static constexpr signed bufsize = 1 << 18;
  char inbuf[bufsize], *p1 = inbuf, *p2 = inbuf;
  char outbuf[bufsize], *pp = outbuf;
  ~FastIO() { flush(); }
  inline char gc() {
    if (p1 == p2) p1 = inbuf, p2 = inbuf + fread(inbuf, 1, bufsize, stdin);
    return p1 == p2 ? EOF : *p1++;
  }
  template <typename T>
  inline void read(T &x) {
    x = 0;
    T f = 1;
    char c = gc();
    while (c < '0' || c > '9') f = (c == '-' ? -f : f), c = gc();
    while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = gc();
    x *= f;
  }
  inline void read(char *s) {
    char c = gc();
    while (c == ' ' || c == '\n' || c == '\r') c = gc();
    while (c != ' ' && c != '\n' && c != '\r') *s++ = c, c = gc();
  }
  inline void read(char &c) {
    c = gc();
    while (c == ' ' || c == '\n' || c == '\r') c = gc();
  }
  inline void read(std::string &s) {
    std::string().swap(s);
    char c = gc();
    while (c == ' ' || c == '\n' || c == '\r') c = gc();
    while (c != ' ' && c != '\n' && c != '\r') s += c, c = gc();
  }
  template <typename T = int>
  inline T read() {
    T res;
    read(res);
    return res;
  }
  inline void pc(const char &c) {
    if (pp - outbuf == bufsize) fwrite(outbuf, 1, bufsize, stdout), pp = outbuf;
    *pp++ = c;
  }
  template <typename T>
  inline void print(T x) {
    if (x < 0) x = -x, pc('-');
    static T sta[35];
    T top = 0;
    do sta[top++] = x % 10, x /= 10;
    while (x);
    while (top) pc(sta[--top] + '0');
  }
  inline void print(const char *s) {
    for (; *s; ++s) pc(*s);
  }
  inline void print(char *s) {
    for (; *s; ++s) pc(*s);
  }
  inline void print(const std::string &s) {
    for (const auto &c : s) pc(c);
  }
  inline void print(const char &c) { pc(c); }
  inline void flush() { fwrite(outbuf, 1, pp - outbuf, stdout), pp = outbuf; }
  template <typename T>
  FastIO &operator>>(T &rhs) {
    return read(rhs), *this;
  }
  FastIO &operator>>(char *rhs) { return read(rhs), *this; }
  template <typename T>
  FastIO &operator<<(const T &rhs) {
    return print(rhs), *this;
  }
} fin, fout;
#pragma endregion

using i64 = long long;

constexpr int N = 5e4 + 50;
int n;
bool isNotPrime[N];
int prime[N], mu[N], cnt;
void getMu(int n) {
  mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) mu[i] = -1, prime[++cnt] = i;
    for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      mu[i * prime[j]] = -mu[i];
      if (i % prime[j] == 0) {
        mu[i * prime[j]] = 0;
        break;
      }
    }
  }
}
inline i64 calc(i64 a, i64 b, i64 k) {
  i64 res = 0;
  a /= k, b /= k;
  for (int l = 1, r; l <= std::min(a, b); l = r + 1) {
    r = std::min(a / (a / l), b / (b / l));
    res += (mu[r] - mu[l - 1]) * (a / l) * (b / l);
  }
  return res;
}
void solve() {
  getMu(5e4);
  for (int i = 1; i <= 5e4; i++) mu[i] += mu[i - 1];
  fin >> n;
  for (int i = 1; i <= n; i++) {
    int a, b, c, d, k;
    fin >> a >> b >> c >> d >> k;
    fout << calc(b, d, k) - calc(b, c - 1, k) - calc(a - 1, d, k) +
                calc(a - 1, c - 1, k)
         << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
