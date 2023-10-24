/**
 * @file    CF611A New Year and Days.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-07
 */
#include <algorithm>
#include <iostream>

#pragma region
namespace FastIO {
constexpr signed bufsize = 1 << 24;
char inbuf[bufsize], *p1 = inbuf, *p2 = inbuf;
char outbuf[bufsize], *pp = outbuf;
inline char gc() {
  if (p1 == p2) p1 = inbuf, p2 = inbuf + fread(inbuf, 1, bufsize, stdin);
  return p1 == p2 ? EOF : *p1++;
}
template <typename T>
inline void read(T &x) {
  x = 0;
  T f = 1;
  char c = gc();
  while (!isdigit(c)) f = ( c == '-' ? -f : f), c = gc();
  while (isdigit(c)) x = x * 10 + c - '0', c = gc();
  x *= f;
}
inline void read(char *s) {
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) c = gc();
  while (isdigit(c) || isalpha(c)) *s++ = c, c = gc();
}
inline void read(std::string &s) {
  std::string().swap(s);
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) c = gc();
  while (isdigit(c) || isalpha(c)) s += c, c = gc();
}
template <typename T, typename... args>
inline void read(T &x, args &...tmp) { read(x), read(tmp...); }
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
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) pc(sta[--top] + '0');
}
inline void print(char *s) {
  for (; s; ++s) pc(*s);
}
inline void print(const std::string &s) {
  for (const auto &c : s) pc(c);
}
template <typename T> inline void print(T x, char c) { print(x), pc(c); }
inline void flush() { fwrite(outbuf, 1, pp - outbuf, stdout), pp = outbuf; }
}  // namespace FastIO
using namespace FastIO;
#pragma endregion

using i64 = long long;

constexpr int month[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
void solve()
{
  int x;
  std::string s;
  read(x, s, s);
  int ans = 0;
  if (s == "week") {
    for (int i = 0; i < 366; i++) {
      if ((4 + i) % 7 + 1 == x) ans++;
    }
  } else {
    ans = std::count_if(month, month + 12, [&](int v) { return v >= x; });
  }
  print(ans, '\n');
  return;
}

signed main() {
  int t = 1;
  // read(t);
  while (t--) solve();
  flush();
  return 0;
}