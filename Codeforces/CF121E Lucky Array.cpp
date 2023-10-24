/**
 * @file    CF121E Lucky Array.cpp
 * @author  ForgotDream
 * @brief   Sqrt Data Structure
 * @date    2023-06-09
 */
#include <bits/stdc++.h>

using i64 = long long;

namespace FastIO{
  char buf[1 << 23], *p1 = buf, *p2 = buf;
  inline char gc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++; }
  template<typename T>
  inline void read(T &x) {
    x = 0;
    T f = 1;
    char c = gc();
    while (!isdigit(c)) { f = (c == '-' ? -f : f), c = gc(); }
    while (isdigit(c)) { x = x * 10 + c - '0', c = gc(); }
    x *= f;
  }
  template<typename T, typename ... args>
  inline void read(T &x, args &...tmp) { read(x), read(tmp...); }
  template<typename T>
  inline void print(T x) {
    if (x < 0) { putchar('-'), x = -x; }
    if (x / 10) { print(x / 10); }
    putchar(x % 10 + '0');
  }
  template<typename T>
  inline void print(T x, char c) { print(x), putchar(c); }
  inline void readString(char *s) {
    char c = gc();
    while (!isdigit(c) && !isalpha(c)) { c = gc(); }
    while (isdigit(c) || isalpha(c)) { *s++ = c, c = gc(); }
  }
}


signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<bool> encode(1e4 + 1);
  std::vector<int> decode;
  [&]() {
    for (int i = 1; i <= 10000; i++) {
      auto check = [](int num) -> bool {
        while (num) {
          if (num % 10 != 4 && num % 10 != 7) { return false; }
          num /= 10;
        }
        return true;
      };
      if (check(i)) { encode[i] = true, decode.push_back(i); }
    }
  }();

  int n, m;
  FastIO::read(n, m);

  int blk = std::sqrt(n + 0.5), cnt = n / blk + !!(n % blk);
  std::vector<int> st(cnt), ed(cnt), bln(n);
  for (int i = 0; i < cnt; i++) { st[i] = i * blk, ed[i] = (i + 1) * blk - 1; }
  ed[cnt - 1] = n - 1;
  for (int i = 0; i < n; i++) { bln[i] = i / blk; }

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) { FastIO::read(a[i]); }

  std::vector<std::vector<int>> f(cnt, std::vector<int>(1e4 + 1));
  std::vector<int> add(cnt);
  for (int i = 0; i < n; i++) { f[bln[i]][a[i]]++; }

  while (m--) {
    char opt[10];
    int l, r;
    FastIO::readString(opt), FastIO::read(l, r);
    l--, r--;
    if (opt[0] == 'a') {
      int val;
      FastIO::read(val);
      if (bln[l] == bln[r]) {
        for (int i = l; i <= r; i++) {
          f[bln[l]][a[i]]--, a[i] += val, f[bln[l]][a[i]]++;
        }
      } else {
        for (int i = l; i <= ed[bln[l]]; i++) {
          f[bln[l]][a[i]]--, a[i] += val, f[bln[l]][a[i]]++;
        }
        for (int i = st[bln[r]]; i <= r; i++) {
          f[bln[r]][a[i]]--, a[i] += val, f[bln[r]][a[i]]++;
        }
        for (int i = bln[l] + 1; i < bln[r]; i++) { add[i] += val; }
      }
    } else {
      int ans = 0;
      if (bln[l] == bln[r]) {
        for (int i = l; i <= r; i++) {
          if (encode[a[i] + add[bln[l]]]) { ans++; }
        }
      } else {
        for (int i = l; i <= ed[bln[l]]; i++) {
          if (encode[a[i] + add[bln[l]]]) { ans++; }
        }
        for (int i = st[bln[r]]; i <= r; i++) {
          if (encode[a[i] + add[bln[r]]]) { ans++; }
        }
        for (int i = bln[l] + 1; i < bln[r]; i++) {
          for (auto j : decode) { 
            if (j < add[i]) { continue; }
            ans += f[i][j - add[i]]; 
          }
        }
      }
      FastIO::print(ans, '\n');
    }
  }

  return 0;
}