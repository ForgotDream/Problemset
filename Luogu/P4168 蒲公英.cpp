/**
 * @file    P4168 蒲公英.cpp
 * @author  ForgotDream
 * @brief   Sqrt Data Structure
 * @date    2023-06-23
 */
#include <bits/stdc++.h>

using i64 = long long;

namespace FastIO {
char buf[1 << 23], *p1 = buf, *p2 = buf;
inline char gc() {
  if (p1 == p2) { p1 = buf, p2 = buf + fread(buf, 1, 1 << 23, stdin); }
  return p1 == p2 ? EOF : *p1++; 
}
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
using namespace FastIO;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  read(n, m);

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    read(a[i]);
  }

  // Discrete
  auto b = a;
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  for (auto &i : a) {
    i = std::lower_bound(b.begin(), b.end(), i) - b.begin();
  }

  int blk = std::sqrt(n), bcnt = std::ceil(1. * n / blk);
  std::vector<int> s(bcnt), t(bcnt), bln(n);
  for (int i = 0; i < bcnt; i++) {
    s[i] = i * blk, t[i] = (i + 1) * blk - 1;
  }
  t[bcnt - 1] = n - 1;
  for (int i = 0; i < n; i++) {
    bln[i] = i / blk;
  }

  std::vector range(bcnt, std::vector<std::pair<int, int>>(bcnt));
  std::vector cnt(bcnt, std::vector<int>(b.size()));
  for (int i = 0; i < bcnt; i++) {
    if (i) {
      for (int j = 0; j < b.size(); j++) {
        cnt[i][j] = cnt[i - 1][j];
      }
    }
    for (int j = s[i]; j <= t[i]; j++) {
      cnt[i][a[j]]++;
    }
  }
  std::vector<int> tmp(b.size());
  for (int i = 0; i < bcnt; i++) {
    tmp.assign(b.size(), 0);
    int max = 0, idx = -1;
    for (int j = i; j < bcnt; j++) {
      for (int k = s[j]; k <= t[j]; k++) {
        tmp[a[k]]++;
      }
      for (int k = s[j]; k <= t[j]; k++) {
        if (tmp[a[k]] > max) {
          max = tmp[a[k]];
          idx = a[k];
        } else if (tmp[a[k]] == max && idx > a[k]) {
          idx = a[k];
        }
      }
      range[i][j] = std::make_pair(idx, max);
    }
  }

  int lst = 0;
  auto decode = [&](int i) {
    return (i + lst - 1) % n + 1;
  };

  tmp.assign(b.size(), 0);
  while (m--) {
    int l, r;
    read(l, r);
    l = decode(l) - 1, r = decode(r) - 1;
    if (l > r) {
      std::swap(l, r);
    }
    if (bln[r] - bln[l] <= 1) {
      for (int i = l; i <= r; i++) {
        tmp[a[i]]++;
      }
      int max = 0, idx = -1;
      for (int i = l; i <= r; i++) {
        if (tmp[a[i]] > max) {
          max = tmp[a[i]];
          idx = a[i];
        } else if (tmp[a[i]] == max && idx > a[i]) {
          idx = a[i];
        }
      }
      for (int i = l; i <= r; i++) {
        tmp[a[i]] = 0;
      }
      print(lst = b[idx], '\n');
    } else {
      bool flg = false;
      auto p = range[bln[l] + 1][bln[r] - 1];
      for (int i = l; i <= t[bln[l]]; i++) {
        tmp[a[i]] = cnt[bln[r] - 1][a[i]] - cnt[bln[l]][a[i]];
        if (a[i] == p.first) {
          flg = true;
        }
      }
      for (int i = s[bln[r]]; i <= r; i++) {
        tmp[a[i]] = cnt[bln[r] - 1][a[i]] - cnt[bln[l]][a[i]];
        if (a[i] == p.first) {
          flg = true;
        }
      }
      for (int i = l; i <= t[bln[l]]; i++) {
        tmp[a[i]]++;
      }
      for (int i = s[bln[r]]; i <= r; i++) {
        tmp[a[i]]++;
      }
      if (!flg) {
        tmp[p.first] += p.second;
      }
      int max = tmp[p.first], idx = p.first;
      for (int i = l; i <= t[bln[l]]; i++) {
        if (tmp[a[i]] > max) {
          max = tmp[a[i]];
          idx = a[i];
        } else if (tmp[a[i]] == max && idx > a[i]) {
          idx = a[i];
        }
      }
      for (int i = s[bln[r]]; i <= r; i++) {
        if (tmp[a[i]] > max) {
          max = tmp[a[i]];
          idx = a[i];
        } else if (tmp[a[i]] == max && idx > a[i]) {
          idx = a[i];
        }
      }
      for (int i = l; i <= t[bln[l]]; i++) {
        tmp[a[i]] = 0;
      }
      for (int i = s[bln[r]]; i <= r; i++) {
        tmp[a[i]] = 0;
      }
      tmp[p.first] = 0;
      print(lst = b[idx], '\n');
    }
  }

  return 0;
}
