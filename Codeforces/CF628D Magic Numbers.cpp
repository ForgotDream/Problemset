/**
 * @file    CF628D Magic Numbers.cpp
 * @author  ForgotDream
 * @brief   Digit DP
 * @date    2023-10-30
 */
#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 2050, mod = 1e9 + 7;
int m, d;
char l[N], r[N];
int len, f[N][N][10];
int dfs(char* num, int pos, int rst, int lst, int frm, bool lim) {
  if (pos == len + 1) return (rst == 0);
  if (frm && !lim && ~f[pos][rst][lst]) return f[pos][rst][lst];
  int res = 0, up = lim ? (num[pos] - '0') : 9;
  if (frm && (pos - frm + 1) % 2 == 0) {
    if (up >= d) {
      (res += dfs(num, pos + 1, (rst * 10 + d) % m, d, frm, lim && (d == up))) %= mod;
    }
  } else {
    for (int i = 0; i <= up; i++) {
      if (i == d) continue;
      int nxt = frm;
      if (!frm && i) nxt = pos;
      (res += dfs(num, pos + 1, (rst * 10 + i) % m, i, nxt, lim && (i == up))) %= mod;
    }
  }
  if (!lim && frm) f[pos][rst][lst] = res;
  return res;
}
int calc(char* num) {
  len = strlen(num + 1);
  return dfs(num, 1, 0, 0, 0, true);
}
void reduce(char* num) {
  int len = strlen(num + 1);
  num[len]--;
  for (int i = len; i >= 1; i--) {
    if (num[i] < '0') num[i] += 10, num[i - 1]--;
  }
}
void solve() {
  memset(f, -1, sizeof(f));
  std::cin >> m >> d >> (l + 1) >> (r + 1);
  reduce(l);
  std::cout << (calc(r) - calc(l) + mod) % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
