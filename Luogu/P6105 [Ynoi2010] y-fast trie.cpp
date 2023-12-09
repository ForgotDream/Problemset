/**
 * @file    P6105 [Ynoi2010] y-fast trie.cpp
 * @author  ForgotDream
 * @brief   Multiset
 * @date    2023-12-08
 */
#include <bits/stdc++.h>

#pragma region
namespace FastIO {
static constexpr signed bufsize = 1 << 20;
struct is {
  char inbuf[bufsize], *p1 = inbuf, *p2 = inbuf;
  inline char gc() {
    if (p1 == p2) p1 = inbuf, p2 = inbuf + fread(inbuf, 1, bufsize, stdin);
    return p1 == p2 ? EOF : *p1++;
  }
  template <typename T>
  inline void read(T &x) {
    x = 0;
    T f = 1;
    char c = gc();
    while (c < '0' || c > '9') f = ( c == '-' ? -f : f), c = gc();
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
  template <typename T>
  is &operator>>(T &rhs) { return read(rhs), *this; }
  is &operator>>(char *rhs) { return read(rhs), *this; }
};
struct os {
  char outbuf[bufsize], *pp = outbuf;
  ~os() { flush(); }
  inline void pc(const char &c) {
    if (pp - outbuf == bufsize) fwrite(outbuf, 1, bufsize, stdout), pp = outbuf;
    *pp++ = c;
  }
  template <typename T>
  inline void print(T x) {
    if (x < 0) x = -x, pc('-');
    static T sta[35];
    T top = 0;
    do sta[top++] = x % 10, x /= 10; while (x);
    while (top) pc(sta[--top] + '0');
  }
  inline void print(const char *s) { for (; *s; ++s) pc(*s); }
  inline void print(char *s) { for (; *s; ++s) pc(*s); }
  inline void print(const std::string &s) { for (const auto &c : s) pc(c); }
  inline void print(const char &c) { pc(c); }
  inline void flush() { fwrite(outbuf, 1, pp - outbuf, stdout), pp = outbuf; }
  template <typename T>
  os &operator<<(const T &rhs) { return print(rhs), *this; }
};
}  // namespace FastIO
FastIO::is fin;
FastIO::os fout;
#pragma endregion

using i64 = int64_t;

int n, siz;
i64 c;
std::multiset<i64> a, b;
i64 calc(i64 x, int opt) {
  if (x == -1) return -1;
  auto it = a.upper_bound(c - x - 1);
  if (it == a.begin()) return -1;
  it--;
  if (opt == 1 && *it == x && a.count(x) == 1) return it == a.begin() ? -1 : *std::prev(it);
  else return *it;
}
void insert(i64 x) {
  siz++;
  if (a.empty()) return a.insert(x), void();
  i64 y = calc(x, 0), z = calc(y, 1), w = calc(z, 1);
  if (y != -1 && z < x) {
    if (z != -1 && y == w) b.erase(b.find(y + z));
    b.insert(x + y);
  }
  a.insert(x);
}
void erase(i64 x) {
  siz--, a.erase(a.find(x));
  if (!siz) return;
  i64 y = calc(x, 0), z = calc(y, 1), w = calc(z, 1);
  if (y != -1 && z < x) {
    if (z != -1 && y == w) b.insert(y + z);
    b.erase(b.find(x + y));
  }
}
i64 query() {
  auto it = a.rbegin();
  if (a.count(*it) >= 2) return 2 * *it % c;
  else return (*it + *std::next(it)) % c;
}
void solve() {
  fin >> n >> c;
  i64 lst = 0;
  for (int i = 1, opt, x; i <= n; i++) {
    fin >> opt >> x, x ^= lst;
    x %= c;
    if (opt == 1) insert(x);
    else erase(x);
    if (siz < 2) fout << "EE\n", lst = 0;
    else fout << (lst = std::max(query(), b.empty() ? 0 : *b.rbegin())) << "\n";
  }
}

int main() {
  // std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
