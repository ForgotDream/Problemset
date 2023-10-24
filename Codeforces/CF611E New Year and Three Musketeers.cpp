/**
 * @file    CF611E New Year and Three Musketeers.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-09-07
 */
#include <algorithm>
#include <iostream>
#include <set>

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
FastIO &operator>>(T &rhs) { return read(rhs), *this; }
FastIO &operator>>(char *rhs) { return read(rhs), *this; }
template <typename T>
FastIO &operator<<(const T &rhs) { return print(rhs), *this; }
} fin, fout;
#pragma endregion

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, a[3];
int t[N];
std::multiset<int> s;
int calc(int u) {
  auto it = s.upper_bound(u);
  if (it == s.begin()) return 0;
  int res = *(--it);
  s.erase(it);
  return res;
}
void solve() {
  fin >> n >> a[0] >> a[1] >> a[2];
  for (int i = 1; i <= n; i++) fin >> t[i], s.insert(t[i]);
  std::sort(a, a + 3);
  int ans = 0;
  for (int i = 1; !s.empty() && i <= n; i++) {
    int max = *s.rbegin();
    ans++;
    if (max <= a[0]) {
      ans += (s.size() - 1) / 3;
      break;
    } else if (max <= a[1]) {
      for (int j = 0; j < 3; j++) calc(a[j]);
    } else if (max <= a[2]) {
      int w = calc(a[0]);
      if (w) {
        if (calc(a[1])) {
          calc(a[2]);
        } else {
          s.insert(w);
          calc(a[0] + a[1]), calc(a[2]);
        }
      } else {
        calc(a[0] + a[1]), calc(a[2]);
      }
    } else {
      if (max <= a[0] + a[1]) {
        calc(a[0] + a[1]), calc(a[2]);
      } else if (max <= a[0] + a[2]) {
        calc(a[0] + a[2]), calc(a[1]);
      } else if (max <= a[1] + a[2]) {
        calc(a[1] + a[2]), calc(a[0]);
      } else if (max <= a[0] + a[1] + a[2]) {
        calc(a[0] + a[1] + a[2]);
      } else {
        fout << -1 << "\n";
        return;
      }
    }
  }
  fout << ans << "\n";
}

signed main() {
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}