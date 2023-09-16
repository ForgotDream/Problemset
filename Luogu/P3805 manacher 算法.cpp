/**
 * @file 	P3805 manacher 算法.cpp
 * @author 	ForgotDream
 * @brief 	Manacher 算法
 * @date 	2023-01-31
 */

#include <bits/stdc++.h>

namespace FastIO {
template <typename T>
inline void read(T& x) {
  x = 0;
  T f = 1;
  char c = getchar();
  while (!isdigit(c)) {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
  x *= f;
  return;
}

template <typename T, typename... args>
inline void read(T& x, args&... tmp) {
  read(x);
  read(tmp...);
  return;
}

template <typename T>
inline void print(T x) {
  if (x < 0) putchar('-'), x = -x;
  if (x / 10) print(x / 10);
  putchar(x % 10 + '0');
  return;
}

template <typename T>
inline void print(T x, char c) {
  print(x), putchar(c);
  return;
}
}  // namespace FastIO

using namespace std;
using namespace FastIO;
using i64 = long long;
using i64u = unsigned long long;

static const int N = 1.5e7 + 50;
char raw[N], s[2 * N];
int d[2 * N], cnt;

void init() {
  int len = strlen(raw + 1);
  s[0] = '$';
  for (int i = 1; i <= len; i++) s[++cnt] = '#', s[++cnt] = raw[i];
  s[++cnt] = '#', s[++cnt] = '|';
  return;
}

int Manacher() {
  int r = 0, mid = 0, res = 0;
  for (int i = 1; i <= cnt; i++) {
    d[i] = (i < r) ? min(d[(mid << 1) - i], d[mid] + mid - i) : 1;
    while (s[i + d[i]] == s[i - d[i]]) d[i]++;
    res = max(res, d[i]);
    if (d[i] + i > r) r = d[i] + i, mid = i;
  }
  return res - 1;
}

int main() {
  scanf("%s", raw + 1);

  init();
  // cerr << s + 1 << endl;

  print(Manacher(), '\n');
  return 0;
}